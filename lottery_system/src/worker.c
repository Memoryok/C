#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"worker.h"
#include"common.h"

/*
	功能：公证员登录
	参数：无
	返回值：0 成功 -1 失败
*/
int worker_login(void)
{
	int count=3;
	char worker_name[LEN_NAME]={'\0'};
	char worker_pwd[LEN_PWD]={'\0'};
	while(count)
	{
		printf("请输入公证员账号:");
		fgets(worker_name,LEN_NAME,stdin);
		if(worker_name[strlen(worker_name)-1]=='\n')
		{
			worker_name[strlen(worker_name)-1]='\0';
		}
		else
		{
			FLUSH;
		}
		if(strcmp(worker_name,WORKER_NAME)==0)
		{
			while(count)
			{
				printf("请输入公证员密码:");
				getPassword(worker_pwd);
				if(strcmp(worker_pwd,WORKER_PWD)==0)
				{
					//验证码
					return validata_code();
				}
				else
				{
					count--;
					printf("输入有误,你还有%d次机会,请重新输入!\n",count);
				}
			}
		}
		else
		{
			count--;
			printf("输入有误,你还有%d次机会,请重新输入!\n",count);
		}
	}
	return -1;
}

/*
	功能：开奖
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int open_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head || NULL==user_lottery_head || NULL==issue_head)
	{
		return -1;
	}
	char pwd[LEN_PWD]={'\0'};
	printf("请输入公证员密码进行确认:");
	getPassword(pwd);
	if(strcmp(pwd,WORKER_PWD)==0)
	{
		if(NULL==issue_head->first)
		{
			printf("彩票还未发行,暂时还不能开奖!\n");
			return -1;
		}

		issue_node_t* p_issue=issue_head->first;
		while(p_issue->next!=NULL)
		{
			p_issue=p_issue->next;	//遍历到彩票链表最新一期
		}
		if(p_issue->data.prize_state==1)	//0未开奖 1已开奖
		{
			printf("当期彩票已经开奖,不能重复开奖!\n");
			return -1;
		}
		else if(p_issue->data.total_lottery==0)
		{
			printf("当前彩票没有售出,不能开奖!\n");
			return -1;
		}
		else
		{
			int flag=1;
			int choose=0;
			while(flag)
			{
				printf("\t**********\n");
				printf("\t1.自动开奖\n");
				printf("\t2.手动开奖\n");
				printf("\t**********\n");
				printf("请选择:");
				scanf("%d",&choose);
				if(choose==1)
				{
					int i=0;
					srand(time(NULL));
					for(i=0;i<7;i++)
					{
						p_issue->data.winning_number[i]=rand()%33+1;	//自动生成1-33中奖号码
					}
					flag=0;
				}
				else if(choose==2)
				{
					printf("请输入中奖号码:");
					int i=0;
					for(i=0;i<7;i++)
					{
						scanf("%d",&p_issue->data.winning_number[i]);	//手动输入中奖号码
					}
					flag=0;
				}
				else
				{
					printf("输入有误,请重新输入!\n");
				}
			}
			p_issue->data.prize_state=1;	//开奖状态改为 1 已开奖
			//调用兑奖函数
			return exchange_lottery(user_head,user_lottery_head,issue_head);
		}
	}
	else
	{
		printf("密码错误,你不是公证员不能进行此操作!\n");
		return -1;
	}
}

/*
	功能：兑奖
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int exchange_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head || NULL==user_lottery_head || NULL==issue_head)
	{
		return -1;
	}
	
	issue_node_t* p_issue=issue_head->first;
	user_node_t* p_user=user_head->first;
	user_lottery_node_t* p_lottery=user_lottery_head->first;
	
	while(p_issue->next!=NULL)		//遍历每期彩票链表,查找到最新的一期
	{
		p_issue=p_issue->next;
	}
	while(p_lottery!=NULL)		//遍历用户彩票链表
	{
		if(p_lottery->data.phase_id==p_issue->data.phase_id)		//筛选用户的期号与最新的一期进行匹配
		{
			int i=0,j=0;
			int count[5]={0};	//定义一个数组存放每一注中的球数
			for(i=0;i<p_lottery->data.lottery_number;i++)	//外循环次数是注数
			{
				for(j=0;j<7;j++)	//内循环次数是7个球
				{
					if(p_lottery->data.select_id[i][j]==p_issue->data.winning_number[j])	//和中奖的号码对比
					{
						count[i]++;		//相同加1
					}
				}
			}
			//写一个排序,返回用户每张彩票注数中的最多的一个值
			int count_max=bubble_sort(count,p_lottery->data.lottery_number);
			switch(count_max)
			{
				case 7:				//一等奖
					p_lottery->data.winning_status=1;
					p_lottery->data.winning_money=5000;		//一等奖5000元
					//奖池余额
					p_issue->data.total_money=p_issue->data.total_money-p_lottery->data.winning_money; 
					while(p_user!=NULL)
					{
						if(strcmp(p_user->data.user_name,p_lottery->data.user_name)==0)
						{
							p_user->data.money=p_user->data.money+p_lottery->data.winning_money;	//用户余额
						}
						p_user=p_user->next;
					}
					break;
				case 6:				//二等奖
					p_lottery->data.winning_status=2;
					p_lottery->data.winning_money=3000;		//二等奖3000元
					//奖池余额
					p_issue->data.total_money=p_issue->data.total_money-p_lottery->data.winning_money;
					while(p_user!=NULL)
					{
						if(strcmp(p_user->data.user_name,p_lottery->data.user_name)==0)
						{
							p_user->data.money=p_user->data.money+p_lottery->data.winning_money;	//用户余额
						}
						p_user=p_user->next;
					}
					break;
				case 5:				//三等奖
					p_lottery->data.winning_status=3;
					p_lottery->data.winning_money=1000;		//三等奖1000元
					//奖池余额
					p_issue->data.total_money=p_issue->data.total_money-p_lottery->data.winning_money;
					while(p_user!=NULL)
					{
						if(strcmp(p_user->data.user_name,p_lottery->data.user_name)==0)
						{
							p_user->data.money=p_user->data.money+p_lottery->data.winning_money;	//用户余额
						}
						p_user=p_user->next;
					}
					break;
				case 4:case 3:		//四等奖
					p_lottery->data.winning_status=4;
					p_lottery->data.winning_money=100;		//四等奖100元
					//奖池余额
					p_issue->data.total_money=p_issue->data.total_money-p_lottery->data.winning_money;
					while(p_user!=NULL)
					{
						if(strcmp(p_user->data.user_name,p_lottery->data.user_name)==0)
						{
							p_user->data.money=p_user->data.money+p_lottery->data.winning_money;	//用户余额
						}
						p_user=p_user->next;
					}
					break;
				case 2:		//五等奖
					p_lottery->data.winning_status=5;
					p_lottery->data.winning_money=50;		//五等奖50元
					//奖池余额
					p_issue->data.total_money=p_issue->data.total_money-p_lottery->data.winning_money;
					while(p_user!=NULL)
					{
						if(strcmp(p_user->data.user_name,p_lottery->data.user_name)==0)
						{
							p_user->data.money=p_user->data.money+p_lottery->data.winning_money;	//用户余额
						}
						p_user=p_user->next;
					}
					break;
				default:			//未中奖
					break;
	
			}
		}
		p_lottery=p_lottery->next;
	}
	return 0;
}

/*
	功能：数组排序（冒泡排序）
	参数：ary 数组地址	len 数组长度
	返回值：数组元素最大值
*/
int bubble_sort(int *ary,int len)
{
	int i=0,j=0;
	for(i=0;i<len-1;i++)
	{
		for(j=0;j<len-1-i;j++)
		{
			if(ary[j]<ary[j+1])
			{
				int temp=ary[j];
				ary[j]=ary[j+1];
				ary[j+1]=temp;
			}
		}
	}
	return ary[0];
}

