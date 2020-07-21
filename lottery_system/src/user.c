#include<stdio.h>
#include<string.h>
#include"user.h"
#include"common.h"
#include"stdlib.h"

//全局变量的声明,当前用户名
extern char name[LEN_NAME];

/*
	功能：用户注册
	参数：user_head 用户链表头文件
	返回值：0 成功 -1 失败
*/
int user_register(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		return -1;
	}
	struct user_data user;		//用户节点值域
	memset(&user,0,sizeof(struct user_data));	//初始化
	//填充结构体
	int flag=1;
	while(flag)
	{
		input_name(user.user_name,LEN_NAME);
		if(user_name_check(user_head,user.user_name)==0)
		{
			printf("用户名重复,请重新输入!\n");
		}
		else
		{
			flag=0;
		}
	}
	flag=1;
	while(flag)
	{
		input_pwd(user.user_pwd,LEN_PWD);
		if(pwd_verification(user.user_pwd)==0)
		{
			flag=0;
		}
		else
		{
			printf("密码不一致,请重新设置密码!\n");
		}
	}
	flag=1;
	while(flag)
	{
		if(validata_code()==0)	//验证码
		{
			flag=0;
		}
	}
	user.money=2;	//系统赠送金额
	//申请用户节点
	user_node_t* new_node=create_user_node(&user);
	//插入用户节点
	return insert_user_node(user_head,new_node);
}

