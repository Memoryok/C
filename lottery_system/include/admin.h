#ifndef ADMIN_H_
#define ADMIN_H_

#include"issue_link.h"
#include"user_lottery_link.h"
#include"user_link.h"

/*
	功能：管理员登录
	参数：无
	返回值：0 成功 -1 失败
*/
int admin_login(void);

/*
	功能：管理员发行彩票
	参数：issue_head 每期彩票头节点
	返回值：0 发行成功 -1 发行失败
*/
int issue_lottery(issue_head_t* issue_head);

/*
	功能：查看最新发行
	参数：issue_head 每期彩票头节点
	返回值：无
*/	
void look_new_issue_lottery(issue_head_t* issue_head);

/*
	功能：得到最大期数
	参数：issue_head 每期彩票头节点
	返回值：返回最大期数
*/
int get_max_phase_id(issue_head_t* issue_head);

/*
	功能：保存每期彩票信息
	参数：issue_head 每期彩票头节点 issue_path 个人彩票文件名
	返回值：无
*/
void save_all_issue(issue_head_t* issue_head,const char* issue_path);

/*
	功能：加载每期彩票信息
	参数：issue_head 每期彩票头节点 issue_path 个人彩票文件名
	返回值：无
*/
void load_all_issue(issue_head_t* issue_head,const char* issue_path);

/*
	功能：查询用户
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点
	返回值：0 成功 -1 失败
*/
int query_user(user_head_t* user_heead,user_lottery_head_t* user_lottery_head);

/*
	功能：按照用户余额降序排序
	参数：use_head 用户链表头节点
	返回值：无
*/
void sort_user_money(user_head_t* user_head);

/*
	功能：打印所有用户信息
	参数：user_head 用户头节点
	返回值：无
*/
void print_user_link(user_head_t* user_head);

/*
	功能：查看所有用户的购买记录
	参数：user_lottery_head 彩票链表头节点
	返回值：无
*/
void look_all_user_lottery(user_lottery_head_t* user_lottery_head);








#endif