/*
	功能：查看历史发行
	参数：issue_head 每期彩票头节点
	返回值：无
*/
void look_history_issue_lottery(issue_head_t* issue_head)
{
	if(NULL==issue_head)
	{
		return ;
	}
	issue_node_t* p=issue_head->first;
	while(p!=NULL)
	{
		printf("%d期彩票发行信息\n",p->data.phase_id);
		printf("本期期号:%d\n",p->data.phase_id);
		printf("每注单价:%d\n",p->data.lottery_price);
		printf("开奖状态(0.未开奖 1.已开奖):%d\n",p->data.prize_state);
		printf("中奖号码:");
		int i=0;
		for(i=0;i<7;i++)
		{
			printf("%.2d ",p->data.winning_number[i]);
		}
		printf("\n");
		printf("%d期售出总注数:%d\n",p->data.phase_id,p->data.total_lottery);
		printf("%d期奖池:%d\n",p->data.phase_id,p->data.total_money);
		printf("************************************\n");
		p=p->next;
	}
}

/*
	功能：查看中奖记录
	参数：user_lottery_head 彩票链表头节点
	返回值：无
*/
void look_all_winning_lottery(user_lottery_head_t* user_lottery_head)
{

	if(NULL==user_lottery_head || NULL==user_lottery_head->first)
	{
		return ;
	}
	
	user_lottery_node_t* p=user_lottery_head->first;
	
	printf("*********************************\n");
	printf("*       所有中奖用户记录\t*\n");
	printf("*********************************\n");
	while(p!=NULL)
	{
		if(p->data.winning_status!=0)
		{
			printf("*期号:%d\t\t\t*\n",p->data.phase_id);
			printf("*唯一标识码:%.3d\t\t\t*\n",p->data.mark_id);
			printf("*购买者账号:%s\t\t\t*\n",p->data.user_name);
			printf("*购买的注数:%d\t\t\t*\n",p->data.lottery_number);
			printf("*选中的号码:\t\t\t*\n");
			int i=0,j=0;
			for(i=0;i < p->data.lottery_number;i++)
			{
				printf("*第%d注:",i+1);
				for(j=0;j<7;j++)
				{
					printf("%.2d ",p->data.select_id[i][j]);
				}
				printf("\t*\n");
			}
			printf("*中奖状态:%d\t\t\t*\n",p->data.winning_status);
			printf("*中奖金额:%d\t\t\t*\n",p->data.winning_money);
			printf("*********************************\n");
		
		}
		p=p->next;
	}
}








