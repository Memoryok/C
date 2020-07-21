#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"issue_link.h"

/*
	功能：创建每期彩票链表
	参数：无
	返回值：链表头节点
*/
issue_head_t* create_issue_link(void)
{
	//申请内存空间
	issue_head_t* issue_head=(issue_head_t*)malloc(sizeof(issue_head_t));	
	if(NULL==issue_head)
	{
		return NULL;	
	}
	memset(issue_head,0,sizeof(issue_head_t));	//初始化
	return issue_head;
}

/*
	功能：申请每期彩票节点
	参数：data 值域地址
	返回值：节点地址
*/
issue_node_t* create_issue_node(struct issue_data* data)
{
	if(NULL==data)
	{
		return NULL;
	}
	//申请内存空间
	issue_node_t* new_issue_node=(issue_node_t*)malloc(sizeof(issue_node_t));
	if(NULL==new_issue_node)
	{
		return NULL;
	}
	memset(new_issue_node,0,sizeof(issue_node_t));	//初始化
	//把值拷贝到新的链表节点值域中
	memcpy(&new_issue_node->data,data,sizeof(issue_node_t));	
	return new_issue_node;
}

/*
	功能：插入每期彩票节点
	参数：issue_head 头节点 new_issue_node新节点
	返回值：0 成功 -1 失败
*/
int insert_issue_node(issue_head_t* issue_head,issue_node_t* new_issue_node)
{
	if(NULL==issue_head || NULL==new_issue_node)
	{
		return -1;
	}
	if(NULL==issue_head->first)
	{
		//链接新节点
		issue_head->first=new_issue_node;
		new_issue_node->next=NULL;
	}
	else
	{
		issue_node_t* p=issue_head->first;
		//遍历找到尾节点
		while(p->next!=NULL)
		{
			p=p->next;
		}
		//链接新节点
		p->next=new_issue_node;
		new_issue_node->next=NULL;
	}
	return 0;
}

/*
	功能：释放所有彩票链表节点
	参数：issue_head 头节点
	返回值：无
*/
void free_issue_node(issue_head_t* issue_head)
{
	if(NULL==issue_head)
	{
		return ;
	}
	issue_node_t* p=issue_head->first;
	issue_node_t* q=p;
	
	while(p!=NULL)
	{
		q=q->next;
		free(p);
		p=q;
	}
	free(issue_head);
	issue_head=NULL;
}










