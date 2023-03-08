//¡¥∂”¡–

#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<Windows.h>

struct Queue
{
	int number;
	struct Queue* next;
};

struct LQPointer
{
	struct LQPointer* front;
	struct LQPointer* rear;
	int count;
}*Pointer;

struct Counter
{
	bool working;
	int number;
	int time_differ;
	time_t start;
	time_t end;
}counter[3];

void CounterIn(struct Counter* counter, int number_in)
{
	counter->working = true;
	counter->number = number_in;
}

void CounterOut(struct Counter* counter)
{
	counter->working = false;
	counter->number = 0;
	counter->time_differ = 0;
}

int TimeCount(int time_base, int time_plus)
{
	srand((unsigned)time(NULL));
	return time_base + rand() % time_plus;
}

struct LQPointer* QueueInit()
{
	struct LQPointer* Pointer = (struct LQPointer*)malloc(sizeof(struct LQPointer));
	struct Queue* HeadNode = (struct Queue*)malloc(sizeof(struct Queue));
	Pointer->count = 0;
	HeadNode->number = 0;
	HeadNode->next = NULL;
	Pointer->front = HeadNode;
	Pointer->rear = Pointer->front;
	return Pointer;
}

void QueueIn(struct LQPointer* Pointer)
{
	Pointer->count++;
	struct Queue* NewNode = (struct Queue*)malloc(sizeof(struct Queue));
	struct Queue* Node = (struct Queue*)malloc(sizeof(struct Queue)); 
	Node = Pointer->rear;
	NewNode->number = Pointer->count;
	NewNode->next = NULL;
	Node->next = NewNode;
	Pointer->rear = NewNode;
	printf("You have successfully obtained the number!\n");
	printf("You number: %d\n", NewNode->number);
}

int QueueOut(struct LQPointer* Pointer)
{
	if (Pointer->front == Pointer->rear)
	{
		printf("Queue is empty!\n");
		return 0;
	}
	struct Queue* Node = (struct Queue*)malloc(sizeof(struct Queue)); 
	struct Queue* DelNode = (struct Queue*)malloc(sizeof(struct Queue));
	Node = Pointer->front;
	DelNode = Node->next;
	int number = DelNode->number;
	Node->next = DelNode->next;
	if (Pointer->rear == DelNode)Pointer->rear = Node;
	free(DelNode);
	return number;
}

void display(struct LQPointer* Customer)
{
	struct Queue* Node = (struct Queue*)malloc(sizeof(struct Queue));
	Node = Customer->front;
	Node = Node->next;
	printf("©∞©§©§©§©§©§©§©§©§©§©§©§©§©–©§©§©§©§©§©§©§©§©§©§©§©§©–©§©§©§©§©§©§©§©§©§©§©§©§©¥\n");
	printf("©¶   Window1  ©¶   Window2  ©¶   Window3  ©¶\n");
	printf("©¿©§©§©§©§©§©§©§©§©§©§©§©§©‡©§©§©§©§©§©§©§©§©§©§©§©§©‡©§©§©§©§©§©§©§©§©§©§©§©§©»\n©¶");
	for (int i = 0; i < 3; i++)
	{
		if (counter[i].number == 0)printf("    Spare   ©¶");
		else printf(" Working:%3d©¶", counter[i].number);
	}
	printf("\n");
	printf("©∏©§©§©§©§©§©§©§©§©§©§©§©§©ÿ©§©§©§©§©§©§©§©§©§©§©§©§©ÿ©§©§©§©§©§©§©§©§©§©§©§©§©º\n");
	printf("Waiting List(s):\n");
	int count = 0;
	while (Node != NULL)
	{
		if (count == 10)
		{
			printf("\n");
			count = 0;
		}
		printf("%4d", Node->number);
		count++;
		Node = Node->next;
	}
	printf("\n");
	printf("-----------Functions--------------\n\n");
	printf("\t[1]Get number\n\n\t[0]Exit\n\n");
	printf("----------------------------------\n");
}

bool call(struct LQPointer* Customer)
{
	struct Queue* Node = (struct Queue*)malloc(sizeof(struct Queue)); 
	Node = Customer->front;
	Node = Node->next;
	bool flag = false;
	if (Customer->front != Customer->rear)
	{
		for (int i = 0; i < 3; i++)
			if (!counter[i].working)
			{
				CounterIn(&counter[i], QueueOut(Customer));
				flag = true;
				break;
			}
	}
	return flag;
}

void refresh(struct LQPointer* Customer)
{
	if (call(Customer))
	{
		system("cls");
		display(Customer);
	}
	for (int i = 0; i < 3; i++)
	{
		if (counter[i].working)
		{
			if (counter[i].time_differ)
			{
				counter[i].end = clock();
				if (counter[i].end - counter[i].start > counter[i].time_differ * 1000)
				{
					CounterOut(&counter[i]);
					system("cls");
					display(Customer);
				}
			}
			else
			{
				counter[i].start = clock();
				counter[i].time_differ = TimeCount(10, 20);
			}
		}
	}
}

void GetNumber(struct LQPointer* Customer)
{
	clock_t start, end;
	QueueIn(Customer);
	bool nothing = call(Customer);
	printf("\n");
	printf("3...");
	int rest = 3;
	start = clock();
	while (rest)
	{
		end = clock();
		switch (rest)
		{
		case 3:
			if (end - start == 1000)
			{
				printf("2...");
				rest = 2;
				break;
			}
		case 2:
			if (end - start == 2000)
			{
				printf("1...");
				rest = 1;
				break;
			}
		case 1:
			if (end - start == 3000)
			{
				rest = 0;
				break;
			}
		}
	}
	system("cls");
	display(Customer);
}

void Pager()
{
	struct LQPointer* Customer = QueueInit();
	for (int i = 0; i < 3; i++)
	{
		counter[i].working = false;
		counter[i].number = 0;
		counter[i].time_differ = 0;
	}
	display(Customer);
	while (true)
	{
		refresh(Customer);
		if (GetAsyncKeyState('1'))GetNumber(Customer);
		if (GetAsyncKeyState('0'))return;
	}
}

int main()
{
	Pager();
	return 0;
}