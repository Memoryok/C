#include<stdio.h>
#include"controller.h"
#include"view.h"
#include"user.h"
#include"user_lottery.h"
#include"admin.h"
#include"worker.h"
#include"common.h"
#include"game.h"

/*
	功能：主界面控制
	参数：user_head用户链表头节点 user_lottery_head 用户个人彩票头节点 issue_head 每期彩票头节点
	返回值：无
*/
void main_interface_hander(user_head_t* user_head,
						user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		int choose1=main_interface();	//调用主界面接口
		int choose2=0;
		switch(choose1)
		{
			case 1:		//用户登录
				if(user_login(user_head)==0)
				{
					CONTINUE("登录成功!\n");
					user_interface_hander(user_head,user_lottery_head,issue_head);
				}
				else
				{
					CONTINUE("登录失败!\n");
				}
				break;
			case 2:		//用户注册
				if(user_register(user_head)==0)
				{
					//保存
					save_all_user(user_head,USER_FILE_NAME);
					CONTINUE("注册成功,系统赠送2元,请登录自动领取!\n");
					getchar();
				}
				else
				{
					CONTINUE("注册失败，请重新注册!\n");
				}
				break;
			case 3:		//管理员登录
				if(admin_login()==0)
				{
					CONTINUE("登录成功!\n");
					user_admin_hander(user_head,user_lottery_head,issue_head);
				}
				else
				{
					CONTINUE("登录失败!\n");
				}
				break;
			case 4:		//公证员登录
				if(worker_login()==0)
				{
					CONTINUE("登录成功!\n");
					user_worker_hander(user_head,user_lottery_head,issue_head);
				}
				else
				{
					CONTINUE("登录失败!\n");
				}
				break;
			//case 5:
				//print_user_link(user_head);	//编写测试,不在终端显示
				//break;
			case 0:		//退出系统
				choose2=confirm_select();	//调用选项选择确认
				if(choose2==1)
				{
					printf("再见!\n");
					flag=0;
				}
				else if(choose2==2)
				{
					CONTINUE("欢迎回来!\n");
				}
				else
				{
					CONTINUE("输入有误,请重新输入!\n");
				}
				break;
			default:
				CONTINUE("输入有误,请重新输入!\n");
				break;	
		}
	}
}

/*
	功能：用户界面控制
	参数：user_head用户链表头节点 user_lottery_head 用户个人彩票头节点 issue_head 每期彩票头节点
	返回值：无
*/
void user_interface_hander(user_head_t* user_head,
						user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		int choose=user_interface();	//调用用户接口
		switch(choose)
		{
			case 1:		//查看个人信息
				look_personal_information(user_head);
				getchar();
				break;
			case 2:		//修改个人信息
				if(modify_personal_pwd(user_head)==0)
				{
					//保存
					save_all_user(user_head,USER_FILE_NAME);
					CONTINUE("修改成功,请重新登录!\n");
					getchar();
					flag=0;	
				}
				else
				{
					CONTINUE("修改失败!\n");
				}
				break;
			case 3:		//查看账户余额
				look_personal_money(user_head);
				getchar();
				break;
			case 4:		//充值账户金额
				if(replenish_personal_money(user_head)==0)
				{
					//保存
					save_all_user(user_head,USER_FILE_NAME);
					CONTINUE("充值成功!\n");
					getchar();
				}
				else
				{
					CONTINUE("充值失败!\n");
					getchar();
				}
				break;
			case 5:		//下	注
				if(buy_lottery(user_head,user_lottery_head,issue_head)==0)
				{
					save_all_user(user_head,USER_FILE_NAME);
					save_all_issue(issue_head,ISSUE_FILE_NAME);
					save_all_lottery(user_lottery_head,LOTTERY_FILE_NAME);
					CONTINUE("购买成功!\n");
					getchar();
				}
				else
				{
					CONTINUE("购买失败!\n");
				}
				break;
			case 6:		//查看彩票信息
				look_new_lottery_records(user_lottery_head,issue_head);
				CONTINUE("查看完成!\n");
				break;
			case 7:		//查询中奖记录
				look_winning_lottery( user_lottery_head);
				CONTINUE("查看完成!\n");
				break;
			case 8:		//查看购买记录
				look_lottery_records(user_lottery_head);
				CONTINUE("查看完成!\n");
				break;
			case 9:		//注销个人账户
				if(logout_user(user_head,user_lottery_head)==0)
				{
					save_all_user(user_head,USER_FILE_NAME);
					CONTINUE("注销成功!\n");
					getchar();
					flag=0;
				}
				else
				{
					CONTINUE("注销失败!\n");
				}
				break;
			case 10:	//放松一下小游戏
				game_interface_hander();
				break;
			case 0:		//返回上一级菜单
				flag=0;
				break;
			default:
				CONTINUE("输入有误,请重新输入!\n");
				break;
		
		}
	}
}

