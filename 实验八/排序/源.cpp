#include<stdio.h>
#include<stdlib.h>

int* ArrayCreat(int n)
{
	int* arry = (int*)malloc(sizeof(int) * (n + 1));
	printf("Please input each elum of the array:\n");
	for (int i = 1; i <= n; i++)
	{
		printf("Array[%d]: ", i);
		scanf("%d", &arry[i]);
	}
	return arry;
}

void ArrayPrint(int *arry, int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (i % 11 == 0)printf("\n");
		printf("%d\t", arry[i]);
	}
}

void ShellSort(int* arry, int n)//Ï£¶ûÅÅÐò
{
	printf("Before sorted: \n");
	ArrayPrint(arry, n);
	for (int d = n / 2; d >= 1; d = d / 2)
	{
		for (int i = d + 1; i <= n; i++)
		{
			if (arry[i] < arry[i - d])
			{
				int j = i - d;
				arry[0] = arry[i];
				for (; j >= 0 && arry[0] <= arry[j]; j = j - d)
					arry[j + d] = arry[j];
				arry[j + d] = arry[0];
			}
		}
	}
	printf("\nAfter sorted: \n");
	ArrayPrint(arry, n);
}

void BubbleSort(int* arry, int n)//Ã°ÅÝÅÅÐò
{
	printf("Before sorted: \n");
	ArrayPrint(arry, n);
	for (int i = 1; i <= n; i++)
	{
		int flag = 1;
		for (int j = 1; j <= n - i; j++)
		{
			if (arry[j] > arry[j + 1])
			{
				flag = 0;
				arry[0] = arry[j];
				arry[j] = arry[j + 1];
				arry[j + 1] = arry[0];
			}
		}
		if (flag)break;
	}
	printf("\nAfter sorted: \n");
	ArrayPrint(arry, n);
}

void  Partition(int* arry, int top, int bottom)
{
	if (top < bottom)
	{
		int i = top, j = bottom, t = arry[top];
		while (i < j)
		{
			while (arry[j] >= t)j--;
			if (i < j)arry[0] = arry[i], arry[i++] = arry[j], arry[j] = arry[0];
			while (arry[i] < t)i++;
			if (i < j)arry[0] = arry[j], arry[j--] = arry[i], arry[i] = arry[0];
		}
		arry[i] = t;
		Partition(arry, top, i - 1);
		Partition(arry, i + 1, bottom);
	}
}

void QuickSort(int* arry, int n)//¿ìËÙÅÅÐò
{
	printf("Before sorted: \n");
	ArrayPrint(arry, n);
	Partition(arry, 1, n);
	printf("\nAfter sorted: \n");
	ArrayPrint(arry, n);
}

void Sift(int* arry, int i, int len)
{
	arry[0] = arry[i];
	for (int j = 2 * i; j <= len; j = i * 2)
	{
		if (j < len && arry[j] < arry[j + 1])j++;
		if (arry[0] > arry[j])break;
		else
		{
			arry[i] = arry[j];
			i = j;
		}
	}
	arry[i] = arry[0];
}

void HeapSort(int* arry, int n)//¶ÑÅÅÐò
{
	printf("Before sorted: \n");
	ArrayPrint(arry, n);
	for (int i = n / 2; i > 0; i--)
	{
		Sift(arry, i, n);
	}
	for (int i = n; i > 1; i--)
	{
		arry[0] = arry[1];
		arry[1] = arry[i];
		arry[i] = arry[0];
		Sift(arry, 1, i - 1);
	}
	printf("\nAfter sorted: \n");
	ArrayPrint(arry, n);
}

int main()
{
	char ch;
	int* arry, n;
	while (1)
	{
		printf("----------------\n");
		printf("[1]ShellSort\n[2]BubbleSort\n[3]QuickSort\n[4]HeapSort\n[0]Exit\n");
		printf("----------------\n");
		printf("Select: ");
		switch (ch = getchar())
		{
		case'1':
			system("cls");
			printf("---------------Create an array---------------\n");
			printf("Please enter the length of the array: ");
			scanf("%d", &n);
			arry = ArrayCreat(n);
			while (getchar() != '\n');
			system("cls"); 
			ShellSort(arry, n); 
			break;
		case'2':
			system("cls");
			printf("---------------Create an array---------------\n");
			printf("Please enter the length of the array: ");
			scanf("%d", &n);
			arry = ArrayCreat(n);
			while (getchar() != '\n');
			system("cls"); 
			BubbleSort(arry, n); 
			break;
		case'3':
			system("cls");
			printf("---------------Create an array---------------\n");
			printf("Please enter the length of the array: ");
			scanf("%d", &n);
			arry = ArrayCreat(n);
			while (getchar() != '\n');
			system("cls");
			QuickSort(arry, n);
			break;
		case'4':
			system("cls");
			printf("---------------Create an array---------------\n");
			printf("Please enter the length of the array: ");
			scanf("%d", &n);
			arry = ArrayCreat(n);
			while (getchar() != '\n');
			system("cls");
			HeapSort(arry, n);
			break;
		case'0':return 0;
		default:printf("Error!\n");
		}
		printf("\n");
		system("pause");
		system("cls");
	}
}