/*
	功能：保存用户注册信息
	参数：user_head 用户链表头节点 user_path 用户文件名
	返回值：无
*/
void save_all_user(user_head_t* user_head,const char* user_path)
{
	if(NULL==user_head || NULL==user_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	//打开文件
	FILE* fp=fopen(user_path,"wb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	user_node_t* p=user_head->first;
	
	while(p!=NULL)
	{
		if(fwrite(&p->data,sizeof(struct user_data),1,fp)==0)
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
	功能：加载用户信息
	参数：user_head 用户链表头节点 user_path 用户文件名
	返回值：无
*/

void load_all_user(user_head_t* user_head,const char* user_path)
{
	if(NULL==user_head || NULL==user_path)
	{
		fprintf(stderr,"指针不能为空指针!\n");
		return ;
	}
	
	//打开文件
	FILE* fp=fopen(user_path,"rb");
	if(NULL==fp)
	{
		fprintf(stderr,"打开文件失败!\n");
		return ;
	}
	
	struct user_data data;
	//内存清空
	memset(&data,0,sizeof(struct user_data));
	while(fread(&data,sizeof(struct user_data),1,fp)!=0)
	{
		//创建节点
		user_node_t* new_node=create_user_node(&data);
		//插入链表
		insert_user_node(user_head,new_node);
		memset(&data,0,sizeof(struct user_data));	
	}
	fclose(fp);
	fp=NULL;
}

/*
	功能：用户名查找
	参数：user_head 用户链表头节点 user_name 用户名
	返回值：0 成功 -1 失败
*/
int user_name_check(user_head_t* user_head,const char* user_name)
{
	if(NULL==user_head || NULL==user_name)
	{
		printf("头节点和用户不能为空!\n");
		return -1;
	}

	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(p->data.user_name,user_name)==0)
		{
			return 0;
		}
		p=p->next;
	}
	return -1;
}

/*
	功能：密码查找
	参数：user_head 用户链表头节点 user_name 用户名 user_pwd 密码
	返回值：0 成功 -1 失败
*/
int user_pwd_check(user_head_t* user_head,const char* user_name,const char* user_pwd)
{
	if(NULL==user_head || NULL==user_name || NULL==user_pwd)
	{
		printf("头节点,用户名,密码不能为空!\n");
		return -1;
	}
	
	user_node_t* p=user_head->first;
	while(p!=NULL)
	{
		if(strcmp(p->data.user_name,user_name)==0)
		{
			if(strcmp(p->data.user_pwd,user_pwd)==0)
			{	
				return 0;
			}
		}
		p=p->next;
	}
	return -1;
}

/*
	功能：用户登录
	参数：user_head 用户链表头结点
	返回值：成功返回
*/
int user_login(user_head_t* user_head)
{
	if(NULL==user_head)
	{
		printf("头结点不能为空!\n");
		return -1;
	}
	char user_name[LEN_NAME]={'\0'};
	char user_pwd[LEN_PWD]={'\0'};
	int count=3;
	while(count)
	{
		printf("请输入用户名:");
		fgets(user_name,LEN_NAME,stdin);
		if(user_name[strlen(user_name)-1]=='\n')
		{
			user_name[strlen(user_name)-1]='\0';
		}
		else
		{
			FLUSH;
		}
		//判断用户名是否与用户链表的用户名匹配
		if(user_name_check(user_head,user_name)==0)
		{
			while(count)
			{
				printf("请输入密码:");
				getPassword(user_pwd);
				//判断密码是否与用户链表的密码匹配
				if(user_pwd_check(user_head,user_name,user_pwd)==0)
				{
					if(validata_code()==0)	//验证码
					{
						strcpy(name,user_name);
						return 0;
					}
					else
					{
						return -1;
					}
				}
				else
				{
					count--;
					printf("密码错误,你还有%d次机会,请重新输入!\n",count);
				}
			}
		}
		else
		{
			count--;
			printf("用户名不对应,你还有%d次机会,请重新输入!\n",count);
		}
	}
	return -1;
}

/*
	功能：注销个人账号
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点
	返回值：0 成功 -1 失败
*/
int logout_user(user_head_t* user_head,user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_head || NULL==user_head->first || NULL==user_lottery_head)
	{
		return -1;
	}
	
	int choose=0;
	printf("*********************************************\n");
	printf("在注销前,请确定您账户下余额是否已经清空;\n");
	printf("一旦注销,您的个人信息及所有购买记录全部消失!\n");
	printf("*********************************************\n");
	printf("您是否要进行此操作:\n");
	printf("1.确定注销\t2.返回\n");
	
	while(1)
	{
		scanf("%d",&choose);
		if(choose==1)
		{
			//删除用户信息
			user_node_t* p1=user_head->first;
			user_node_t* p2=p1;
			if(strcmp(name,p1->data.user_name)==0)	//用户如果在第一个节点的情况
			{
				user_head->first=p1->next;
				free(p1);
				p1=NULL;
				remove_all_records(user_lottery_head);
				return 0;
			}
			while(p1!=NULL)		//用户在第一个节点之后的情况
			{
				p1=p1->next;
				if(strcmp(name,p1->data.user_name)==0)
				{
					p2->next=p1->next;
					free(p1);
					p1=NULL;
					remove_all_records(user_lottery_head);
					return 0;
				}
				p2=p1;
			}
			return -1;
		}
		else if(choose==2)
		{
			return -1;
		}
		else
		{
			printf("输入有误,请重新选择!\n");
		}
	}
}

/*
	功能：查找当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点
	返回值:节点地址
*/
user_lottery_node_t* fine_user_lottery(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head)
	{
		return NULL;
	}
	
	user_lottery_node_t* fine=user_lottery_head->first;
	
	while(fine!=NULL)		//循环遍历整个彩票链表找到该用户购买记录的第一个节点
	{
		if(strcmp(fine->data.user_name,name)==0)
		{
			return fine;	//返回第一个节点
		}
		fine=fine->next;
	}
	return NULL;
}

/*
	功能：删除当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点 fine 查找到当前用户购买彩票的历史信息
	返回值：0 成功 -1 失败
*/
int remove_records(user_lottery_head_t* user_lottery_head,user_lottery_node_t* fine)
{
	if(NULL==user_lottery_head || NULL==fine)
	{
		return -1;
	}

	if(fine==user_lottery_head->first)	//判断找到的这个节点是否是整个链表的第一个,如果是则删除
	{
		user_lottery_head->first=fine->next;
		free(fine);
		fine=NULL;
		return 0;
	}
	
	user_lottery_node_t* p=user_lottery_head->first;
	
	while(p->next!=fine)	//如果不是第一个,则遍历查找到这个节点删除
	{	
		p=p->next;
	}
	p->next=fine->next;
	free(fine);
	fine=NULL;
	return 0;
}

/*
	功能：循环删除当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点 
	返回值：无
*/
void remove_all_records(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head)
	{
		return ;
	}

	while(1)	//购买信息不止一条,利用死循环直至把该用户下所有购买信息全删除
	{
		user_lottery_node_t* fine = fine_user_lottery(user_lottery_head);
		if(-1 == remove_records(user_lottery_head,fine))
		{
			break;
		}
	}
}








