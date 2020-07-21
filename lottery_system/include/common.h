#ifndef COMMON_H_
#define COMMON_H_

#define LEN_NAME 20
#define LEN_PWD 20

#define ADMIN_NAME "admin"
#define ADMIN_PWD "123456"

#define WORKER_NAME "worker"
#define WORKER_PWD "123456"

//清理缓存
#define FLUSH {	char c=0;	while((c=getchar())!='\n'  && c!=EOF);}

//暂停
#define CONTINUE(X) {	printf(X);	getchar();}

//用户文件名
#define USER_FILE_NAME "data/user.bin"

//彩票文件名
#define LOTTERY_FILE_NAME "data/lottery.bin"

//每期彩票文件名
#define ISSUE_FILE_NAME "data/issue.bin"

/*
	功能：选项选择确认
	参数：无
	返回值：选择确认结果
*/
int confirm_select(void);

/*
	功能：注册账号
	参数：字符串地址 字符串长度
	返回值：字符串地址
*/

void input_name(char* s,int size);

/*
	功能：注册密码
	参数：字符串地址 字符串长度
	返回值：字符串地址
*/
void input_pwd(char* s,int size);

/*
	功能：发送验证码
	参数：无
	返回值：0 成功 -1 失败
*/
int validata_code(void);

/*
	功能：密码验证
	参数：pwd 密码
	返回值：0 正确 -1 不正确
*/
int pwd_verification(char* pwd);

/*
	功能：用户须知
	参数：无
	返回值：操作选项
*/
int instructions(void);

//功能：密码隐藏
int getch();
void getPassword(char *pcPWD);






#endif
