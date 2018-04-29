#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <process.h>

//判断是否为闰年，是的话返回true
int runnian(int year) 
{
	if(year%4==0&&year%100!=0||year%400==0)
		return 1;
	else
		return 0;
}

// 返回某月的天数 
int day1(int year,int month)
{
	int a[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	if(runnian(year))
		a[1]=29;
	return a[month-1];
}

// 返回值为该日期是该年的第几天
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

// 判断该天星期几 
int week1(int year,int month,int day)
{
	int number=(year-1)+(year-1)/4-(year-1)/100+(year-1)/400+day2(year,month,day);
	number%=7;
	return number;
}


// 输出本月日历 
void x2(int year,int month)
{
	int week,day,i; 
	printf("\t\t公元%d年\n",year);
	printf("\t\t公元%d月\n",month);
	printf("星期日\t星期一\t星期二\t星期三\t星期四\t星期五\t星期六\n"); 
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
	printf("\t\t公元%d年\n",year);
	printf("\t\t公元%d月\n",month);
	printf("星期日\t星期一\t星期二\t星期三\t星期四\t星期五\t星期六\n"); 
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
	if(runnian(year))printf("闰年");
	else printf("平年");
	printf("    %d   年      %d    月     %d    日",year,month,day);
	switch(number)
	{
	case 0:
		printf("  星期日 \n\n");
		break;
	case 1:
		printf("  星期一 \n\n");
		break;
	case 2:
		printf("  星期二 \n\n");
		break;
	case 3:
		printf("  星期三 \n\n");
		break;
	case 4:
		printf("  星期四 \n\n");
		break;
	case 5:
		printf("  星期五 \n\n");
		break;
	case 6:
		printf("  星期六 \n\n");
		break;
	default:
		printf(" 错误 \n\n");
		return; 
	}
	x5(year,month,day);
	 
}

// 判断日期是否合法 
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
	if(runnian(year))printf("闰年");
	else printf("平年");
	printf("  %d  年 \n\n",year);
	
	//输出年历 
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
		printf("闰年");
	else printf("平年");
	printf("  %d  年  %d  月\n\n",year,month);
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
	printf("                                   欢迎进入万年历                         \n");
	printf("                              *                     *                   \n\n");
	printf("               *********************************************************\n\n");
	
	SYSTEMTIME time;
	GetLocalTime(&time);//获取当前系统的时间
	year=time.wYear;
	month=time.wMonth;
	day = time.wDay; 
	printf("今天是公元%d年%d月%d日\n\n",time.wYear,time.wMonth,time.wDay);
	x5(year,month,day);
	while(1)
	{
		printf("\n\n\n\n");
		printf("               *********************************************************\n\n");
		printf("                              *                     *                   \n\n");
		printf("                                   欢迎进入万年历                         \n");
		printf("                              *                     *                   \n\n");
		printf("               *********************************************************\n\n");
	
		printf(" 1、年历   2、月历  3、日历  4、退出\n");
		printf("请输出您的选择<1~4>,按回车键确定:");
		scanf("%d",&b);
		switch(b)
		{
		case 1:printf("请输入您要查的年份:");
			scanf("%d",&year);
			a=x3(year,1,1);
			if(a==0)
			{
				printf("错误！请您重新输入。\n");
				break;
			}
			nianli(year);
			break;
		case 2:printf("\n请输入您要查的年和月，年月之间用空格隔开:");
			scanf("%d%d",&year,&month);
			a=x3(year,month,1);
			if(a==0)
			{
				printf("错误！请您重新输入。\n");
				break;

			}
			yueli(year,month);
			break;
		case 3:printf("\n请您输入要查的年月日，年月日之间用空格隔开：");
			scanf("%d%d%d",&year,&month,&day);
			a=x3(year,month,day);
			if(a==0)
			{
				printf("错误！请您重新输入。\n");
				break;
			}
			rili(year,month,day);
			break;
		case 4:exit(0);
		default:printf("错误！请您重新输入。\n\n");
		}
	}
}
