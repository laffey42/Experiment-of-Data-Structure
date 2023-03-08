//¾ØÕóµÄ³Ë·¨

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
	int position[MAXSIZE];
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
	int data_in, count = 0; 
	for (int i = 0; i < TsMatrix->length_row; i++)
	{
		printf("row %d: ", i + 1);
		TsMatrix->position[count++] = TsMatrix->length_Elem;
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

struct TSMatrix* MultMatrix(struct TSMatrix* A, struct TSMatrix* B)
{
	if (A->length_col != B->length_row)return NULL;
	struct TSMatrix* C = (struct TSMatrix*)malloc(sizeof(struct TSMatrix));
	C->length_row = A->length_row;
	C->length_col = B->length_col;
	C->length_Elem = 0;
	if (A->length_Elem * B->length_Elem != 0)
	{
		for (int A_row = 0; A_row < A->length_row; A_row++)
		{
			int* sum = (int*)malloc(sizeof(int) * C->length_col);
			for (int C_col = 0; C_col < C->length_col; C_col++)
				sum[C_col] = 0;
			C->position[A_row] = C->length_Elem;
			int end_A;
			if (A_row + 1 < A->length_row)end_A = A->position[A_row + 1];
			else end_A = A->length_Elem;
			for (int p = A->position[A_row]; p < end_A; p++)
			{
				int B_row = A->Elem[p].col;
				int end_B;
				if (B_row + 1 < B->length_row)end_B = B->position[B_row + 1];
				else end_B = B->length_Elem;
				for (int q = B->position[B_row]; q < end_B; q++)
				{
					int C_col = B->Elem[q].col;
					sum[C_col] += A->Elem[p].data * B->Elem[q].data;
				}
			}
			for (int C_col = 0; C_col < C->length_col; C_col++)
			{
				if (sum[C_col])
				{
					if (C->length_Elem > MAXSIZE) return NULL;
					C->Elem[C->length_Elem].row = A_row;
					C->Elem[C->length_Elem].col = C_col;
					C->Elem[C->length_Elem].data = sum[C_col];
					C->length_Elem++;
				}
			}
		}
	}
	return C;
}

void Calculate()
{
	struct TSMatrix* TsMatrix_A = MatrixInit();
	struct TSMatrix* TsMatrix_B = MatrixInit();
	struct TSMatrix* TsMatrix_C = MultMatrix(TsMatrix_A, TsMatrix_B);
	if (TsMatrix_C != NULL)
	{
		printf("The result is: \n");
		print(TsMatrix_C);
	}
	else printf("These two matrices cannot be multiplied!\n");
}

int main()
{
	Calculate();
	system("pause");
	return 0;
}