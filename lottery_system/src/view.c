#include<stdio.h>
#include<stdlib.h>
#include"view.h"
#include"common.h"

/*
	功能：主界面接口
	参数：无
	返回值：操作选项
*/
int main_interface(void)
{
	system("clear");
	printf("\t*************************\n");
	printf("\t*\t欢迎进入\t*\n");
	printf("\t*   中国福利彩票中心\t*\n");
	printf("\t*************************\n");
	printf("\t*\t\t\t*\n");
	printf("\t*      1.用户登录 \t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*      2.新用户注册 \t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*      3.管理员登录 \t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*      4.公证员登录 \t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*      0.退出系统 \t*\n");
	printf("\t*************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);		
	//清理缓存
	FLUSH;
	return choose;	
}

/*
	功能：用户界面接口
	参数：无
	返回值：操作选项
*/
int user_interface(void)
{
	system("clear");
	printf("\t*************************\n");
	printf("\t*   欢迎进入用户界面\t*\n");
	printf("\t*************************\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    1.查看个人信息\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    2.修改个人密码\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    3.查看账户余额\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    4.充值账户金额\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    5.下	 注\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    6.查看彩票信息\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    7.查询中奖记录\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    8.查看购买记录\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    9.注销个人账户\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    10.放松一下\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    0.返回上一级菜单\t*\n");
	printf("\t*************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);	
	//清理缓存
	FLUSH;
	return choose;	
}

/*
	功能：管理员界面接口
	参数：无
	返回值：操作选项
*/
int admin_interface(void)
{
	system("clear");
	printf("\t*************************\n");
	printf("\t*   欢迎进入管理员界面\t*\n");
	printf("\t*************************\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    1.发行彩票\t\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    2.查看最新发行\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    3.查询用户\t\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    4.彩民余额排序\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    5.查看所有用户\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    6.查看彩票记录\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    0.返回上一级菜单\t*\n");
	printf("\t*************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);		
	//清理缓存
	FLUSH;
	return choose;
}

/*
	功能：公证员界面接口
	参数：无
	返回值：操作选项
*/
int worker_interface(void)
{
	system("clear");
	printf("\t*************************\n");
	printf("\t*   欢迎进入公证员界面\t*\n");
	printf("\t*************************\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    1.彩票开奖\t\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    2.查看历史发行\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    3.查看中奖记录\t*\n");
	printf("\t*\t\t\t*\n");
	printf("\t*    0.返回上一级菜单\t*\n");
	printf("\t*************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);		
	//清理缓存
	FLUSH;
	return choose;
}







