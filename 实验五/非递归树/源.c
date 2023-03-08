//·ÇµÝ¹éÊ÷

#include<stdio.h>
#define MAXSIZE 128

struct BiNode
{
	char data;
	struct BiNode* lchild;
	struct BiNode* rchild;
};

struct Queue
{
	int front, rear;
	struct BiNode* Elem[MAXSIZE];
}queue;

struct Queue QueueInit()
{
	struct Queue queue;
	queue.front = 0;
	queue.rear = 0;
	return queue;
}

void QueueIn(struct BiNode* Node)
{
	if (Node != NULL)
	{
		queue.Elem[queue.rear] = Node;
		queue.rear++;
		queue.rear = queue.rear % MAXSIZE;
	}
}

struct BiNode* QueueOut()
{
	struct BiTree* Node = queue.Elem[queue.front];
	queue.front++;
	queue.front = queue.front % MAXSIZE;
	return Node;
}

struct BiNode* BiTreeInit()
{
	struct BiNode* Node = (struct BiNode*)malloc(sizeof(struct BiNode));
	Node->lchild = NULL;
	Node->rchild = NULL;
	return Node;
}

struct BiNode* BiTreeCreat()
{
	struct BiNode* Node;
	char ch;
	printf("Create a node: ");
	scanf("%c", &ch);
	while ((getchar()) != '\n');
	if (ch == ' ')Node = NULL;
	else
	{
		struct BiNode* stack[MAXSIZE];
		int top = 0;
		Node = BiTreeInit();
		Node->data = ch;
		stack[top++] = Node;
		while (top != 0)
		{
			struct BiNode* ONode = (struct BiNode*)malloc(sizeof(struct BiNode));
			ONode = stack[top - 1];
			printf("Create a node: ");
			scanf("%c", &ch);
			while ((getchar()) != '\n');
			if (ONode->lchild == NULL)
			{
				while (ch != ' ')
				{
					struct BiNode* LNode = BiTreeInit();
					LNode->data = ch;
					ONode = stack[top - 1];
					ONode->lchild = LNode;
					stack[top++] = LNode; 
					printf("Create a node: ");
					scanf("%c", &ch);
					while ((getchar()) != '\n');
				}	
				ONode = stack[top - 1];
				printf("Create a node: ");
				scanf("%c", &ch);
				while ((getchar()) != '\n');
			}	
			if (ch == ' ')
			{
				top--;
				ONode = stack[top - 1];
				while (ONode->rchild != NULL)
				{
					top--;
					if (!top)break;
					ONode = stack[top - 1];
				}
				if (top)
				{
					printf("Create a node: ");
					scanf("%c", &ch);
					while ((getchar()) != '\n');
				}	
			}
			if (top)
			{
				struct BiNode* RNode = BiTreeInit();
				RNode->data = ch;
				ONode->rchild = RNode;
				stack[top++] = RNode;
			}
		}
	}
	return Node;
}

void PreOrder(struct BiNode* Node)
{
	struct BiNode* stack[MAXSIZE];
	int top = 0;
	while (Node != NULL || top != 0)
	{
		while (Node != NULL)
		{
			printf("%c", Node->data);
			stack[top] = Node;
			Node = Node->lchild;
			top++;
		}
		if (top != 0)
		{
			top--;
			Node = stack[top];
			Node = Node->rchild;
		}
	}
}

void InOrder(struct BiNode* Node)
{
	struct BiNode* stack[MAXSIZE];
	int top = 0;
	while (Node != NULL || top != 0)
	{
		while (Node != NULL)
		{
			stack[top] = Node;
			Node = Node->lchild;
			top++;
		}
		if (top != 0)
		{
			top--;
			Node = stack[top];
			printf("%c", Node->data);
			Node = Node->rchild;
		}
	}
}

