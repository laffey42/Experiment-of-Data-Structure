//Í¼µÄ±éÀú

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct Node
{
	int index;
	struct Node* next;
};

struct LNode
{
	char vexName;
	struct Node* firstarc;
};

struct Graph
{
	struct LNode* NodeList;
	int length;
};

struct Graph* CreateGraph()
{
	int n, vex01, vex02;
	printf("Please enter the number of vertex: ");
	scanf("%d", &n);
	struct Graph* G = (struct Graph*)malloc(sizeof(struct Graph));
	G->NodeList = (struct LNode*)malloc(sizeof(struct LNode) * n);
	G->length = n;
	char ch;
	printf("Please enter the name of every vertex\n");
	for (int i = 0; i < n; i++)
	{
		while (getchar() != '\n');
		printf("vextex %d: ", i);
		scanf("%c", &ch);
		G->NodeList[i].vexName = ch;
		G->NodeList[i].firstarc = NULL;
	}
	printf("Please enter the coordinates of two vertices to determine their relationship\n");
	scanf("%d%d", &vex01, &vex02);
	while (vex01 != vex02)
	{
		struct Node* NewNode01 = (struct Node*)malloc(sizeof(struct Node));
		NewNode01->index = vex02;
		NewNode01->next = G->NodeList[vex01].firstarc;
		G->NodeList[vex01].firstarc = NewNode01;
		struct Node* NewNode02 = (struct Node*)malloc(sizeof(struct Node));
		NewNode02->index = vex01;
		NewNode02->next = G->NodeList[vex02].firstarc;
		G->NodeList[vex02].firstarc = NewNode02;
		scanf("%d%d", &vex01, &vex02);
	}
	return G;
}

void BFS(struct Graph* G)
{
	int length = G->length, front = 0, rear = 0;
	struct LNode* List = G->NodeList;
	bool* flag = (bool*)malloc(sizeof(bool) * length);
	int* queue = (int*)malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++)
		flag[i] = false;
	printf("Result of BFS: ");
	for (int i = 0; i < length; i++)
	{
		if (!flag[i])queue[rear++] = i;
		int index = queue[front++];
		flag[index] = true;
		printf("%c", List[index].vexName);
		if (!flag[i])
		{
			if (List[index].firstarc != NULL)
			{
				struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
				NewNode = List[index].firstarc;
				if(!flag[NewNode->index])queue[rear++] = NewNode->index;
				while (NewNode->next != NULL)
				{
					NewNode = NewNode->next;
					if (!flag[NewNode->index])queue[rear++] = NewNode->index;
				}
			}
		}
	}
	printf("\n");
}

void display(struct Graph* G)
{
	int length = G->length;
	struct LNode* List = G->NodeList;
	printf("Adjacency list: \n");
	for (int i = 0; i < length; i++)
	{
		printf("%c", List[i].vexName);
		if (List[i].firstarc != NULL)
		{
			struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
			NewNode = List[i].firstarc;
			int index = NewNode->index;
			printf("->%c", List[index].vexName);
			while (NewNode->next != NULL)
			{
				NewNode = NewNode->next;
				index = NewNode->index;
				printf("->%c", List[index].vexName);
			}
			printf("%d\t", closeEdge[j].distance);
		}
		printf("\n");
	}
}

int main()
{
	struct Graph* G = CreateGraph();
	BFS(G);
	display(G);
	return 0;
}