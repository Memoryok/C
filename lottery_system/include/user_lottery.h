#ifndef USER_LOTTERY_H_
#define USER_LOTTERY_H_

#include"user_link.h"
#include"user_lottery_link.h"
#include"issue_link.h"

/*
	功能：用户查看个人信息
	参数：user_head 用户链表头节点
	返回值：无
*/
void look_personal_information(user_head_t* user_head);

/*
	功能：用户修改个人密码
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int modify_personal_pwd(user_head_t* user_head);

/*
	功能：查看账户金额
	参数：user_head 用户链表头节点
	返回值：无
*/
void look_personal_money(user_head_t* user_head);

/*
	功能：充值账户金额
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int replenish_personal_money(user_head_t* user_head);

/*
	功能：保存个人彩票信息
	参数：user_lottery_head 彩票链表头节点 lottery_path 个人彩票文件名
	返回值：无
*/
void save_all_lottery(user_lottery_head_t* user_lottery_head,const char* lottery_path);

/*
	功能：加载彩票信息
	参数：user_lottery_head 彩票链表头节点 lottery_path 个人彩票文件名
	返回值：无
*/
void load_all_lottery(user_lottery_head_t* user_lottery_head,const char* lottery_path);

/*
	功能：用户下注
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：0 成功 -1 失败
*/
int buy_lottery(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：获得最大唯一标识
	参数：user_lottery_head 彩票链表头节点
	返回值：返回最大唯一标识
*/
int get_max_mark_id(user_lottery_head_t* user_lottery_head);

/*
	功能：进行跳转充值
	参数：user_head 用户链表头节点
	返回值：0 成功 -1 失败
*/
int jump_replenish(user_head_t* user_head);

/*
	功能：查看彩票信息
	参数：user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值:无
*/
void look_new_lottery_records(user_lottery_head_t* user_lottery_head,issue_head_t* issue_head);

/*
	功能：查看中奖记录
	参数：user_lottery_head 彩票链表头节点
	返回值:无
*/
void look_winning_lottery(user_lottery_head_t* user_lottery_head);

/*
	功能：查看购买记录
	参数：user_lottery_head 彩排链表头节点 
	返回值:无
*/
void look_lottery_records(user_lottery_head_t* user_lottery_head);









#endif
