#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user_lottery_link.h"

//全局变量的声明,当前用户名
extern char name[LEN_NAME];

/*
	功能：创建个人彩票链表
	参数：无
	返回值：链表头节点
*/
user_lottery_head_t* create_user_lottery_link(void)
{
	//申请内存空间
	user_lottery_head_t* user_lottery_head=(user_lottery_head_t*)malloc(sizeof(user_lottery_head_t));	
	if(NULL==user_lottery_head)
	{
		return NULL;	
	}
	memset(user_lottery_head,0,sizeof(user_lottery_head_t));	//初始化
	return user_lottery_head;
}

/*
	功能：申请个人彩票节点
	参数：data 值域地址
	返回值：节点地址
*/
user_lottery_node_t* create_user_lottery_node(struct user_lottery_data* data)
{
	if(NULL==data)
	{
		return NULL;
	}
	//申请内存空间
	user_lottery_node_t* new_user_lottery_node=(user_lottery_node_t*)malloc(sizeof(user_lottery_node_t));
	if(NULL==new_user_lottery_node)
	{
		return NULL;
	}
	memset(new_user_lottery_node,0,sizeof(user_lottery_node_t));		//初始化
	memcpy(&new_user_lottery_node->data,data,sizeof(user_lottery_node_t));	//把值拷贝到新的链表节点值域中
	return new_user_lottery_node;
}

/*
	功能：插入个人彩票节点
	参数：user_lottery_head 头节点 new_user_lottery_node新节点
	返回值：0 成功 -1 失败
*/
int insert_user_lottery_node(user_lottery_head_t* user_lottery_head,user_lottery_node_t* new_user_lottery_node)
{
	if(NULL==user_lottery_head || NULL==new_user_lottery_node)
	{
		return -1;
	}
	if(NULL==user_lottery_head->first)
	{
		//链接新节点
		user_lottery_head->first=new_user_lottery_node;
		new_user_lottery_node->next=NULL;
	}
	else
	{
		user_lottery_node_t* p=user_lottery_head->first;
		//遍历找到尾节点
		while(p->next!=NULL)
		{
			p=p->next;
		}
		//链接新节点
		p->next=new_user_lottery_node;
		new_user_lottery_node->next=NULL;
	}
	return 0;
}

/*
	功能：释放个人彩票所有链表节点
	参数：user_lottery_head 头节点
	返回值：无
*/
void free_user_lottery_node(user_lottery_head_t* user_lottery_head)
{
	if(NULL==user_lottery_head)
	{
		return ;
	}
	user_lottery_node_t* p=user_lottery_head->first;
	user_lottery_node_t* q=p;
	
	while(p!=NULL)
	{
		q=q->next;
		free(p);
		p=q;
	}
	free(user_lottery_head);
	user_lottery_head=NULL;
}








