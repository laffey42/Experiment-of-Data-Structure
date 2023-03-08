//Õÿ∆À≈≈–Ú

#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int index;
	struct Node* next;
};

struct LNode
{
	int indegree;
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
		G->NodeList[i].indegree = 0;
		G->NodeList[i].firstarc = NULL;
	}
	printf("Please enter the coordinates of two vertices to determine their relationship\n");
	scanf("%d%d", &vex01, &vex02);
	while (vex01 != vex02)
	{
		struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
		NewNode->index = vex02;
		NewNode->next = G->NodeList[vex01].firstarc;
		G->NodeList[vex01].firstarc = NewNode;
		G->NodeList[vex02].indegree++;
		scanf("%d%d", &vex01, &vex02);
	}
	return G;
}

void Topo(struct Graph* G)
{
	int length = G->length, top = 0;
	struct LNode* List = G->NodeList;
	int* stack = (int*)malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++)
	{
		if (!List[i].indegree)
		{
			stack[top] = i;
			top++;
			break;
		}
	}
	printf("Topological sequence: ");
	while (top)
	{
		top--;
		int index = stack[top];
		printf("%c", List[index].vexName);
		List[index].indegree--;
		if (List[index].firstarc != NULL)
		{
			struct Node* NewNode = (struct Node*)malloc(sizeof(struct Node));
			NewNode = List[index].firstarc;
			index = NewNode->index;
			List[index].indegree--;
			while (NewNode->next != NULL)
			{
				NewNode = NewNode->next;
				index = NewNode->index;
				List[index].indegree--;
			}
		}
		for (int i = 0; i < length; i++)
		{
			if (!List[i].indegree)
			{
				stack[top] = i;
				top++;
				break;
			}
		}
	}
	printf("\n");
}

int main()
{
	struct Graph* G = CreateGraph();
	Topo(G);
	return 0;
}