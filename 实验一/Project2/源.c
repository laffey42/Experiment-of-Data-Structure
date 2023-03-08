#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>

int ListLength = 0;

struct Worker{
	long JobNumber;
	char Name[20];
	int WorkYear;
	float BasePay;
	float Sub;
	float Bonus;
	float Charge;
	float NetPay;
	int Rank;
}WorkerList[100];

void copy(struct Worker *List01, struct Worker *List02)
{
	List01->JobNumber = List02->JobNumber;
	strcpy(List01->Name, List02->Name);
	List01->WorkYear = List02->WorkYear;
	List01->BasePay = List02->BasePay;
	List01->Sub = List02->Sub;
	List01->Bonus = List02->Bonus;
	List01->Charge = List02->Charge;
	List01->NetPay = List02->NetPay;
	List01->Rank = List02->Rank;

}

void pushback(int i)
{
	for (int j = ListLength; i < j; j--)
	{
		copy(&WorkerList[j], &WorkerList[j - 1]);
	}
}

void pushfoward(int i)
{
	while (i < ListLength)
	{
		copy(&WorkerList[i], &WorkerList[i + 1]);
		i++;
	}
}

void load()
{
	FILE* fp;
	fp = fopen("D:\\test\\data\\test_01", "rb");
	if (!fp)
	{
		printf("�����ļ���ʧ�ܣ�\n");
		return -1;
	}
	while (!feof(fp))
	{
		fread(&WorkerList[ListLength], sizeof(struct Worker), 1, fp);
		if(!feof(fp))ListLength++;
	}
	fclose(fp);
}

void save()
{
	FILE* fp;
	fp = fopen("D:\\test\\data\\test_01", "wb");
	if (!fp)
	{
		printf("�����ļ���ʧ�ܣ�\n");
		return -1;
	}
    fwrite(&WorkerList, sizeof(struct Worker), ListLength, fp);
	fclose(fp);
}

void input(struct Worker *NewWorker)
{
	printf("������Ҫ����Ĺ�����Ϣ\n");
	printf("���ţ�");
	scanf("%ld", &NewWorker->JobNumber);
	printf("������");
	scanf("%s", NewWorker->Name);
	printf("���䣺");
	scanf("%d", &NewWorker->WorkYear);
	printf("�������ʣ�");
	scanf("%f", &NewWorker->BasePay);
	printf("����");
	scanf("%f", &NewWorker->Bonus);
	printf("ˮ��ѣ�");
	scanf("%f", &NewWorker->Charge);
	NewWorker->Sub = NewWorker->WorkYear * 200;
	NewWorker->NetPay = NewWorker->BasePay + NewWorker->Sub + NewWorker->Bonus - NewWorker->Charge;
	NewWorker->Rank = 0;
}

void rankSort()
{
	int RankMark[100][2];
	for (int i = 0; i < ListLength; i++)
	{
		RankMark[i][0] = i;
		RankMark[i][1] = WorkerList[i].WorkYear;
	}
	for (int i = 0; i < ListLength; i++)
	{
		int Max = RankMark[i][1];
		int Mark = i;
		for (int j = i + 1; j < ListLength; j++)
		{
			if (RankMark[j][1] > Max)
			{
				Max = RankMark[j][1];
				Mark = j;
			}
		}
		int Temp = RankMark[i][0];
		RankMark[i][0] = RankMark[Mark][0];
		RankMark[Mark][0] = Temp;
		Temp = RankMark[i][1];
		RankMark[i][1] = RankMark[Mark][1];
		RankMark[Mark][1] = Temp;
	}
	for (int i = 0; i < ListLength; i++)
	{
		WorkerList[RankMark[i][0]].Rank = i + 1;
	}
}

void search()
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		printf("������Ҫ���ҹ��˵Ĺ��ţ�");
		long InputJobNumber;
		scanf("%ld", &InputJobNumber);
		bool flag = false;
		int i = 0;
		while (i < ListLength)
		{
			if (WorkerList[i].JobNumber == InputJobNumber)
			{
				flag = true;
				break;
			}
			i++;
		}
		if (flag)
		{
			printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
			printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
			printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
			printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
			printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
		}
		else printf("����ʧ�ܣ��ù��Ų����ڣ�\n");
	}
}

void insert()
{
	struct Worker NewWorker;
	input(&NewWorker);
	if (!ListLength)
	{
		copy(&WorkerList[0], &NewWorker);
	}
	else
	{
		int i = 0;
		for (; i < ListLength; i++)
		{
			if (NewWorker.JobNumber < WorkerList[i].JobNumber)
			{
				pushback(i);
				break;
			}
		}
		copy(&WorkerList[i], &NewWorker);
	}
	ListLength++;
	rankSort();
	printf("�����ɹ����ù�����Ϣ�Ѳ��룡�������£�\n");
	printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
	printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
	for (int i = 0; i < ListLength; i++)
	{
		printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
		printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
	}
	printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
}