/*
	功能：管理员界面控制
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：无
*/
void user_admin_hander(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head || NULL==user_lottery_head)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		int choose=admin_interface();	//管理员界面接口
		switch(choose)
		{
			case 1:		//发行彩票
				if(issue_lottery(issue_head)==0)
				{
					save_all_issue(issue_head,ISSUE_FILE_NAME);
					CONTINUE("发行成功!\n");	
					getchar();
				}
				else
				{
					CONTINUE("发行失败!\n");
				}
				break;
			case 2:		//查看最新发行
				look_new_issue_lottery(issue_head);
				CONTINUE("查看成功!\n");
				break;
			case 3:		//查询彩民
				if(query_user(user_head,user_lottery_head)==0)
				{
					CONTINUE("查询成功!\n");
					getchar();
				}
				else
				{
					CONTINUE("查询失败!\n");
					getchar();
				}
				break;
			case 4:		//彩民余额排序
				sort_user_money(user_head);
				save_all_user(user_head,USER_FILE_NAME);
				print_user_link(user_head);
				CONTINUE("排序完成!\n");
				break;
			case 5:		//查看所有用户
				print_user_link(user_head);
				CONTINUE("查看完成!\n");
				break;
			case 6:		//查看所有用户的购买记录
				look_all_user_lottery(user_lottery_head);
				CONTINUE("查看完成!\n");
				break;
			case 0:		//返回上一级菜单
				flag=0;
				break;
			default:
				CONTINUE("输入有误,请重新输入!\n");
				break;
		}
	
	}

}

/*
	功能：公证员界面控制
	参数：user_head 用户链表头节点 user_lottery_head 彩票链表头节点 issue_head 每期彩票头节点
	返回值：无
*/
void user_worker_hander(user_head_t* user_head,user_lottery_head_t* user_lottery_head,issue_head_t* issue_head)
{
	if(NULL==user_head || NULL==user_lottery_head || NULL==issue_head)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		int choose=worker_interface();	//公证员界面接口
		switch(choose)
		{
			case 1:		//彩票开奖
				if(open_lottery(user_head,user_lottery_head,issue_head)==0)
				{
					save_all_user(user_head,USER_FILE_NAME);
					save_all_issue(issue_head,ISSUE_FILE_NAME);
					save_all_lottery(user_lottery_head,LOTTERY_FILE_NAME);
					CONTINUE("开奖成功!\n");
					getchar();
				}
				else
				{
					CONTINUE("开奖失败!\n");
					getchar();
				}
				break;
			case 2:		//查看历史发行
				look_history_issue_lottery(issue_head);
				CONTINUE("查看完成!\n");
				break;
			case 3:		//查看中奖记录
				look_all_winning_lottery(user_lottery_head);
				CONTINUE("查看完成!\n");
				break;
			case 0:		//返回上一级菜单
				flag=0;
				break;
			default:
				CONTINUE("输入有误,请重新输入!\n")
				break;
		}
	
	}

}





