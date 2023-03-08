//¾ØÕóµÄ×ªÖÃ

#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 128

struct Triple
{
	int row;
	int col;
	int data;
};

struct TSMatrix
{
	struct Triple Elem[MAXSIZE];
	int length_row, length_col, length_Elem;
};

struct TSMatrix* MatrixInit()
{
	struct TSMatrix* TsMatrix = (struct TSMatrix*)malloc(sizeof(struct TSMatrix));
	printf("Please enter the number of rows and columns of the matrix.\n");
	printf("row: ");
	scanf("%d", &TsMatrix->length_row);
	printf("col: ");
	scanf("%d", &TsMatrix->length_col);
	TsMatrix->length_Elem = 0;
	printf("\n");
	int data_in;
	for (int i = 0; i < TsMatrix->length_row; i++)
	{
		printf("row %d: ", i + 1);
		for (int j = 0; j < TsMatrix->length_col; j++)
		{
			scanf("%d", &data_in);
			if (data_in)
			{
				TsMatrix->Elem[TsMatrix->length_Elem].row = i;
				TsMatrix->Elem[TsMatrix->length_Elem].col = j;
				TsMatrix->Elem[TsMatrix->length_Elem].data = data_in;
				TsMatrix->length_Elem++;
			}
		}
	}
	printf("\n");
	return TsMatrix;
}

struct TSMatrix* FastTransMatrix(struct TSMatrix* A)
{
	int number[MAXSIZE];
	int position[MAXSIZE];
	struct TSMatrix* B = (struct TSMatrix*)malloc(sizeof(struct TSMatrix));
	B->length_row = A->length_col; 
	B->length_col = A->length_row;
	B->length_Elem = A->length_Elem;
	if (B->length_Elem)
	{
		for (int j = 0; j < A->length_col; j++)
			number[j] = 0;
		for (int t = 0; t < A->length_Elem; t++)
			number[A->Elem[t].col]++;
		position[0] = 0;
		for (int j = 1; j < A->length_col; j++)
			position[j] = position[j - 1] + number[j - 1];
		for (int p = 0; p < A->length_Elem; p++)  
		{
			int j = A->Elem[p].col;
			int q = position[j];
			B->Elem[q].row = A->Elem[p].col;
			B->Elem[q].col = A->Elem[p].row;
			B->Elem[q].data = A->Elem[p].data;
			position[j]++;
		}
	}
	return B;
}

void print(struct TSMatrix* TsMatrix)
{
	int count = 0;
	for (int i = 0; i < TsMatrix->length_row; i++)
	{
		for (int j = 0; j < TsMatrix->length_col; j++)
		{
			if (TsMatrix->Elem[count].row == i && TsMatrix->Elem[count].col == j)
			{
				printf("%4d", TsMatrix->Elem[count].data);
				count++;
			}
			else printf("%4d", 0);
		}
		printf("\n");
	}
	count = 0;
	printf("©°©¤©¤©¤©¤©¤©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©¤©Ð©¤©¤©¤©¤©¤©¤©¤©¤©´\n");
	printf("©¦   row  ©¦   col  ©¦  data  ©¦\n");
	for (int i = 0; i < TsMatrix->length_row; i++)
	{
		for (int j = 0; j < TsMatrix->length_col; j++)
			if (TsMatrix->Elem[count].row == i && TsMatrix->Elem[count].col == j)
			{
				printf("©À©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©à©¤©¤©¤©¤©¤©¤©¤©¤©È\n");
			    printf("©¦  %3d   ©¦  %3d   ©¦  %3d   ©¦\n", TsMatrix->Elem[count].row + 1, TsMatrix->Elem[count].col + 1, TsMatrix->Elem[count].data);
				count++;
			}
	}
	printf("©¸©¤©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©¤©Ø©¤©¤©¤©¤©¤©¤©¤©¤©¼\n");
}

void Trans()
{
	struct TSMatrix* TsMatrix = MatrixInit();
	printf("Before transpose: \n");
	print(TsMatrix);
	TsMatrix = FastTransMatrix(TsMatrix);
	printf("After transpose: \n");
	print(TsMatrix);
}

int main()
{
	Trans();
	system("pause");
	return 0;
}