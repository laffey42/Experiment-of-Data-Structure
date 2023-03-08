#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int ListLength = 0;

struct Worker {
	struct Worker* prior;
	long JobNumber;
	char Name[20];
	int WorkYear;
	float BasePay;
	float Sub;
	float Bonus;
	float Charge;
	float NetPay;
	int Rank;
	struct Worker* next;
};

struct RankMark{
	struct RankMark* prior;
	int WorkYear;
	struct Worker* Mark;
	struct RankMark* next;
};

void load(struct Worker* HeadNode)
{
	FILE* fp;
	fp = fopen("D:\\test\\data\\test_02", "rb");
	if (!fp)
	{
		printf("错误：文件打开失败！\n");
		return -1;
	}
	long JobNumber;
	char Name[20];
	int WorkYear, Rank;
	float BasePay, Sub, Bonus, Charge, NetPay;
	while (fscanf(fp, "%ld%s%d%f%f%f%f%f%d", &JobNumber, Name, &WorkYear, &BasePay, &Sub, &Bonus, &Charge, &NetPay, &Rank) != EOF)
	{
		struct Worker* Node = (struct Worker*)malloc(sizeof(struct Worker));
		Node->JobNumber = JobNumber;
		strcpy(Node->Name, Name);
		Node->WorkYear = WorkYear;
		Node->BasePay = BasePay;
		Node->Sub = Sub;
		Node->Bonus = Bonus;
		Node->Charge = Charge;
		Node->NetPay = NetPay;
		Node->Rank = Rank;
		if (!ListLength)
		{
			Node->next = HeadNode->next;
			HeadNode->next = Node;
			Node->prior = HeadNode;
		}
		else
		{
			struct Worker* CompareNode = HeadNode;
			bool flag = false;
			while (CompareNode->next != NULL)
			{
				CompareNode = CompareNode->next;
				if (Node->JobNumber < CompareNode->JobNumber)
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				Node->prior = CompareNode->prior;
				Node->next = CompareNode;
				CompareNode->prior->next = Node;
				CompareNode->prior = Node;
			}
			else
			{
				Node->next = CompareNode->next;
				CompareNode->next = Node;
				Node->prior = CompareNode;
			}
		}
		ListLength++;
	}
	fclose(fp);
}

void save(struct Worker* HeadNode)
{
	FILE* fp;
	fp = fopen("D:\\test\\data\\test_02", "wb");
	if (!fp)
	{
		printf("错误：文件打开失败！\n");
		return -1;
	}
	struct Worker* Node = HeadNode->next;
	while (Node != NULL)
	{
		fprintf(fp, "%ld %s %d %.2f %.2f %.2f %.2f %.2f %d\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay, Node->Rank);
		Node = Node->next;
	}
	fclose(fp);
}

void input(struct Worker* NewNode)
{
	printf("请输入要插入的工人信息\n");
	printf("工号：");
	scanf("%ld", &NewNode->JobNumber);
	printf("姓名：");
	scanf("%s", NewNode->Name);
	printf("工龄：");
	scanf("%d", &NewNode->WorkYear);
	printf("基本工资：");
	scanf("%f", &NewNode->BasePay);
	printf("奖金：");
	scanf("%f", &NewNode->Bonus);
	printf("水电费：");
	scanf("%f", &NewNode->Charge);
	NewNode->Sub = NewNode->WorkYear * 200;
	NewNode->NetPay = NewNode->BasePay + NewNode->Sub + NewNode->Bonus - NewNode->Charge;
	NewNode->Rank = 0;
}

void rankSort(struct Worker* HeadNode)
{
	struct Worker* Node = HeadNode->next;
	struct RankMark* HeadNodeRank = (struct RankMark*)malloc(sizeof(struct RankMark));
	HeadNodeRank->next = NULL;
	while (Node != NULL)
	{
		struct RankMark* RankNode = (struct RankMark*)malloc(sizeof(struct RankMark));
		RankNode->WorkYear = Node->WorkYear;
		RankNode->Mark = Node;
		if (HeadNodeRank->next == NULL)
		{
			RankNode->next = HeadNodeRank->next;
			HeadNodeRank->next = RankNode;
			RankNode->prior = HeadNodeRank;
		}
		else
		{
			struct RankMark* NodeRank = HeadNodeRank;
			bool flag = false;
			while (NodeRank->next != NULL)
			{
				NodeRank = NodeRank->next;
				if (NodeRank->WorkYear < RankNode->WorkYear)
				{
					flag = true;
					break;
				}
			}
			if (flag)
			{
				RankNode->prior = NodeRank->prior;
				RankNode->next = NodeRank;
				NodeRank->prior->next = RankNode;
				NodeRank->prior = RankNode;
			}
			else
			{
				RankNode->next = NodeRank->next;
				NodeRank->next = RankNode;
				RankNode->prior = NodeRank;
			}
		}
		Node = Node->next;
	}
	struct RankMark* NodeSorted = (struct RankMark*)malloc(sizeof(struct RankMark));
	NodeSorted = HeadNodeRank->next;
	int i = 1;
	while (NodeSorted!= NULL)
	{
		NodeSorted->Mark->Rank = i++;
		NodeSorted = NodeSorted->next;
	}
}

void search(struct Worker* HeadNode)
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		printf("请输入要查找工人的工号：");
		long InputJobNumber;
		scanf("%ld", &InputJobNumber);
		struct Worker* SearchNode = HeadNode->next;
		bool flag = false;
		while (SearchNode != NULL)
		{
			if (SearchNode->JobNumber == InputJobNumber)
			{
				flag = true;
				break;
			}
			SearchNode = SearchNode->next;
		}
		if (flag)
		{
			printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
			printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
			printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
			printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", SearchNode->JobNumber, SearchNode->Name, SearchNode->WorkYear, SearchNode->BasePay, SearchNode->Sub, SearchNode->Bonus, SearchNode->Charge, SearchNode->NetPay, SearchNode->Rank);
			printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
		}
		else printf("操作失败：该工号不存在！\n");
	}
}

