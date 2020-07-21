#include<stdio.h>
#include<string.h>
#include"admin.h"
#include"common.h"
#include"user_lottery.h"

//全局变量的声明,用于查询用户信息
extern char name[LEN_NAME];

/*
	功能：管理员登录
	参数：无
	返回值：0 成功 -1 失败
*/
int admin_login(void)
{
	int count=3;
	char admin_name[LEN_NAME]={'\0'};
	char admin_pwd[LEN_PWD]={'\0'};
	while(count)
	{
		printf("请输入管理员账号:");
		fgets(admin_name,LEN_NAME,stdin);
		if(admin_name[strlen(admin_name)-1]=='\n')
		{
			admin_name[strlen(admin_name)-1]='\0';
		}
		else
		{
			FLUSH;
		}
		if(strcmp(admin_name,ADMIN_NAME)==0)
		{
			while(count)
			{
				printf("请输入管理员密码:");
				getPassword(admin_pwd);
				if(strcmp(admin_pwd,ADMIN_PWD)==0)
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
	功能：管理员发行彩票
	参数：issue_head 每期彩票头节点
	返回值：0 发行成功 -1 发行失败
*/
int issue_lottery(issue_head_t* issue_head)
{
	if(NULL==issue_head)
	{
		return -1;
	}
	//填充结构体
	char pwd[LEN_PWD]={'\0'};
	printf("请输入管理员密码进行确认:");
	getPassword(pwd);
	if(strcmp(pwd,ADMIN_PWD)==0)
	{
		struct issue_data data;		//新增每期彩票值域
		memset(&data,0,sizeof(struct issue_data));	//初始化
		issue_node_t* p=issue_head->first;
		if(issue_head->first==NULL)
		{
			data.phase_id=1001;		//当前期数
			int price=0;
			printf("请输入本期彩票每注单价:");
			scanf("%d",&price);
			data.lottery_price=price;	//每注彩票的单价
			data.prize_state=0;			//0未开奖 1开奖  本次判断为第一次发行无上一次的开奖状态
			int i=0;
			for(i=0;i<7;i++)
			{
				data.winning_number[i]=0;	//中奖号码初始化全部为0
			}
			data.total_lottery=0;		//本期售出总注数
			data.total_money=100000;	//奖池金额=投资100000元
			//申请每期彩票节点
			issue_node_t* new_issue_node=create_issue_node(&data);
			//插入每期彩票节点
			return insert_issue_node(issue_head,new_issue_node);
		}
		else
		{
			while(p->next!=NULL)
			{
				p=p->next;
			}
			if(p->data.prize_state==1)	//上一次已经发行并开奖
			{
				int max_phase_id=get_max_phase_id(issue_head);	//得到最大期数
				data.phase_id=max_phase_id+1;	//当前期数
				int price=0;
				printf("请输入本期彩票每注单价:");
				scanf("%d",&price);
				data.lottery_price=price;	//每注彩票的单价
				data.prize_state=0;		//0未开奖 1开奖
				int i=0;
				for(i=0;i<7;i++)
				{
					data.winning_number[i]=0;	//中奖号码初始化全部为0
				}
				data.total_lottery=0;	//本期售出总注数
				data.total_money=p->data.total_money;	 //奖池金额=上一期奖池金额的累和 
				//申请每期彩票节点
				issue_node_t* new_issue_node=create_issue_node(&data);
				//插入每期彩票节点
				return insert_issue_node(issue_head,new_issue_node);
			}
			else
			{
				printf("上一期还未开奖,暂时还不能发行!\n");
				return -1;
			}
		}
	}
	else
	{
		printf("密码错误,你不是管理员不能进行此操作!\n");
		return -1;
	}
}	

/*
	功能：查看最新发行
	参数：issue_head 每期彩票头节点
	返回值：无
*/	
void look_new_issue_lottery(issue_head_t* issue_head)
{
	if(NULL==issue_head || NULL==issue_head->first)
	{
		return ;
	}
	issue_node_t* p=issue_head->first;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	printf("本期彩票发行信息\n");
	printf("***********************************\n");
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
	printf("本期售出总注数:%d\n",p->data.total_lottery);
	printf("本期奖池:%d\n",p->data.total_money);
	printf("***********************************\n");
}

/*
	功能：得到最大期数
	参数：issue_head 每期彩票头节点
	返回值：返回最大期数
*/
int get_max_phase_id(issue_head_t* issue_head)
{
	if(NULL==issue_head)
	{
		return -1;
	}
	
	int id=1000;
	issue_node_t* p=issue_head->first;
	while(p!=NULL)
	{
		if(id<p->data.phase_id)
		{
			id=p->data.phase_id;
		}
		p=p->next;
	}
	return id;
}

/*
	功能：保存每期彩票信息
	参数：issue_head 每期彩票头节点 issue_path 个人彩票文件名
	返回值：无
*/
void save_all_issue(issue_head_t* issue_head,const char* issue_path)
{
	if(NULL==issue_head || NULL==issue_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	
	//打开文件
	FILE* fp=fopen(issue_path,"wb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	issue_node_t* p=issue_head->first;
	
	while(p!=NULL)
	{
		if(fwrite(&p->data,sizeof(struct issue_data),1,fp)==0)
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
	功能：加载每期彩票信息
	参数：issue_head 每期彩票头节点 issue_path 个人彩票文件名
	返回值：无
*/
void load_all_issue(issue_head_t* issue_head,const char* issue_path)
{
	if(NULL==issue_head || NULL==issue_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	
	//打开文件
	FILE* fp=fopen(issue_path,"rb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	struct issue_data data;
	
	//内存清空
	memset(&data,0,sizeof(struct issue_data));
	while(fread(&data,sizeof(struct issue_data),1,fp)!=0)
	{
		//创建节点
		issue_node_t* new_issue_node=create_issue_node(&data);
		//插入链表
		insert_issue_node(issue_head,new_issue_node);
		memset(&data,0,sizeof(struct issue_data));
	}
	fclose(fp);
	fp=NULL;
}

/*
	功能：查询用户
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点
	返回值：0 成功 -1 失败
*/
int query_user(user_head_t* user_head,user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_head || NULL==user_lottery_head)
	{
		return -1;
	}
	char query[LEN_NAME]={'\0'};
	printf("请输入需要查询的用户账号:");
	scanf("%s",query);
	user_node_t* p=user_head->first;
	
	while(p!=NULL)
	{
		if(strcmp(query,p->data.user_name)==0)
		{
			printf("\t用户基础信息\n");
			printf("\t用户名:%s\n",p->data.user_name);
			printf("\t余额:%d\n",p->data.money);
			strcpy(name,query);		//把需要查找的用户名给到全局变量name,进入下面函数使用
			look_lottery_records(user_lottery_head);
			memset(name,0,sizeof(char));	//使用完成后,将name置空,防止后面出错
			return 0;
		}
		p=p->next;
	}
	printf("没有该用户!\n");
	return -1;
}

/*
	功能：按照用户余额降序排序
	参数：use_head 用户链表头节点
	返回值：无
*/
void sort_user_money(user_head_t* user_head)
{
	if(NULL==user_head || NULL==user_head->first || NULL==user_head->first->next)
	{
		return ;
	}
	user_node_t* p=user_head->first;
	user_node_t* q=NULL;
	for(p=user_head->first;p->next!=NULL;p=p->next)
	{
		for(q=p->next;q!=NULL;q=q->next)
		{
			if(p->data.money<q->data.money)
			{
				struct user_data temp=p->data;
				p->data=q->data;
				q->data=temp;	
			}
		}
	}
}

/*
	功能：打印所有用户信息
	参数：user_head 用户头节点
	返回值：无
*/
void print_user_link(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return ;
	}
	user_node_t* p=user_head->first;
	printf("********************************\n");
	printf("账号\t\t\t金额\n");
	while(p!=NULL)
	{
		printf("%s\t\t\t%d\n",p->data.user_name,p->data.money);
		p=p->next;
	}
	printf("********************************\n");
}

/*
	功能：查看所有用户的购买记录
	参数：user_lottery_head 彩票链表头节点
	返回值：无
*/
void look_all_user_lottery(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head || NULL==user_lottery_head->first)
	{
		return ;
	}
	
	user_lottery_node_t* p=user_lottery_head->first;
	
	printf("\t*********************************\n");
	printf("\t*       所有用户购买记录\t*\n");
	printf("\t*********************************\n");
	while(p!=NULL)
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
		
		p=p->next;
	}
}