void del()
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		printf("������Ҫɾ�����˵Ĺ��ţ�");
		long JobNumberDel;
		scanf("%ld", &JobNumberDel);
		bool flag = false;
		for (int i = 0; i < ListLength; i++)
		{
			if (WorkerList[i].JobNumber == JobNumberDel)
			{
				pushfoward(i);
				flag = true;
				break;
			}
		}
		if (flag)
		{
			printf("�����ɹ����ù���������ɾ����\n");
			ListLength--;
			rankSort();
			printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
			printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ� ����������\n");
			for (int i = 0; i < ListLength; i++)
			{
				printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
				printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��%8.2d ��\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
			}
			printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
		}
		else printf("����ʧ�ܣ�δ���ҵ���Ӧ���ţ�\n");
	}
}

void SubandPay()
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		printf("ÿ�����˵Ĳ�����ʵ���������£�\n");
		printf("���������������������Щ������������������Щ������������������Щ�������������������\n");
		printf("��   ����  ��   ����  ��   ����  �� ʵ�����ʩ�\n");
		for (int i = 0; i < ListLength; i++)
		{
			printf("���������������������੤�����������������੤�����������������੤������������������\n");
			printf("��%8ld ��%8s ��%8.2f ��%9.2f��\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].Sub, WorkerList[i].NetPay);
		}
		printf("���������������������ة������������������ة������������������ة�������������������\n");
	}
}

void sum()
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
		for (int i = 0; i < ListLength; i++)
		{
			Sum_BasePay += WorkerList[i].BasePay;
			Sum_Sub += WorkerList[i].Sub;
			Sum_Bonus += WorkerList[i].Bonus;
			Sum_Charge += WorkerList[i].Charge;
			Sum_NetPay += WorkerList[i].NetPay;
		}
	}
	printf("��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��\n", Sum_BasePay, Sum_Sub, Sum_Bonus, Sum_Charge, Sum_NetPay);
	printf("���������������������ة������������������ة������������������ة������������������ة�������������������\n");
}

void search_oldest()
{
	if (!ListLength)printf("����ʧ�ܣ�Ŀǰϵͳ��û�����ݣ�\n");
	else
	{
		int i = 0;
		for (; i < ListLength; i++)
		{
			if (WorkerList[i].Rank == 1)break;
		}
		printf("������Ĺ�����Ϣ���£�\n");
		printf("���������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ������������������Щ�������������������\n");
		printf("��   ����  ��   ����  ��   ����  �� �������ʩ�   ����  ��   ����  ��  ˮ��� �� ʵ�����ʩ�\n");
		printf("���������������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤�����������������੤������������������\n");
		printf("��%8ld ��%8s ��%6d   ��%9.2f��%8.2f ��%8.2f ��%8.2f ��%9.2f��\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay);
		printf("���������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة������������������ة�������������������\n");
	}
}

void display()
{
	int Rest = ListLength;
	while (Rest)
	{
		int count, i;
		int loop = (ListLength - Rest) / 10;
		if (Rest == ListLength)
		{
			printf("����������������");
			for (count = 0; count < Rest && count < 10; count++)printf("�Щ���������������");
			printf("��\n");
		}

		i = loop * 10;
		if (Rest == ListLength)printf("��  ���� ");
		else printf("��   /   ");
		for (count = 0; count < Rest && count < 10; count++, i++)printf("��%7ld ", WorkerList[i].JobNumber);
		printf("��\n");

		printf("����������������");
		for (count = 0; count < Rest && count < 10; count++)printf("�੤��������������");
		printf("��\n");

		i = loop * 10;
		if (Rest == ListLength)printf("��  ���� ");
		else printf("��   /   ");
		for (count = 0; count < Rest && count < 10; count++, i++)printf("��%7s ", WorkerList[i].Name);
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

void print()
{
	printf("-------------------------\n");
	printf("����ְ����������\n");
	display();
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

void menu()
{
	char ch;
	while (true)
	{
		print();
		switch (ch = getchar())
		{
		case'1':printf("-------------------------");	if (judgement())search(); break;
		case'2':printf("-------------------------"); 	if (judgement())insert(); break;
		case'3':printf("-------------------------"); 	if (judgement())del(); break;
		case'4':printf("-------------------------");	if (judgement())SubandPay(); break;
		case'5':printf("-------------------------"); 	if (judgement())sum(); break;
		case'6':printf("-------------------------"); 	if (judgement())search_oldest(); break;
		case'7':printf("-------------------------"); 	if (judgement())return; break;
		default:printf("-------------------------"); printf("\n����ʧ�ܣ������ѡ�\n�밴�س�������...");
		}
		while ((ch = getchar()) != '\n');
		printf("\n");
		system("pause");
		system("cls");
	}
}

int main()
{
	load();
	menu();
	save();
	return 0;
}