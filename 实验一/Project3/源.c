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
		printf("�����ļ���ʧ�ܣ�\n");
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
		printf("�����ļ���ʧ�ܣ�\n");
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
	printf("������Ҫ����Ĺ�����Ϣ\n");
	printf("���ţ�");
	scanf("%ld", &NewNode->JobNumber);
	printf("������");
	scanf("%s", NewNode->Name);
	printf("���䣺");
	scanf("%d", &NewNode->WorkYear);
	printf("�������ʣ�");
	scanf("%f", &NewNode->BasePay);
	printf("����");
	scanf("%f", &NewNode->Bonus);
	printf("ˮ��ѣ�");
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
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		printf("������Ҫ���ҹ��˵Ĺ��ţ�");
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
			printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
			printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
			printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
			printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", SearchNode->JobNumber, SearchNode->Name, SearchNode->WorkYear, SearchNode->BasePay, SearchNode->Sub, SearchNode->Bonus, SearchNode->Charge, SearchNode->NetPay, SearchNode->Rank);
			printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
		}
		else printf("����ʧ�ܣ��ù��Ų����ڣ�\n");
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
	printf("�����ɹ����ù�����Ϣ�Ѳ��룡�������£�\n");
	printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
	printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
	struct Worker* Node = HeadNode;
	while (Node != NULL)
	{
		Node = Node->next;
		if (Node == NULL)break;
		printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
		printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay, Node->Rank);

	}
	printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
}

void del(struct Worker* HeadNode)
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		printf("������Ҫɾ�����˵Ĺ��ţ�");
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
			printf("�����ɹ����ù���������ɾ����\n");
			ListLength--;
			rankSort(HeadNode);
			printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
			printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
			struct Worker* Node = HeadNode;
			while (Node != NULL)
			{
				Node = Node->next;
				if (Node == NULL)break;
				printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
				printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay, Node->Rank);

			}
			printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
		}
		else printf("����ʧ�ܣ�δ���ҵ���Ӧ���ţ�\n");
	}
}

void SubandPay(struct Worker* HeadNode)
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		struct Worker* Node = HeadNode;
		printf("ÿ�����˵Ĳ�����ʵ���������£�\n");
		printf("���������������������Щ������������������Щ������������������Щ�������������������\n");
		printf("��   ����  ��   ����  ��   ����  �� ʵ�����ʩ�\n");
		while (Node->next != NULL)
		{
			Node = Node->next;
			if (Node == NULL)break;
			printf("���������������������੤�����������������੤�����������������੤������������������\n");
			printf("��%8ld ��%8s ��%8.2f ��%9.2f��\n", Node->JobNumber, Node->Name, Node->Sub, Node->NetPay);
		}
		printf("���������������������ة������������������ة������������������ة�������������������\n");
	}
}

void sum(struct Worker* HeadNode)
{
	float Sum_BasePay = 0;
	float Sum_Sub = 0;
	float Sum_Bonus = 0;
	float Sum_Charge = 0;
	float Sum_NetPay = 0;
	printf("�������ʡ�����������ˮ��ѡ�ʵ�����ʵ��ܶ����£�\n");
	printf("���������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
	printf("�� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ�\n");
	printf("���������������������੤�����������������੤�����������������੤�����������������੤������������������\n");
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
	printf("��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��\n", Sum_BasePay, Sum_Sub, Sum_Bonus, Sum_Charge, Sum_NetPay);
	printf("���������������������ة������������������ة������������������ة������������������ة�������������������\n");
}

void search_oldest(struct Worker* HeadNode)
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		struct Worker* Node = HeadNode;
		while (Node->next != NULL)
		{
			Node = Node->next;
			if (Node->Rank == 1 || Node == NULL)break;
		}
		printf("������Ĺ�����Ϣ���£�\n");
		printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
		printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ�\n");
		printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
		printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��\n", Node->JobNumber, Node->Name, Node->WorkYear, Node->BasePay, Node->Sub, Node->Bonus, Node->Charge, Node->NetPay);
		printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
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
			printf("����������������");
			for (count = 0; count < Rest && count < 10; count++)printf("�Щ���������������");
			printf("��\n");
		}
		
		Node = MarkNode->next;
		if (Rest == ListLength)printf("��  ���� ");
		else printf("��   /   ");
		for (count = 0; count < Rest && count < 10; count++, Node = Node->next)printf("��%7ld ", Node->JobNumber);
		printf("��\n");
		
		printf("����������������");
		for (count = 0; count < Rest && count < 10; count++)printf("�੤��������������");
		printf("��\n");
		
		Node = MarkNode->next;
		if (Rest == ListLength)printf("��  ���� ");
		else printf("��   /   ");
		for (count = 0; count < Rest && count < 10; count++, MarkNode = Node, Node = Node->next)printf("��%7s ", Node->Name);
		printf("��\n");

		if (Rest > 10)
		{
			printf("����������������");
			for (count = 0; count <= Rest - 10 && count < 10; count++)printf("�੤��������������");
			for (; count < Rest && count < 10; count++)printf("�ة���������������");
			if (Rest - 20 > 0)printf("��\n");
			else printf("��\n");
		}
		else
		{
			printf("����������������");
			for (count = 0; count < Rest && count < 10; count++)printf("�ة���������������");
			printf("��\n");
		}
		
		Rest = Rest - count;
	}	
}

void print(struct Worker* HeadNode)
{
	printf("-------------------------\n");
	printf("����ְ����������\n");
	display(HeadNode);
	printf("-------------------------\n");
	printf("[1]��ѯ������Ϣ\n[2]�����µĹ�����Ϣ\n[3]ɾ��������Ϣ\n[4]ÿ�����˵Ĳ�����ʵ������\n[5]�������ʡ�����������ˮ��ѡ�ʵ�����ʵ��ܶ�\n[6]������Ĺ�����Ϣ\n[7]�˳�����\n");
	printf("-------------------------\n");
	printf("��ѡ����Ҫִ�еĹ��ܣ�");
}

bool judgement()
{
	char ch;
	int count = 0;
	while (1)
	{
		while ((ch = getchar()) != '\n');
		printf("\n��ȷ�����Ĳ�����[Y]�� [N]�񣩣�");
		switch (ch = getchar())
		{
		case'Y':
		case'y':printf("----------------------------\n"); return true;
		case'N':
		case'n':return false;
		default:printf("����ʧ�ܣ������ѡ�\n"); count++;
		}
		if (count == 5)
		{
			printf("\n�����Ĳ���ʧ�ܣ������������˵���\n");
			printf("�밴�س�������...");
			return false;
		}
		printf("�밴�س�������...");
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
		default:printf("-------------------------"); printf("\n����ʧ�ܣ������ѡ�\n");
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
