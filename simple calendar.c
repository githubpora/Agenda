#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <process.h>

//�ж��Ƿ�Ϊ���꣬�ǵĻ�����true
int runnian(int year) 
{
	if(year%4==0&&year%100!=0||year%400==0)
		return 1;
	else
		return 0;
}

// ����ĳ�µ����� 
int day1(int year,int month)
{
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(runnian(year))
		a[1]=29;
	return a[month-1];
}

// ����ֵΪ�������Ǹ���ĵڼ���
int day2(int year,int month,int day) 
{
	int i,sum=0;
	for(i=1;i<month;i++)
	{
		sum+=day1(year,i);
	}
	sum+=day;
	return sum;
}

// �жϸ������ڼ� 
int week1(int year,int month,int day)
{
	int number=(year-1)+(year-1)/4-(year-1)/100+(year-1)/400+day2(year,month,day);
	number%=7;
	return number;
}


// ����������� 
void x2(int year,int month)
{
	int week,day,i; 
	printf("\t\t��Ԫ%d��\n",year);
	printf("\t\t��Ԫ%d��\n",month);
	printf("������\t����һ\t���ڶ�\t������\t������\t������\t������\n"); 
	day = day1(year,month); 
	week = week1(year,month,1); 
	for(i=1;i<=week;i++)
	{
		printf(" \t"); 
	}
	for(i=1;i<=day;i++) 
	{ 
		printf("%d",i);
		if((i+week)%7==0) printf("\n");
		else printf("\t");
	}
	int j = 1;
	for(j=1;j<=42-week-i;j++)
	{
		printf("\t");
	}
	printf("\n\n");
}

void x5(int year,int month,int da)
{
	int week,day,i; 
	printf("\t\t��Ԫ%d��\n",year);
	printf("\t\t��Ԫ%d��\n",month);
	printf("������\t����һ\t���ڶ�\t������\t������\t������\t������\n"); 
	day = day1(year,month); 
	week = week1(year,month,1); 
	for(i=1;i<=week;i++)
	{
		printf(" \t"); 
	}
	for(i=1;i<=day;i++) 
	{
		if (i == da) {
			printf("%d* ", i);
		} else {
			printf("%d",i);
		}
		if((i+week)%7==0) printf("\n");
		else printf("\t");
	}
	int j = 1;
	for(j=1;j<=42-week-i;j++)
	{
		printf("\t");
	}
	printf("\n\n");
}

void x1(int year,int month,int day)
{
	int number=week1(year,month,day);
	if(runnian(year))printf("����");
	else printf("ƽ��");
	printf("    %d   ��      %d    ��     %d    ��",year,month,day);
	switch(number)
	{
	case 0:
		printf("  ������ \n\n");
		break;
	case 1:
		printf("  ����һ \n\n");
		break;
	case 2:
		printf("  ���ڶ� \n\n");
		break;
	case 3:
		printf("  ������ \n\n");
		break;
	case 4:
		printf("  ������ \n\n");
		break;
	case 5:
		printf("  ������ \n\n");
		break;
	case 6:
		printf("  ������ \n\n");
		break;
	default:
		printf(" ���� \n\n");
		return; 
	}
	x5(year,month,day);
	 
}

// �ж������Ƿ�Ϸ� 
int x3(int year,int month,int day)
{ 
	if(year<0||month<1||month>12||day<1||day>day1(year,month))
		return 0;
	else
		return 1;
}
void nianli(int year)
{
	int i;
	printf("\n");
	if(runnian(year))printf("����");
	else printf("ƽ��");
	printf("  %d  �� \n\n",year);
	
	//������� 
	for(i=1;i<=12;i++)
	{
		x2(year,i);
		printf("\n");
	}
	printf("\n\n");
	 
}
void yueli(int year,int month)
{
	if(runnian(year))
		printf("����");
	else printf("ƽ��");
	printf("  %d  ��  %d  ��\n\n",year,month);
	x2(year,month);
}
void rili(int year,int month,int day)
{
	printf("\n");
	x1(year,month,day);
}


int main()
{
	int year,month,day,a,b;
	printf("\n\n\n\n");
	printf("               *********************************************************\n\n");
	printf("                              *                     *                   \n\n");
	printf("                                   ��ӭ����������                         \n");
	printf("                              *                     *                   \n\n");
	printf("               *********************************************************\n\n");
	
	SYSTEMTIME time;
	GetLocalTime(&time);//��ȡ��ǰϵͳ��ʱ��
	year=time.wYear;
	month=time.wMonth;
	day = time.wDay; 
	printf("�����ǹ�Ԫ%d��%d��%d��\n\n",time.wYear,time.wMonth,time.wDay);
	x5(year,month,day);
	while(1)
	{
		printf("\n\n\n\n");
		printf("               *********************************************************\n\n");
		printf("                              *                     *                   \n\n");
		printf("                                   ��ӭ����������                         \n");
		printf("                              *                     *                   \n\n");
		printf("               *********************************************************\n\n");
	
		printf(" 1������   2������  3������  4���˳�\n");
		printf("���������ѡ��<1~4>,���س���ȷ��:");
		scanf("%d",&b);
		switch(b)
		{
		case 1:printf("��������Ҫ������:");
			scanf("%d",&year);
			a=x3(year,1,1);
			if(a==0)
			{
				printf("���������������롣\n");
				break;
			}
			nianli(year);
			break;
		case 2:printf("\n��������Ҫ�������£�����֮���ÿո����:");
			scanf("%d%d",&year,&month);
			a=x3(year,month,1);
			if(a==0)
			{
				printf("���������������롣\n");
				break;

			}
			yueli(year,month);
			break;
		case 3:printf("\n��������Ҫ��������գ�������֮���ÿո������");
			scanf("%d%d%d",&year,&month,&day);
			a=x3(year,month,day);
			if(a==0)
			{
				printf("���������������롣\n");
				break;
			}
			rili(year,month,day);
			break;
		case 4:exit(0);
		default:printf("���������������롣\n\n");
		}
	}
}
