//最小生成树

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 10000

struct Graph
{
	int** matrix;
	int length;
};

struct CloseEdge
{
	int distance;
	int row;
	int col;
};

struct Graph* CreateGraph()
{
	int n, vex01, vex02, distance;
	printf("Please enter the number of vertex: ");
	scanf("%d", &n);
	int** matrix = (int**)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) 
	{
		matrix[i] = (int*)malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++)
			matrix[i][j] = MAXSIZE;
	}
	printf("Please enter the position and distance of two vertices(Make the distance 0 to stop the input): \n");
	scanf("%d%d%d", &vex01, &vex02, &distance);
	while (distance)
	{
		matrix[vex01][vex02] = distance;
		matrix[vex02][vex01] = distance;
		scanf("%d%d%d", &vex01, &vex02, &distance);
	}
	struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
	G->matrix = matrix;
	G->length = n;
	return G;
}

void Prime(struct Graph* G)
{
	int length = G->length;
	int** matrix = G->matrix;
	bool* rest = (bool*)malloc(sizeof(length));
	struct CloseEdge* closeEdge = (struct CloseEdge*)malloc(sizeof(struct CloseEdge) * length);
	for (int i = 0; i < length; i++)
	{
		rest[i] = true;
		closeEdge[i].distance = MAXSIZE;
		closeEdge[i].row = i;
		closeEdge[i].col = i;
	}
	int mark = 0, count = length - 1;
	printf("Result: \n");
	while (count--)
	{
		rest[mark] = false;
		int i = mark, min = MAXSIZE;
		for (int j = 0; j < length; j++)
		{
			if (rest[j] && matrix[i][j] < closeEdge[j].distance)
			{
				closeEdge[j].distance = matrix[i][j];
				closeEdge[j].row = i;
				closeEdge[j].col = j;
			}
			if (closeEdge[j].distance < min)
			{
				min = closeEdge[j].distance;
				mark = j;
			}
			//printf("%d\t", closeEdge[j].distance);
		}
		closeEdge[mark].distance = MAXSIZE;
		printf("(%d,%d)\n", closeEdge[mark].row, closeEdge[mark].col);
	}
}

int main()
{
	struct Graph* G = CreateGraph();
	Prime(G);
	system("pause");
	return 0;
}