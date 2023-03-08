//À≥–Ú∂”¡–

#include<stdio.h>
#include<stdbool.h>
#include<time.h>
#include<Windows.h>
#define MAXSIZE 128

struct Queue
{
	int front, rear;
	bool check[MAXSIZE];
};

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
	counter->number = MAXSIZE;
	counter->time_differ = 0;
}

int TimeCount(int time_base,int time_plus)
{
	srand((unsigned)time(NULL));
	return time_base + rand() % time_plus;
}

struct Queue QueueInit()
{
	struct Queue queue;
	queue.front = 0;
	queue.rear = 0;
	for (int i = 0; i < MAXSIZE; i++)
		queue.check[i] = false;
	return queue;
}

void QueueIn(struct Queue* queue)
{
	if (queue->front == queue->rear && queue->check[queue->front] == true)
	{
		printf("Queue is full!\n");
		return;
	}
	printf("You have successfully obtained the number!\n");
	printf("You number: %d\n", queue->rear + 1);
	queue->check[queue->rear] = true;
	queue->rear = (queue->rear + 1) % MAXSIZE;
}

int QueueOut(struct Queue* queue)
{
	if (queue->front == queue->rear && queue->check[queue->front] == false)
	{
		printf("Queue is empty!\n");
		return MAXSIZE;
	}
	queue->check[queue->front] = false;
	int called = queue->front;
	queue->front = (queue->front + 1) % MAXSIZE;
	return called;
}

void display(struct Queue Customer)
{
	printf("©∞©§©§©§©§©§©§©§©§©§©§©§©§©–©§©§©§©§©§©§©§©§©§©§©§©§©–©§©§©§©§©§©§©§©§©§©§©§©§©¥\n");
	printf("©¶   Window1  ©¶   Window2  ©¶   Window3  ©¶\n");
	printf("©¿©§©§©§©§©§©§©§©§©§©§©§©§©‡©§©§©§©§©§©§©§©§©§©§©§©§©‡©§©§©§©§©§©§©§©§©§©§©§©§©»\n©¶");
	for (int i = 0; i < 3; i++)
	{
		if (counter[i].number == MAXSIZE)printf("    Spare   ©¶");
		else printf(" Working:%3d©¶", counter[i].number + 1);
	}
	printf("\n");
	printf("©∏©§©§©§©§©§©§©§©§©§©§©§©§©ÿ©§©§©§©§©§©§©§©§©§©§©§©§©ÿ©§©§©§©§©§©§©§©§©§©§©§©§©º\n");
	printf("Waiting List(s):\n");
	int count = 0;
	for (int i = 0; i < MAXSIZE; i++)
	{
		if (count == 10)
		{
			printf("\n");
			count = 0;
		}
		if (Customer.check[i])
		{
			printf("%4d", i + 1);
			count++;
		}
	}
	printf("\n");
	printf("-----------Functions--------------\n\n");
	printf("\t[1]Get number\n\n\t[0]Exit\n\n");
	printf("----------------------------------\n");
}

bool call(struct Queue* Customer)
{
	bool flag = false;
	if (Customer->check[Customer->front])
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

void refresh(struct Queue *Customer)
{
	if (call(Customer))
	{
		system("cls");
		display(*Customer);
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
					display(*Customer);
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

void GetNumber(struct Queue* Customer)
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
	display(*Customer);
}

void Pager()
{
	struct Queue Customer = QueueInit();
	for (int i = 0; i < 3; i++)
	{
		counter[i].working = false;
		counter[i].number = MAXSIZE;
		counter[i].time_differ = 0;
	}
	display(Customer);
	while (true)
	{
		refresh(&Customer);
		if (GetAsyncKeyState('1'))GetNumber(&Customer);
		if (GetAsyncKeyState('0'))return;
	}
}

int main()
{
	Pager();
	return 0;
}