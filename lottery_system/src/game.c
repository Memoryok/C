#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"common.h"
#include"game.h"

/*
	功能：小游戏界面控制
	参数：无
	返回值：无
*/
void game_interface_hander(void)
{
	int flag=1;
	while(flag)
	{
		int choose=game_interface();	//调用小游戏界面接口
		switch(choose)
		{
			case 1:		//掷骰子小游戏
				size_leopard();
				break;
			case 2:		//猜拳小游戏
				guess_finger();
				break;
			case 3:		//猜数字小游戏
				guess_number();
				break;
			case 0:		//返回上一级菜单
				flag=0;
				break;
			default:
				CONTINUE("输入有误,请重新输入!\n");
				break;
		}
	}
}

/*
	功能：小游戏界面接口
	参数：无
	返回值：操作选项
*/
int game_interface(void)
{
	system("clear");
	printf("\t*************************\n");
	printf("\t*   欢迎进入小游戏界面\t*\n");
	printf("\t*************************\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    1.掷骰子小游戏\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    2.猜拳小游戏\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    3.猜数字小游戏\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    0.返回上一级菜单\t*\n");
	printf("\t*************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);
		
	//清理缓存
	FLUSH;
	return choose;
}

/*
	功能：大小豹子
	参数：无
	返回值：无
*/
void size_leopard(void)
{
	int choose1=0,choose2=0;
	int a=0,b=0,c=0;
	int sum=0;
	srand(time(NULL));
	printf(">>>欢迎来到掷骰子游戏<<<\n");
	printf("掷骰子游戏规则:\n");
	printf("共三个骰子,点数在1-10之间为小,点数在11-18之间为大,三个骰子点数相同为豹子\n");
	printf("1.大\t2.小\t3.豹子\n");
	while(1)
	{
		printf("请您选择:");
		scanf("%d",&choose1);
		a=rand()%6+1;
		b=rand()%6+1;
		c=rand()%6+1;
		sum=a+b+c;
		int flag=1;
		if(choose1==1)
		{
			printf("****************\n");
			printf("第一个点数:%d\n第二个点数:%d\n第三个点数:%d\n总点数:%d\n",a,b,c,sum);
			if(sum>=11 && (a!=b || a!=c || b!=c))
			{
				printf("你赢了!\n");
			}
			else
			{
				printf("你输了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else if(choose1==2)
		{
			printf("****************\n");
			printf("第一个点数:%d\n第二个点数:%d\n第三个点数:%d\n总点数:%d\n",a,b,c,sum);
			if(sum<=10 && (a!=b || a!=c || b!=c))
			{
				printf("你赢了!\n");
			}
			else
			{
				printf("你输了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else if(choose1==3)
		{
			printf("****************\n");
			printf("第一个点数:%d\n第二个点数:%d\n第三个点数:%d\n总点数:%d\n",a,b,c,sum);
			if(a==b && b==c && a==c)
			{
				printf("你赢了!\n");
			}
			else
			{
				printf("你输了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else
		{
			printf("输入有误,请重新选择!\n");
		}
	}
}

/*
	功能：猜拳
	参数：无
	返回值：无
*/
void guess_finger(void)
{
	int choose1=0,choose2=0;
	int num=0;
	srand(time(NULL));
	printf(">>>欢迎来到猜拳游戏<<<\n");
	printf("猜拳游戏规则:\n");
	printf("1.剪刀\t2.石头\t3.布\n");
	while(1)
	{
		printf("请您选择:");
		scanf("%d",&choose1);
		num=rand()%3+1;
		int flag=1;
		if(choose1==1)
		{
			printf("****************\n");
			if(1-num==-2)
			{
				printf("电脑:布\n");
				printf("你:剪刀\n");
				printf("你赢了!\n");
			}
			else if(1-num==-1)
			{
				printf("电脑:石头\n");
				printf("你:剪刀\n");
				printf("你输了!\n");
			}
			else if(1-num==0)
			{
				printf("电脑:剪刀\n");
				printf("你:剪刀\n");
				printf("平局了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else if(choose1==2)
		{
			printf("****************\n");
			if(2-num==1)
			{
				printf("电脑:剪刀\n");
				printf("你:石头\n");
				printf("你赢了!\n");
			}
			else if(2-num==-1)
			{
				printf("电脑:布\n");
				printf("你:石头\n");
				printf("你输了!\n");
			}
			else if(2-num==0)
			{
				printf("电脑:石头\n");
				printf("你:石头\n");
				printf("平局了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else if(choose1==3)
		{
			printf("****************\n");
			if(3-num==1)
			{
				printf("电脑:石头\n");
				printf("你:布\n");
				printf("你赢了!\n");
			}
			else if(3-num==2)
			{
				printf("电脑:剪刀\n");
				printf("你:布\n");
				printf("你输了!\n");
			}
			else if(3-num==0)
			{
				printf("电脑:布\n");
				printf("你:布\n");
				printf("平局了!\n");
			}
			printf("****************\n");
			printf("是否继续?\n");
			printf("1.继续\t2.退出\n");
			while(flag)
			{
				scanf("%d",&choose2);
				if(choose2==1)
				{
					flag=0;
				}
				else if(choose2==2)
				{
					return ;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
		}
		else
		{
			printf("输入有误,请重新选择!\n");
		}
	}
}

/*
	功能：猜数字
	参数：无
	返回值：无
*/
void guess_number(void)
{
	int number=0;
	int num=0;
	int choose=0;
	srand(time(NULL));
	printf(">>>欢迎来到猜数字游戏<<<\n");
	printf("猜数字游戏规则:\n");
	printf("在1-100之间选择1个数字,和电脑随机生成的数字进行匹配,只有5次机会!\n");
	while(1)
	{
		number=rand()%100+1;
		int flag=1;
		int i=0;
		for(i=0;i<5;i++)	//5次机会
		{
			flag=1;
			while(flag)
			{
				printf("请输入你要猜的数字:");
				scanf("%d",&num);
				if(num<1 || num>100)
				{
					printf("输入有误,请重新输入!\n");
				}
				else
				{
					flag=0;
				}
			}
			if(num==number)
			{
				printf("你猜到第%d次,就猜对了!\n",i+1);
				break;
			}
			else
			{
				if(num<number)
				{
					printf("猜小了,这是你第%d次猜!\n",i+1);
				}
				else
				{
					printf("猜大了,这是你第%d次猜!\n",i+1);
				}
			}
		}
		if(i==5 && num!=number)
		{
			printf("你猜了5次,还没有猜出来,正确答案是%d\n",number);
		}
		printf("游戏结束!\n");
		printf("****************\n");
		printf("是否继续?\n");
		printf("1.继续\t2.退出\n");
		flag=1;
		while(flag)
		{
			scanf("%d",&choose);
			if(choose==1)
			{
				flag=0;
			}
			else if(choose==2)
			{
				return ;
			}
			else
			{
				printf("输入有误,请重新输入!\n");
			}
		}
	}
}







