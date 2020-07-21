#ifndef ISSUE_LINK_H_
#define ISSUE_LINK_H_

//每期彩票链表值域的声明
struct issue_data{
	int phase_id;				//期号
	int lottery_price;			//彩票单价(每注2元)
	int prize_state;			//开奖状态 1 已开奖 0 未开奖
	int winning_number[7];		//中奖号码
	int total_lottery;			//本期售出总数
	int total_money;			//本期奖池总额
};

//每期彩票链表普通节点声明
typedef struct issue_node{
	struct issue_data data;		//值域
	struct issue_node* next;		//指针域
}issue_node_t;

//每期彩票链表头节点声明
typedef struct issue_head{
	issue_node_t* first;	//指向第一个节点
}issue_head_t;

/*
	功能：创建每期彩票链表
	参数：无
	返回值：链表头节点
*/
issue_head_t* create_issue_link(void);

/*
	功能：申请每期彩票节点
	参数：data 值域地址
	返回值：节点地址
*/
issue_node_t* create_issue_node(struct issue_data* data);

/*
	功能：插入每期彩票节点
	参数：issue_head 头节点 new_issue_node新节点
	返回值：0 成功 -1 失败
*/
int insert_issue_node(issue_head_t* issue_head,issue_node_t* new_issue_node);

/*
	功能：释放所有彩票链表节点
	参数：issue_head 头节点
	返回值：无
*/
void free_issue_node(issue_head_t* issue_head);








#endif
