//’€∞Î≤È’“

#include<stdio.h>
#include<stdlib.h>

struct Array
{
	int* arry;
	int length;
};

void Sort(int* arry, int length)
{
	for (int i = 0; i < length; i++)
	{
		int mark = i, min = arry[i];
		for (int j = i + 1; j < length; j++)
		{
			if (arry[j] < min)
			{
				mark = j;
				min = arry[j];
			}
		}
		arry[mark] = arry[i];
		arry[i] = min;
	}
}

struct Array* ArrayCreat()
{
	struct Array* arryBinary = (struct Array*)malloc(sizeof(struct Array));
	printf("Please enter the number of array elements: ");
	scanf("%d", &arryBinary->length);
	int* arry = (int*)malloc(sizeof(int) * arryBinary->length);
	printf("Please enter every element of array: ");
	for (int i = 0; i < arryBinary->length; i++)
		scanf("%d", &arry[i]);
	Sort(arry, arryBinary->length);
	int count = 1;
	printf("After sorted:\n");
	for (int i = 0; i < arryBinary->length; i++)
	{
		if (count++ == 10)
		{
			printf("\n");
			count = 1;
		}
		printf("%d\t", arry[i]);
	}
	printf("\n");
	arryBinary->arry = arry;
	return arryBinary;
}

void SearchNormal(struct Array* arryBinary)
{
	int length = arryBinary->length;
	int* arry = arryBinary->arry;
	int x, middle, begin = 0, end = length - 1;
	printf("---------------Non-Recursive---------------\n");
	printf("Please enter the number you wnat to find: ");
	scanf("%d", &x);
	while (end - begin >= 0)
	{
		middle = (begin + end) / 2;
		if (x < arry[middle])end = middle - 1;
		else if (x > arry[middle])begin = middle + 1;
		else 
		{
			printf("%d is found at index %d\n", x, middle);
			return;
		}
	}
	printf("%d is not found!\n", x);
}

int Recursive(int* arry, int begin, int end, int x)
{
	if (end - begin < 0)
	{
		printf("%d is not found!\n", x);
		return;
	}
	int middle = (begin + end) / 2;
	if (x < arry[middle])Recursive(arry, begin, middle - 1, x);
	else if (x > arry[middle])Recursive(arry, middle + 1, end, x);
	else
	{
		printf("%d is found at index %d\n", x, middle);
		return;
	}
}

void SearchRecursive(struct Array* arryBinary)
{
	int length = arryBinary->length;
	int* arry = arryBinary->arry;
	int x, begin = 0, end = length - 1;
	printf("-----------------Recursive-----------------\n");
	printf("Please enter the number you wnat to find: ");
	scanf("%d", &x);
	Recursive(arry, begin, end, x);
}

int main()
{
	struct Array* arryBinary = ArrayCreat();
	SearchNormal(arryBinary);
	SearchRecursive(arryBinary);
	return 0;
}