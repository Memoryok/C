#ifndef WORKER_H_
#define WORKER_H_

#include"user_link.h"
#include"user_lottery_link.h"
#include"issue_link.h"

/*
	功能：公证员登录
	参数：无
	返回值：0 成功 -1 失败
*/
int worker_login(void);

/*
	功能：开奖
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int open_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：兑奖
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int exchange_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：数组排序（冒泡排序）
	参数：ary 数组地址	len 数组长度
	返回值：数组元素最大值
*/
int bubble_sort(int *ary,int len);

/*
	功能：查看历史发行
	参数：issue_head 每期彩票头节点
	返回值：无
*/
void look_history_issue_lottery(issue_head_t* issue_head);

/*
	功能：查看中奖记录
	参数：user_lottery_head 彩票链表头节点
	返回值：无
*/
void look_all_winning_lottery(user_lottery_head_t* user_lottery_head);






#endif
