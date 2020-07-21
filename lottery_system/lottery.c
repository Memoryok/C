/****************************************
	项目名称：彩票管理系统
	作    者：Memory
	开始时间：2019.09.12
	完成时间：2019.09.20
	调试时间：2019.09.22
	更新时间：2019.09.23
	项目周期：2019.09.12-2019.09.24
	项目语言：C语言
	项目环境：Linux系统
	当前版本：lottery_system 2.0
****************************************/

#include<stdio.h>
#include"user_link.h"
#include"controller.h"
#include"user.h"
#include"common.h"
#include"user_lottery_link.h"
#include"issue_link.h"
#include"user_lottery.h"
#include"admin.h"

//定义全局变量,当前登录用户名
char name[LEN_NAME]={'\0'};

int main(int argc,char **argv)
{
	while(1)
	{
		int choose=instructions();
		if(choose==1)
		{
			//创建用户链表
			user_head_t* user_head=create_user_link();
			if(NULL==user_head)
			{
				return -1;	
			}
			//用户信息加载
			load_all_user(user_head,USER_FILE_NAME);
	
			//创建个人彩票链表
			user_lottery_head_t* user_lottery_head=create_user_lottery_link();
			if(NULL==user_lottery_head)
			{
				return -1;
			}
			//彩票链表加载
			load_all_lottery(user_lottery_head,LOTTERY_FILE_NAME);
	
			//创建每期彩票信息链表
			issue_head_t* issue_head=create_issue_link();
			if(NULL==issue_head)
			{
				return -1;
			}
			//每期彩票链表加载
			load_all_issue(issue_head,ISSUE_FILE_NAME);
	
			//主界面控制
			main_interface_hander(user_head,user_lottery_head,issue_head);
	
			//释放用户节点
			free_user_node(user_head);
			//释放个人彩票节点
			free_user_lottery_node(user_lottery_head);
			//释放每期彩票节点
			free_issue_node(issue_head);
			return 0;
		}
		else if(choose==2)
		{
			return 0;
		}
		else
		{
			printf("输入有误,请重新输入!\n");
		}
	}
}









