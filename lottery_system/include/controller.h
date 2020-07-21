#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include"user_link.h"
#include"user_lottery_link.h"
#include"issue_link.h"

/*
	功能：主界面控制
	参数：user_head用户链表头节点 user_lottery_head 用户个人彩票头节点 issue_head 每期彩票头节点
	返回值：无 
*/
void main_interface_hander(user_head_t* user_head,
					user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：用户界面控制
	参数：user_head用户链表头节点 user_lottery_head 用户个人彩票头节点 issue_head 每期彩票头节点
	返回值：无
*/
void user_interface_hander(user_head_t* user_head,
						user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：管理员界面控制
	参数：user_head 用户链表头节点 user_lottery_head 个人彩票链表头文件 issue_head 每期彩票头节点
	返回值：无
*/
void user_admin_hander(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：公证员界面控制
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：无
*/
void user_worker_hander(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);








#endif
