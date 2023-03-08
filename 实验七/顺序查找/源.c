//À≥–Ú≤È’“

#include<stdio.h>
#include<stdlib.h>

int* ArrayCreat(int n)
{
	int* arry = (int*)malloc(sizeof(int) * n);
	printf("Please enter every element of array: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &arry[i]);
	return arry;
}

void Search(int* arry, int n, int x)
{
	printf("Result: ");
	for (int i = 0; i < n; i++)
	{
		if (x == arry[i])
		{
			printf("%d is found at index %d\n", x, i);
			return;
		}
	}
	printf("%d is not found!\n", x);
}

int main()
{
	int n, x;
	printf("Please enter the number of array elements: ");
	scanf("%d", &n);
	int* arry = ArrayCreat(n);
	printf("Please enter the number you wnat to find: ");
	scanf("%d", &x);
	Search(arry, n, x);
	return 0;
}