void PostOrder(struct BiNode* Node)
{
	struct Stack
	{
		struct BiNode* node;
		int tag;
	}stack[MAXSIZE];
	int top = 0;
	while (Node != NULL || top != 0)
	{
		while (Node != NULL)
		{
			stack[++top].node = Node;
			stack[top].tag = 0;
			Node = Node->lchild;
		}
		while (top != 0 && stack[top].tag)
			printf("%c", stack[top--].node->data);
		if (top)
		{
			stack[top].tag = 1;
			Node = stack[top].node;
			Node = Node->rchild;
		}
	}
}

void LevelOrder(struct BiNode* Node)
{
	QueueIn(Node);
	while (queue.front != queue.rear)
	{
		struct BiNode* NewNode = QueueOut();
		printf("%c", NewNode->data);
		QueueIn(NewNode->lchild);
		QueueIn(NewNode->rchild);
	}
}

void Reserve(struct BiNode* Node)
{
	if (Node != NULL)
	{
		struct BiNode* TempNode = Node->lchild;
		Node->lchild = Node->rchild;
		Node->rchild = TempNode;
		Reserve(Node->lchild);
		Reserve(Node->lchild);
	}
}

void Depth(struct BiNode* Node)
{
	struct BiNode* stack[MAXSIZE];
	int top = 0;
	int count = 0;
	while (Node != NULL || top != 0)
	{
		while (Node != NULL)
		{
			stack[top] = Node;
			Node = Node->lchild;
			top++;
			count = (count > top) ? count : top;
		}
		if (top != 0)
		{
			top--;
			Node = stack[top];
			Node = Node->rchild;
		}
	}
	printf("%d", count);
}

void NumberOfLeaf(struct BiNode* Node)
{
	QueueIn(Node);
	int count = 0;
	while (queue.front != queue.rear)
	{
		struct BiNode* NewNode = QueueOut();
		if (NewNode->lchild == NULL && NewNode->rchild == NULL)count++;
		else
		{
			QueueIn(NewNode->lchild);
			QueueIn(NewNode->rchild);
		}
	}
	printf("%d", count);
}

void Calculate(struct BiNode* Node, int* count)
{
	if (Node != NULL)
	{
		*count = *count + 1;
		Calculate(Node->lchild, count);
		Calculate(Node->rchild, count);
	}
}

void NumberOfNode(struct BiNode* Node)
{
	int count = 0;
	int* p_count = &count;
	Calculate(Node, p_count);
	printf("%d", count);
}

int main()
{
	struct BiNode* HeadNode = BiTreeInit();
	struct Queue queue = QueueInit();
	printf("Input data to creat a tree\n");
	HeadNode->lchild = BiTreeCreat();
	if (HeadNode->lchild != NULL)
	{
		struct BiNode* Node = (struct BiNode*)malloc(sizeof(struct BiNode));
		Node = HeadNode->lchild;
		printf("\nDepth of the tree: ");
		Depth(Node);
		printf("\nNumber of leaves of the tree: ");
		NumberOfLeaf(Node);
		printf("\nNumber of nodes of the tree: ");
		NumberOfNode(Node);
		printf("\n------Before swap left and right subtrees------");
		printf("\nRepresented in the form of preorder traversal: ");
		PreOrder(Node);
		printf("\nRepresented in the form of inorder traversal: ");
		InOrder(Node);
		printf("\nRepresented in the form of postorder traversal: ");
		PostOrder(Node);
		printf("\nRepresented in the form of levelorder traversal: ");
		LevelOrder(Node);
		printf("\n------After swap left and right subtrees------");
		Reserve(Node);
		printf("\nRepresented in the form of preorder traversal: ");
		PreOrder(Node);
		printf("\nRepresented in the form of inorder traversal: ");
		InOrder(Node);
		printf("\nRepresented in the form of postorder traversal: ");
		PostOrder(Node);
		printf("\nRepresented in the form of levelorder traversal: ");
		LevelOrder(Node);
		printf("\n");
	}
	else printf("The tree is not exist!\n");
	printf("\n");
	system("pause");
	return 0;
}