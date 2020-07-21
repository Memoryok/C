#include<stdio.h>
#include"user_lottery.h"
#include"user_link.h"
#include<string.h>
#include"user.h"
#include"user_lottery_link.h"
#include"common.h"

//全局变量的声明,当前用户名
extern char name[LEN_NAME];

/*
	功能：用户查看个人信息
	参数：user_head 用户链表头节点
	返回值：无
*/
void look_personal_information(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return ;
	}
	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0)
		{
			printf("个人信息\n");
			printf("****************\n");
			printf("账号:%s\n密码:%s\n余额:%d\n",p->data.user_name,p->data.user_pwd,p->data.money);
			printf("****************\n");
		}
		p=p->next;
	}
}

/*
	功能：用户修改个人密码
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int modify_personal_pwd(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return -1;
	}
	char old_pwd[LEN_PWD]={'\0'};
	char new_pwd1[LEN_PWD]={'\0'};
	char new_pwd2[LEN_PWD]={'\0'};
	int count1=3,count2=3;
	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0)
		{
			while(count1)
			{
				printf("请输入原先密码:");
				getPassword(old_pwd);
				if(strcmp(old_pwd,p->data.user_pwd)==0)
				{
					count1=0;
				}
				else
				{
					printf("密码错误,请重新输入!\n");
					count1--;
					if(count1==0)
					{
						return -1;
					}
					count2=count1;
					printf("您还有%d次机会!\n",count1);
				}
			}
			while(1)
			{
				printf("请输入新的密码:");
				getPassword(new_pwd1);
				if(strcmp(old_pwd,new_pwd1)==0)
				{
					printf("新密码与原密码重复,请重新输入!\n");
				}
				else if(strlen(new_pwd1) >= LEN_PWD-1)
				{
					printf("你输入的密码过长,请重新输入!\n");
				}
				else if(strlen(new_pwd1)<=5)
				{
					printf("你输入的密码过短,安全性低,请重新输入!\n");
				}
				else
				{
					while(count2)
					{
						printf("请再输入一次新密码:");
						getPassword(new_pwd2);
						if(strcmp(new_pwd1,new_pwd2)==0)
						{
							int choose=0;
							while(1)
							{
								printf("**********\n");
								printf("1.确认修改\n");
								printf("2.退    出\n");
								printf("**********\n");
								scanf("%d",&choose);
								if(choose==1)
								{
									//把原来的密码覆盖掉
									strcpy(p->data.user_pwd,new_pwd1);
									return 0;
								}
								else if(choose==2)
								{
									return -1;
								}
								else
								{
									printf("输入有误,请重新操作!\n");
								}
							}
						}
						else
						{
							printf("密码不一致,请重新设置!\n");
							count2--;
							if(count2==0)
							{
								return -1;
							}
							printf("您还有%d次机会!\n",count2);
						}
					}
				}
			}
		}
		p=p->next;
	}
	return -1;
}

/*
	功能：查看账户金额
	参数：user_head 用户链表头节点
	返回值：无
*/
void look_personal_money(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return ;
	}
	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0)
		{
			printf("*****************\n");
			printf("您账户还有%d元!\n",p->data.money);
			printf("*****************\n");
		}
		p=p->next;
	}
}

