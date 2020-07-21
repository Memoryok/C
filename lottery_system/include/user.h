#ifndef USER_H_
#define USER_H_

#include"user_link.h"
#include"user_lottery_link.h"

/*
	功能：用户注册
	参数：user_head 用户链表头文件
	返回值：0 成功 -1 失败
*/
int user_register(user_head_t* user_head);

/*
	功能：用户名查找
	参数：user_head 用户链表头节点 user_name 用户名
	返回值：0 成功 -1 失败
*/
int user_name_check(user_head_t* user_head,const char* user_name);

/*
	功能：密码查找
	参数：user_head 用户链表头节点 user_pwd 密码
	返回值：0 成功 -1 失败
*/
int user_pwd_check(user_head_t* user_head,const char* user_name,const char* user_pwd);

/*
	功能：用户登录
	参数：user_head 用户链表头结点
	返回值：0 成功 -1 失败
*/
int user_login(user_head_t* user_head);

/*
	功能：保存用户注册信息
	参数：user_head 用户链表头节点 user_path 用户文件名
	返回值：无
*/
void save_all_user(user_head_t* user_head,const char* user_path);

/*
	功能：加载用户信息
	参数：user_head 用户链表头节点 user_path 用户文件名
	返回值：无
*/
void load_all_user(user_head_t* user_head,const char* user_path);

/*
	功能：注销个人账号
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点
	返回值：0 成功 -1 失败
*/
int logout_user(user_head_t* user_head,user_lottery_head_t* user_lottery_head);

/*
	功能：查找当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点
	返回值:节点地址
*/
user_lottery_node_t* fine_user_lottery(user_lottery_head_t* user_lottery_head);

/*
	功能：删除当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点 fine 查找到当前用户购买彩票的历史信息
	返回值：0 成功 -1 失败
*/
int remove_records(user_lottery_head_t* user_lottery_head,user_lottery_node_t* fine);

/*
	功能：循环删除当前用户所购买的彩票信息节点
	参数：user_lottery_head 彩票链表头节点 fine 查找到当前用户购买彩票的历史信息
	返回值：无
*/
void remove_all_records(user_lottery_head_t* user_lottery_head);









#endif
