//Á´Õ»

#include<stdio.h>
#include<math.h>
#include<stdbool.h>

struct Stack_OPTR
{
	char data;
	struct Stack_OPTR* next;
};

struct Stack_OPND
{
	double data;
	struct Stack_OPND* next;
};

struct Stack_OPTR* Push_OPTR(struct Stack_OPTR* Node, char data_in)
{
	struct Stack_OPTR* NewNode = (struct Stack_OPTR*)malloc(sizeof(struct Stack_OPTR));
	NewNode->data = data_in;
	NewNode->next = Node;
	Node = NewNode;
	return Node;
}

struct Stack_OPND* Push_OPND(struct Stack_OPND* Node, double data_in)
{
	struct Stack_OPND* NewNode = (struct Stack_OPND*)malloc(sizeof(struct Stack_OPND));
	NewNode->data = data_in;
	NewNode->next = Node;
	Node = NewNode;
	return Node;
}

struct Stack_OPTR* Pop_OPTR(struct Stack_OPTR* Node, char* data_out)
{
	*data_out = Node->data;
	struct Stack_OPND* DelNode = Node;
	Node = Node->next;
	DelNode = NULL;
	free(DelNode);
	return Node;
}

struct Stack_OPND* Pop_OPND(struct Stack_OPND* Node, double* data_out)
{
	*data_out = Node->data;
	struct Stack_OPND* DelNode = Node;
	Node = Node->next;
	DelNode = NULL;
	free(DelNode);
	return Node;
}

char Precede(struct Stack_OPTR* Node, char data_in)
{
	char  ch_cmp = Node->data;
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
		struct Stack_OPTR* OPTR = (struct Stack_OPTR*)malloc(sizeof(struct Stack_OPTR));
		struct Stack_OPND* OPND = (struct Stack_OPND*)malloc(sizeof(struct Stack_OPND));
		OPTR->next = NULL;
		OPND->next = NULL;
		OPTR = Push_OPTR(OPTR, '#');
		char ch = getchar();
		bool sx = true;
		if (ch != '#')
		{
			while (!(ch == '#' && OPTR->next->next == NULL))
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
					OPND = Push_OPND(OPND, num);	
				}
				else if (Judgement(ch) == 1)
				{
					switch (Precede(OPTR, ch))
					{
					case'<':
						OPTR = Push_OPTR(OPTR, ch);
						ch = getchar();
						break;
					case'>':
						char theat;
						OPTR = Pop_OPTR(OPTR, &theat);
						double num01, num02;
						OPND = Pop_OPND(OPND, &num02);
						OPND = Pop_OPND(OPND, &num01);
						OPND = Push_OPND(OPND, Operate(num01, num02, theat));
						break;
					case'=':
						char del;
						OPTR = Pop_OPTR(OPTR, &del);
						ch = getchar();
						break;
					}
				}
			}
		}
		printf("--------------------------------------------------------------------------------\n");
		if (sx)
		{
			double result;
			OPND = Pop_OPND(OPND, &result);
			printf("The result is %f\n\n", result);
		}
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