#ifndef USER_LINK_H_
#define USER_LINK_H_

#include"common.h"

//链表值域的声明
struct user_data{
	char user_name[LEN_NAME];	//账号
	char user_pwd[LEN_PWD];		//密码
	int money;					//金额
};

//链表普通节点声明
typedef struct user_node{
	struct user_data data;		//值域
	struct user_node* next;		//指针域
}user_node_t;

//头节点声明
typedef struct user_head{
	user_node_t* first;	//指向第一个节点
}user_head_t;

/*
	功能：创建链表
	参数：无
	返回值：链表头节点
*/
user_head_t* create_user_link(void);

/*
	功能：申请用户节点
	参数：data 值域地址
	返回值：节点地址
*/
user_node_t* create_user_node(struct user_data* data);

/*
	功能：插入用户节点
	参数：head 头节点 new_node新节点
	返回值：0 成功 -1 失败
*/
int insert_user_node(user_head_t* head,user_node_t* new_node);

/*
	功能：释放所有链表节点
	参数：head 头节点
	返回值：无
*/
void free_user_node(user_head_t* head);









#endif