/*
	功能：充值账户金额
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int replenish_personal_money(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return	-1;
	}
	int replenish_money=0;
	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0)
		{
			printf("**********************************\n");
			printf("您需要充值多少钱,最低2元且是整数:");
			scanf("%d",&replenish_money);
			if(replenish_money>=2)
			{
				p->data.money+=replenish_money;
				return 0;
			}
			else
			{
				return -1;
			}
		}
		p=p->next;
	}
	return -1;
}

/*
	功能：保存个人彩票信息
	参数：user_lottery_head 彩票链表头节点 lottery_path 个人彩票文件名
	返回值：无
*/
void save_all_lottery(user_lottery_head_t* user_lottery_head,const char* lottery_path)
{
	if(NULL==user_lottery_head || NULL==lottery_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	//打开文件
	FILE* fp=fopen(lottery_path,"wb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	user_lottery_node_t* p=user_lottery_head->first;
	
	while(p!=NULL)
	{
		if(fwrite(&p->data,sizeof(struct user_lottery_data),1,fp)==0)
		{
			fprintf(stderr,"写入失败!\n");
		}
		p=p->next;
	}
	//关闭文件
	fclose(fp);
	fp=NULL;
}

/*
	功能：加载彩票信息
	参数：user_lottery_head 彩票链表头节点 lottery_path 个人彩票文件名
	返回值：无
*/
void load_all_lottery(user_lottery_head_t* user_lottery_head,const char* lottery_path)
{
	if(NULL==user_lottery_head || NULL==lottery_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	
	//打开文件
	FILE* fp=fopen(lottery_path,"rb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	struct user_lottery_data data;
	//内存清空
	memset(&data,0,sizeof(struct user_lottery_data));
	while(fread(&data,sizeof(struct user_lottery_data),1,fp)!=0)
	{
		//创建节点
		user_lottery_node_t* new_user_lottery_node=create_user_lottery_node(&data);
		//插入链表
		insert_user_lottery_node(user_lottery_head,new_user_lottery_node);
		memset(&data,0,sizeof(struct user_lottery_data));
	}
	fclose(fp);
	fp=NULL;
}

/*
	功能：用户下注
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int buy_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head || NULL==user_lottery_head || NULL==issue_head)
	{
		return -1;
	}
	if(NULL==issue_head->first)
	{
		printf("彩票还未发行,暂时还不能购买!\n");
		return -1;
	}

	issue_node_t* p_issue=issue_head->first;
	
	struct user_lottery_data data;		//彩票的值域
	memset(&data,0,sizeof(struct user_lottery_data));	//初始化
	
	while(p_issue->next!=NULL)
	{
		p_issue=p_issue->next;
	}
	printf("本期发行彩票信息\n");
	printf("***************************************************************\n");
	printf("本期期数\t每注单价\t开奖状态(0.未开奖 1.已开奖)\n");
	printf("%d\t\t%d\t\t%d\n",p_issue->data.phase_id,p_issue->data.lottery_price,p_issue->data.prize_state);
	printf("***************************************************************\n");
	if(p_issue->data.prize_state==1)
	{
		printf("本期彩票已开奖,不能购买,请等待下次发行!\n");
		return -1;
	}
	while(1)
	{
		int num=0;		//购买彩票注数
		int flag=1;
		while(flag)
		{
			printf("请输入需要购买彩票的注数(最多只能买5注):");
			scanf("%d",&num);
			if(num>0 && num<6)
			{
				flag=0;
			}
			else
			{
				printf("输入有误,请重新输入!\n");
			}
		}
		user_node_t* p_user=user_head->first;
		while(p_user!=NULL)
		{
			if(strcmp(name,p_user->data.user_name)==0)
			{
				if((num*p_issue->data.lottery_price) <= p_user->data.money)
				{
					data.phase_id=p_issue->data.phase_id;	//本期期号
					strcpy(data.user_name,name);			//购买者账号
					data.mark_id=get_max_mark_id(user_lottery_head)+1;	//单张彩票唯一标识
					data.lottery_number=num;	//购买的注数
					int i=0,j=0;
					for(i=0;i<num;i++)
					{
						printf("请输入第%d注购买的号码:",i+1);
						for(j=0;j<7;j++)
						{
							scanf("%d",&data.select_id[i][j]);	//读取购买的号码
						}
						int k=0;
						for(k=0;k<7;k++)
						{
							if(data.select_id[i][k]<1 || data.select_id[i][k]>33)	//检测球号在1-33是否之间
							{
								printf("您购买的号码有误,请重新购买,注意确认球号是否在1-33中间!\n");
								i--;
								break;
							}
						}
					}
					data.winning_status=0;	//中奖状态 0未中奖 1-7中奖等级  还未开奖，初始化为0
					data.winning_money=0;	//还未开奖，初始化为0
					//本期售出的总注数
					p_issue->data.total_lottery=p_issue->data.total_lottery+num;
				
					//购买后奖池金额
					p_issue->data.total_money=p_issue->data.total_money+(num*p_issue->data.lottery_price);
					//购买者购买后余额
					p_user->data.money=p_user->data.money-(num*p_issue->data.lottery_price);
					
					//插入新节点
					user_lottery_node_t* new_user_lottery_node=create_user_lottery_node(&data);
					//链接新节点
					return insert_user_lottery_node(user_lottery_head,new_user_lottery_node);
				}
				else
				{
					printf("金额不足,请充值后购买!\n");
					if(jump_replenish(user_head)==0)
					{
						printf("充值成功!\n");
						look_personal_money(user_head);
					}
					else
					{
						printf("充值失败!\n");
						return -1;
					}
				}
			}
			p_user=p_user->next;
		}
	}
	return 0;
}

/*
	功能：获得最大唯一标识
	参数：user_lottery_head 彩票链表头节点
	返回值：返回最大唯一标识
*/
int get_max_mark_id(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head)
	{
		return -1;
	}
	int id=0;
	user_lottery_node_t* p=user_lottery_head->first;
	while(p!=NULL)
	{
		if(id<p->data.mark_id)
		{
			id=p->data.mark_id;
		}
		p=p->next;
	}
	return id;
}

/*
	功能：进行跳转充值
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int jump_replenish(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return -1;
	}
	int choose=0;
	printf("**********************\n");
	printf("是否充值:\n1.跳转充值 2.退出\n");
	while(1)
	{
		scanf("%d",&choose);
		if(choose==1)
		{
			if(replenish_personal_money(user_head)==0)
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else if(choose==2)
		{
			return -1;
		}
		else
		{
			printf("输入有误,请重新输入!\n");
		}
	}
}

/*
	功能：查看彩票信息
	参数：user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值:无
*/
void look_new_lottery_records(user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_lottery_head || NULL==issue_head || NULL==user_lottery_head->first || NULL==issue_head->first)
	{
		return ;
	}
	user_lottery_node_t* p=user_lottery_head->first;
	issue_node_t* q=issue_head->first;
	while(q->next!=NULL)
	{
		q=q->next;
	}
	
	printf("\t*********************************\n");
	printf("\t*       最新彩票购买信息\t*\n");
	printf("\t*********************************\n");
	
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0 && p->data.phase_id == q->data.phase_id)
		{
			printf("\t*********************************\n");
			printf("\t*期号:%d\t\t\t*\n",p->data.phase_id);
			printf("\t*唯一标识码:%.3d\t\t\t*\n",p->data.mark_id);
			printf("\t*购买者账号:%s\t\t\t*\n",p->data.user_name);
			printf("\t*购买的注数:%d\t\t\t*\n",p->data.lottery_number);
			printf("\t*选中的号码:\t\t\t*\n");
			int i=0,j=0;
			for(i=0;i < p->data.lottery_number;i++)
			{
				printf("\t*第%d注:",i+1);
				for(j=0;j<7;j++)
				{
					printf("%.2d ",p->data.select_id[i][j]);
				}
				printf("\t*\n");
			}
			printf("\t*中奖状态:%d\t\t\t*\n",p->data.winning_status);
			printf("\t*中奖金额:%d\t\t\t*\n",p->data.winning_money);
			printf("\t*********************************\n");
		
		}
		p=p->next;
	}
}