void insert(struct Worker* HeadNode)
{
	
	struct Worker* NewNode = (struct Worker*)malloc(sizeof(struct Worker));
	input(NewNode);
	if (!ListLength)
	{
		NewNode->next = HeadNode->next;
		HeadNode->next = NewNode;
		NewNode->prior = HeadNode;
	}
	else
	{
		struct Worker* CompareNode = HeadNode;
		bool flag = false;
		while (CompareNode->next != NULL)
		{
			CompareNode = CompareNode->next;
			if (NewNode->JobNumber < CompareNode->JobNumber)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			NewNode->prior = CompareNode->prior;
			NewNode->next = CompareNode;
			CompareNode->prior->next = NewNode;
			CompareNode->prior = NewNode;
		}
		else
		{
			NewNode->next = CompareNode->next;
			CompareNode->next = NewNode;
			NewNode->prior = CompareNode;
		}
	}
	ListLength++;
	rankSort(HeadNode);
	printf("操作成功：该工人信息已插入！具体如下：\n");
	printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
	printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
	struct Worker* Node = HeadNode;
	while (Node != NULL)
	{
		Node = Node->next;
		if (Node == NULL)break;
		printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
		printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay, Node->Rank);

	}
	printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
}

void del(struct Worker* HeadNode)
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		printf("请输入要删除工人的工号：");
		long JobNumberDel;
		scanf("%ld", &JobNumberDel);
		struct Worker* DelNode = HeadNode->next;
		bool flag = false;
		while (DelNode != NULL)
		{
			if (DelNode->JobNumber == JobNumberDel)
			{
				DelNode->prior->next = DelNode->next;
				if (DelNode->next != NULL)DelNode->next->prior = DelNode->prior;
				free(DelNode);
				flag = true;
				break;
			}
			DelNode = DelNode->next;
		}
		if (flag)
		{
			printf("操作成功：该工人数据已删除！\n");
			ListLength--;
			rankSort(HeadNode);
			printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
			printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
			struct Worker* Node = HeadNode;
			while (Node != NULL)
			{
				Node = Node->next;
				if (Node == NULL)break;
				printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
				printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay, Node->Rank);

			}
			printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
		}
		else printf("操作失败：未查找到对应工号！\n");
	}
}

void SubandPay(struct Worker* HeadNode)
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		struct Worker* Node = HeadNode;
		printf("每个工人的补贴与实发工资如下：\n");
		printf("┌─────────┬─────────┬─────────┬─────────┐\n");
		printf("│   工号  │   姓名  │   补贴  │ 实发工资│\n");
		while (Node->next != NULL)
		{
			Node = Node->next;
			if (Node == NULL)break;
			printf("├─────────┼─────────┼─────────┼─────────┤\n");
			printf("│%8ld │%8s │%8.2f │%9.2f│\n", Node->JobNumber, Node->Name, Node->Sub, Node->NetPay);
		}
		printf("└─────────┴─────────┴─────────┴─────────┘\n");
	}
}

void sum(struct Worker* HeadNode)
{
	float Sum_BasePay = 0;
	float Sum_Sub = 0;
	float Sum_Bonus = 0;
	float Sum_Charge = 0;
	float Sum_NetPay = 0;
	printf("基本工资、补贴、奖金、水电费、实发工资的总额如下：\n");
	printf("┌─────────┬─────────┬─────────┬─────────┬─────────┐\n");
	printf("│ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│\n");
	printf("├─────────┼─────────┼─────────┼─────────┼─────────┤\n");
	if (!ListLength);
	else
	{
		struct Worker* Node = HeadNode;
		while (Node->next != NULL)
		{
			Node = Node->next;
			if (Node == NULL)break;
			Sum_BasePay += Node->BasePay;
			Sum_Sub += Node->Sub;
			Sum_Bonus += Node->Bonus;
			Sum_Charge += Node->Charge;
			Sum_NetPay += Node->NetPay;
		}
	}
	printf("│%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│\n", Sum_BasePay, Sum_Sub, Sum_Bonus, Sum_Charge, Sum_NetPay);
	printf("└─────────┴─────────┴─────────┴─────────┴─────────┘\n");
}

