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
		printf("错误：文件打开失败！\n");
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
		printf("错误：文件打开失败！\n");
		return -1;
	}
    fwrite(&WorkerList, sizeof(struct Worker), ListLength, fp);
	fclose(fp);
}

void input(struct Worker *NewWorker)
{
	printf("请输入要插入的工人信息\n");
	printf("工号：");
	scanf("%ld", &NewWorker->JobNumber);
	printf("姓名：");
	scanf("%s", NewWorker->Name);
	printf("工龄：");
	scanf("%d", &NewWorker->WorkYear);
	printf("基本工资：");
	scanf("%f", &NewWorker->BasePay);
	printf("奖金：");
	scanf("%f", &NewWorker->Bonus);
	printf("水电费：");
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
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		printf("请输入要查找工人的工号：");
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
			printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
			printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
			printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
			printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
			printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
		}
		else printf("操作失败：该工号不存在！\n");
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
	printf("操作成功：该工人信息已插入！具体如下：\n");
	printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
	printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
	for (int i = 0; i < ListLength; i++)
	{
		printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
		printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
	}
	printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
}

void del()
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		printf("请输入要删除工人的工号：");
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
			printf("操作成功：该工人数据已删除！\n");
			ListLength--;
			rankSort();
			printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
			printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│ 工龄排名│\n");
			for (int i = 0; i < ListLength; i++)
			{
				printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
				printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│%8.2d │\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay, WorkerList[i].Rank);
			}
			printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
		}
		else printf("操作失败：未查找到对应工号！\n");
	}
}

void SubandPay()
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		printf("每个工人的补贴与实发工资如下：\n");
		printf("┌─────────┬─────────┬─────────┬─────────┐\n");
		printf("│   工号  │   姓名  │   补贴  │ 实发工资│\n");
		for (int i = 0; i < ListLength; i++)
		{
			printf("├─────────┼─────────┼─────────┼─────────┤\n");
			printf("│%8ld │%8s │%8.2f │%9.2f│\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].Sub, WorkerList[i].NetPay);
		}
		printf("└─────────┴─────────┴─────────┴─────────┘\n");
	}
}

void sum()
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
		for (int i = 0; i < ListLength; i++)
		{
			Sum_BasePay += WorkerList[i].BasePay;
			Sum_Sub += WorkerList[i].Sub;
			Sum_Bonus += WorkerList[i].Bonus;
			Sum_Charge += WorkerList[i].Charge;
			Sum_NetPay += WorkerList[i].NetPay;
		}
	}
	printf("│%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│\n", Sum_BasePay, Sum_Sub, Sum_Bonus, Sum_Charge, Sum_NetPay);
	printf("└─────────┴─────────┴─────────┴─────────┴─────────┘\n");
}

void search_oldest()
{
	if (!ListLength)printf("操作失败：目前系统中没有数据！\n");
	else
	{
		int i = 0;
		for (; i < ListLength; i++)
		{
			if (WorkerList[i].Rank == 1)break;
		}
		printf("工龄最长的工人信息如下：\n");
		printf("┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐\n");
		printf("│   工号  │   姓名  │   工龄  │ 基本工资│   补贴  │   奖金  │  水电费 │ 实发工资│\n");
		printf("├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤\n");
		printf("│%8ld │%8s │%6d   │%9.2f│%8.2f │%8.2f │%8.2f │%9.2f│\n", WorkerList[i].JobNumber, WorkerList[i].Name, WorkerList[i].WorkYear, WorkerList[i].BasePay, WorkerList[i].Sub, WorkerList[i].Bonus, WorkerList[i].Charge, WorkerList[i].NetPay);
		printf("└─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘\n");
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
			printf("┌───────");
			for (count = 0; count < Rest && count < 10; count++)printf("┬────────");
			printf("┐\n");
		}

		i = loop * 10;
		if (Rest == ListLength)printf("│  工号 ");
		else printf("│   /   ");
		for (count = 0; count < Rest && count < 10; count++, i++)printf("│%7ld ", WorkerList[i].JobNumber);
		printf("│\n");

		printf("├───────");
		for (count = 0; count < Rest && count < 10; count++)printf("┼────────");
		printf("┤\n");

		i = loop * 10;
		if (Rest == ListLength)printf("│  姓名 ");
		else printf("│   /   ");
		for (count = 0; count < Rest && count < 10; count++, i++)printf("│%7s ", WorkerList[i].Name);
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

void print()
{
	printf("-------------------------\n");
	printf("【在职工人名单】\n");
	display();
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
		default:printf("-------------------------"); printf("\n操作失败：错误的选项！\n请按回车键继续...");
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