/*
	功能：查看中奖记录
	参数：user_lottery_head 彩票链表头节点
	返回值:无
*/
void look_winning_lottery(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head || NULL==user_lottery_head->first)
	{
		return ;
	}
	user_lottery_node_t* p=user_lottery_head->first;

	printf("\t*********************************\n");
	printf("\t*       彩票中奖记录信息\t*\n");
	printf("\t*********************************\n");
		
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0 && p->data.winning_money!=0)
		{
			printf("\t*********************************\n");
			printf("\t*期号:%d\t\t\t*\n",p->data.phase_id);
			printf("\t*唯一标识码:%.3d\t\t\t*\n",p->data.mark_id);
			printf("\t*购买者账号:%s\t\t\t*\n",p->data.user_name);
			printf("\t*购买的注数:%d\t\t\t*\n",p->data.lottery_number);
			printf("\t*选中的号码:\t\t\t*\n");
			int i=0,j=0;
			for(i=0;i < p->data.lottery_number;i++)
			{
				printf("\t*第%d注:",i+1);
				for(j=0;j<7;j++)
				{
					printf("%.2d ",p->data.select_id[i][j]);
				}
				printf("\t*\n");
			}
			printf("\t*中奖状态:%d\t\t\t*\n",p->data.winning_status);
			printf("\t*中奖金额:%d\t\t\t*\n",p->data.winning_money);
			printf("\t*********************************\n");
		
		}
		p=p->next;
	}
}

/*
	功能：查看购买记录
	参数：user_lottery_head 彩票链表头节点 
	返回值:无
*/
void look_lottery_records(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head || NULL==user_lottery_head->first)
	{
		return ;
	}
	user_lottery_node_t* p=user_lottery_head->first;
	
	printf("\t*********************************\n");
	printf("\t*       购买彩票历史记录\t*\n");
	printf("\t*********************************\n");
	
	while(p!=NULL)
	{
		if(strcmp(name,p->data.user_name)==0)
		{
			printf("\t*********************************\n");
			printf("\t*期号:%d\t\t\t*\n",p->data.phase_id);
			printf("\t*唯一标识码:%.3d\t\t\t*\n",p->data.mark_id);
			printf("\t*购买者账号:%s\t\t\t*\n",p->data.user_name);
			printf("\t*购买的注数:%d\t\t\t*\n",p->data.lottery_number);
			printf("\t*选中的号码:\t\t\t*\n");
			int i=0,j=0;
			for(i=0;i < p->data.lottery_number;i++)
			{
				printf("\t*第%d注:",i+1);
				for(j=0;j<7;j++)
				{
					printf("%.2d ",p->data.select_id[i][j]);
				}
				printf("\t*\n");
			}
			printf("\t*中奖状态:%d\t\t\t*\n",p->data.winning_status);
			printf("\t*中奖金额:%d\t\t\t*\n",p->data.winning_money);
			printf("\t*********************************\n");
		
		}
		p=p->next;
	}
}








