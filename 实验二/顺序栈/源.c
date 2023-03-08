//À≥–Ú’ª

#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#define MAXSIZE 128

struct Stack_OPTR //‘ÀÀ„∑˚’ª
{
	int top;
	char data[MAXSIZE];
};

struct Stack_OPND //‘ÀÀ„¡ø’ª
{
	int top;
	double data[MAXSIZE];
};

void Push_OPTR(struct Stack_OPTR* stack, char data_in)
{
	if (stack->top == MAXSIZE)
	{
		printf("Stack_OPTR is overflow!\n");
		return;
	}
	stack->data[stack->top] = data_in;
	stack->top++;
}

void Push_OPND(struct Stack_OPND* stack, double data_in)
{
	if (stack->top == MAXSIZE)
	{
		printf("Stack_OPND is overflow!\n");
		return;
	}
	stack->data[stack->top] = data_in;
	stack->top++;
}

char Pop_OPTR(struct Stack_OPTR* stack)
{
	if (stack->top == 0)
	{
		printf("Stack_OPTR is empty!\n");
		return 0;
	}
	stack->top--;
	return stack->data[stack->top];
}

double Pop_OPND(struct Stack_OPND* stack)
{
	if (stack->top == 0)
	{
		printf("Stack_OPND is empty!\n");
		return 0;
	}
	stack->top--;
	return stack->data[stack->top];
}

char Precede(struct Stack_OPTR* stack, char data_in)
{
	char  ch_cmp = stack->data[stack->top - 1];
	switch (data_in)
	{
	case'+':
	case'-':
		if (ch_cmp == '+' || ch_cmp == '-' || ch_cmp == '*' || ch_cmp == '/' || ch_cmp == ')')
		{
			return '>';
			break;
		}
		else return '<';
	case'*':
	case'/':
		if (ch_cmp == '*' || ch_cmp == '/' || ch_cmp == ')') return '>';
		else return '<';
	case'(':
		if (ch_cmp == ')')printf("\b");
		else return '<';
		break;
	case')':
		if (ch_cmp == '(')return '=';
		else return '>';
		break;
	case'#':
		if (ch_cmp == '#')return '=';
		else return '>';
		break;
	}
	
}

int Judgement(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '#') return 1;
	if ((ch <= '9' && ch >= '0') || ch == '.')return 2;
	return 0;
}

double Operate(double num01, double num02, char theat)
{
	double result = 0;
	switch (theat)
	{
	case'+':result = num01 + num02; break;
	case'-':result = num01 - num02; break;
	case'*':result = num01 * num02; break;
	case'/':result = num01 / num02; break;
	}
	return result;
}

void Print()
{
	printf("--------------------------------------------------------------------------------\n");
	printf("This is a simple calculator, able to add, subtract, multiply and divide.\n");
	printf("(Tip:Enter '#' as the end sign.)\n");
	printf("Please enter the formula you want to calculate below.\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Formula: ");
}

void Calculator()
{
	while (true)
	{
		Print();
		struct Stack_OPTR OPTR;
		struct Stack_OPND OPND;
		OPTR.top = 0;
		OPND.top = 0;
		Push_OPTR(&OPTR, '#');
		char ch = getchar();
		bool sx = true;
		if (ch != '#')
		{
			while (!(ch == '#' && OPTR.top == 1))
			{
				if (!Judgement(ch))
				{
					printf("error!\n");
					sx = false;
					break;
				}
				else if (Judgement(ch) == 2)
				{
					double num, decimal, integer;
					int count = 0;
					bool flag = true;
					decimal = 0;
					integer = 0;
					while (Judgement(ch) == 2)
					{
						if (ch == '.')
						{
							flag = false;
							ch = getchar();
							continue;
						}
						if (flag)
						{
							integer = integer * 10 + (ch - '0');
							ch = getchar();
						}
						else
						{
							decimal = decimal * 10 + (ch - '0');
							count++;
							ch = getchar();
						}
					}
					num = integer + decimal / pow(10, count);
					count = 0;
					Push_OPND(&OPND, num);
				}
				else if (Judgement(ch) == 1)
				{
					switch (Precede(&OPTR, ch))
					{
					case'<':
						Push_OPTR(&OPTR, ch);
						ch = getchar();
						break;
					case'>':
						char theat = Pop_OPTR(&OPTR);
						double num02 = Pop_OPND(&OPND);
						double num01 = Pop_OPND(&OPND);
						Push_OPND(&OPND, Operate(num01, num02, theat));
						break;
					case'=':
						char del = Pop_OPTR(&OPTR);
						ch = getchar();
						break;
					}
				}
			}
		}
		printf("--------------------------------------------------------------------------------\n");
		if (sx)printf("The result is %f\n\n", Pop_OPND(&OPND));
		system("pause");
		while (ch = getchar() != '\n');
		system("cls");
	}
}

int main()
{
	Calculator();
	return 0;
}