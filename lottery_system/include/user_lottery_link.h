#ifndef USER_LOTTERY_LINK_H_
#define USER_LOTTERY_LINK_H_

#include"common.h"

//个人彩票链表值域的声明
struct user_lottery_data{
	int phase_id;				//期号
	char user_name[LEN_NAME];	//购买者账号
	int mark_id;				//单张彩票唯一标识id
	int lottery_number;			//购买注数
	int select_id[5][7];		//彩票选中的号码
	int winning_status;			//中奖状态 非零 中奖 0 未中奖
	int winning_money;			//中奖金额
};

//个人彩票链表普通节点声明
typedef struct user_lottery_node{
	struct user_lottery_data data;		//值域
	struct user_lottery_node* next;		//指针域
}user_lottery_node_t;

//个人彩票链表头节点声明
typedef struct user_lottery_head{
	user_lottery_node_t* first;	//指向第一个节点
}user_lottery_head_t;

/*
	功能：创建个人彩票链表
	参数：无
	返回值：链表头节点
*/
user_lottery_head_t* create_user_lottery_link(void);

/*
	功能：申请个人彩票节点
	参数：data 值域地址
	返回值：节点地址
*/
user_lottery_node_t* create_user_lottery_node(struct user_lottery_data* data);

/*
	功能：插入个人彩票节点
	参数：user_lottery_head 头节点 new_user_lottery_node新节点
	返回值：0 成功 -1 失败
*/
int insert_user_lottery_node(user_lottery_head_t* user_lottery_head,user_lottery_node_t* new_user_lottery_node);

/*
	功能：释放个人彩票所有链表节点
	参数：user_lottery_head 头节点
	返回值：无
*/
void free_user_lottery_node(user_lottery_head_t* user_lottery_head);










#endif
