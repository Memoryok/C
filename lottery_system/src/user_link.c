#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user_link.h"

/*
	功能：创建链表
	参数：无
	返回值：链表头节点
*/
user_head_t* create_user_link(void)
{
	user_head_t* head=(user_head_t*)malloc(sizeof(user_head_t));	//申请内存空间
	if(NULL==head)
	{
		return NULL;	
	}
	memset(head,0,sizeof(user_head_t));	//初始化
	return head;
}

/*
	功能：申请用户节点
	参数：data 值域地址
	返回值：节点地址
*/
user_node_t* create_user_node(struct user_data* data)
{
	if(NULL==data)
	{
		return NULL;
	}
	user_node_t* new_node=(user_node_t*)malloc(sizeof(user_node_t));	//申请内存空间
	if(NULL==new_node)
	{
		return NULL;
	}
	memset(new_node,0,sizeof(user_node_t));		//初始化
	memcpy(&new_node->data,data,sizeof(user_node_t));	//把值拷贝到新的链表节点值域中
	return new_node;
}

/*
	功能：插入用户节点
	参数：head 头节点 new_node新节点
	返回值：0 成功 -1 失败
*/
int insert_user_node(user_head_t* head,user_node_t* new_node)
{
	if(NULL==head || NULL==new_node)
	{
		return -1;
	}
	if(NULL==head->first)
	{
		//链接新节点
		head->first=new_node;
		new_node->next=NULL;
	}
	else
	{
		user_node_t* p=head->first;
		//遍历找到尾节点
		while(p->next!=NULL)
		{
			p=p->next;
		}
		//链接新节点
		p->next=new_node;
		new_node->next=NULL;
	}
	return 0;
}

/*
	功能：释放用户链表节点
	参数：head 头节点
	返回值：无
*/
void free_user_node(user_head_t* head)
{
	if(NULL==head)
	{
		return ;
	}
	user_node_t* p=head->first;
	user_node_t* q=p;
	
	while(p!=NULL)
	{
		q=q->next;
		free(p);
		p=q;
	}
	free(head);
	head=NULL;
}