void search_oldest(struct Worker* HeadNode)
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		struct Worker* Node = HeadNode;
		while (Node->next != NULL)
		{
			Node = Node->next;
			if (Node->Rank == 1 || Node == NULL)break;
		}
		printf("工龄最长的工人信息如下：\n");
		printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
		printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│\n");
		printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
		printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay);
		printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
	}
}

void display(struct Worker* HeadNode)
{
	struct Worker* Node;
	struct Worker* MarkNode = HeadNode;
	int Rest = ListLength;
	while (Rest)
	{
		int count;
		if (Rest == ListLength)
		{
			printf("┌───────");
			for (count = 0; count < Rest && count < 10; count++)printf("┬────────");
			printf("┐\n");
		}
		
		Node = MarkNode->next;
		if (Rest == ListLength)printf("│  工号 ");
		else printf("│   /   ");
		for (count = 0; count < Rest && count < 10; count++, Node = Node->next)printf("│%7ld ", Node->JobNumber);
		printf("│\n");
		
		printf("├───────");
		for (count = 0; count < Rest && count < 10; count++)printf("┼────────");
		printf("┤\n");
		
		Node = MarkNode->next;
		if (Rest == ListLength)printf("│  姓名 ");
		else printf("│   /   ");
		for (count = 0; count < Rest && count < 10; count++, MarkNode = Node, Node = Node->next)printf("│%7s ", Node->Name);
		printf("│\n");

		if (Rest > 10)
		{
			printf("├───────");
			for (count = 0; count <= Rest - 10 && count < 10; count++)printf("┼────────");
			for (; count < Rest && count < 10; count++)printf("┴────────");
			if (Rest - 20 > 0)printf("┤\n");
			else printf("┘\n");
		}
		else
		{
			printf("└───────");
			for (count = 0; count < Rest && count < 10; count++)printf("┴────────");
			printf("┘\n");
		}
		
		Rest = Rest - count;
	}	
}

void print(struct Worker* HeadNode)
{
	printf("-------------------------\n");
	printf("【在职工人名单】\n");
	display(HeadNode);
	printf("-------------------------\n");
	printf("[1]查询工人信息\n[2]插入新的工人信息\n[3]删除工人信息\n[4]每个工人的补贴与实发工资\n[5]基本工资、补贴、奖金、水电费、实发工资的总额\n[6]工龄最长的工人信息\n[7]退出程序\n");
	printf("-------------------------\n");
	printf("请选择您要执行的功能：");
}

bool judgement()
{
	char ch;
	int count = 0;
	while (1)
	{
		while ((ch = getchar()) != '\n');
		printf("\n请确认您的操作（[Y]是 [N]否）：");
		switch (ch = getchar())
		{
		case'Y':
		case'y':printf("----------------------------\n"); return true;
		case'N':
		case'n':return false;
		default:printf("操作失败：错误的选项！\n"); count++;
		}
		if (count == 5)
		{
			printf("\n连续的操作失败，即将返回主菜单！\n");
			printf("请按回车键继续...");
			return false;
		}
		printf("请按回车键继续...");
	}
}

void menu(struct Worker* HeadNode)
{
	char ch;
	while (true)
	{
		print(HeadNode);
		switch (ch = getchar())
		{
		case'1':printf("-------------------------"); if (judgement())search(HeadNode); break;
		case'2':printf("-------------------------"); if (judgement())insert(HeadNode); break;
		case'3':printf("-------------------------"); if (judgement())del(HeadNode); break;
		case'4':printf("-------------------------"); if (judgement())SubandPay(HeadNode); break;
		case'5':printf("-------------------------"); if (judgement())sum(HeadNode); break;
		case'6':printf("-------------------------"); if (judgement())search_oldest(HeadNode); break;
		case'7':printf("-------------------------"); if (judgement())return; break;
		default:printf("-------------------------"); printf("\n操作失败：错误的选项！\n");
		}
		while ((ch = getchar()) != '\n');
		printf("\n");
		system("pause");
		system("cls");
	}
}

int main()
{
	struct Worker* HeadNode;
	HeadNode = (struct Worker*)malloc(sizeof(struct Worker));
	HeadNode->next = NULL;
	load(HeadNode);
	menu(HeadNode);
	save(HeadNode);
	return 0;
}
