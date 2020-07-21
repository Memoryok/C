#include<stdio.h>
#include<string.h>
#include"common.h"
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<termios.h>
#include<assert.h> 

/*
	功能：用户须知
	参数：无
	返回值：操作选项
*/
int instructions(void)
{
	system("clear");
	printf("\t*****************************************************************\n");
	printf("\t*		            用户须知\t\t\t\t*\n");
	printf("\t*****************************************************************\n");
	printf("\t*尊敬的用户:\t\t\t\t\t\t\t*\n");
	printf("\t*    您好!非常感谢您体验本产品,为了方便您的学习和使用,请您仔细阅*\n");
	printf("\t*读本用户须知:\t\t\t\t\t\t\t*\n");
	printf("\t*\t\t\t\t\t\t\t\t*\n");
	printf("\t*    1.本产品属于学习项目,禁止用于商业用途及有关金钱交易,禁止用 *\n");
	printf("\t*于违反国家法律的操作;\t\t\t\t\t\t*\n");
	printf("\t*    2.本产品中所涉及到金钱均属于虚拟数字,不存在真实交易,用户可 *\n");
	printf("\t*以随时体验产品中各项服务;\t\t\t\t\t*\n");
	printf("\t*    3.因本产品为学习软件,请不要透露个人真实信息;\t\t*\n");
	printf("\t*    4.本产品彩票购买规则:① 用户每次购买最多可以买5注,每注7个球,*\n");
	printf("\t*球号为1-33号不可越界,但可以多次购买;② 用户每次购买不管注数多少,*\n");
	printf("\t*不重复中奖,每一张彩票只取中奖最大的奖项;③ 设立了5个奖项:一等奖 *\n");
	printf("\t*5000元,二等奖3000元,三等奖1000元,四等奖100元,五等奖50元;④ 7个球*\n");
	printf("\t*全中为一等奖;中6个球为二等奖;中5个球为三等奖;中4个或3个球为四等*\n");
	printf("\t*奖;中2个球为五等奖;否则不中奖;\t\t\t\t\t*\n");
	printf("\t*    5.本产品功能设计由新人所写,中间有可能存在BUG,请用户在使用过*\n");
	printf("\t*程中遇到问题,请反馈给程序设计者,多谢支持和理解!\t\t*\n");
	printf("\t*\t\t\t\t\t\t\t\t*\n");
	printf("\t*\t\t\t\t\t\t作者:Memory\t*\n");
	printf("\t*\t\t\t\t\t\t\t\t*\n");
	printf("\t*     	是否继续登录:	1.继续	2.退出\t\t\t\t*\n");
	printf("\t*\t\t\t\t\t\t\t\t*\n");
	printf("\t*****************************************************************\n");
	printf("\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);

	return choose;
}

/*
	功能：选项选择确认
	参数：无
	返回值：选择确认结果
*/
int confirm_select(void)
{
	system("clear");	//清屏
	printf("\t***********\n");
	printf("\t1.确定退出!\n");
	printf("\t2.返    回!\n");
	printf("\t***********\n");
	int choose=0;
	printf("请选择:");
	scanf("%d",&choose);
	
	//清除缓存
	FLUSH;
	return choose;
}

/*
	功能：注册账号
	参数：字符串地址 字符串长度
	返回值：字符串地址
*/
void input_name(char* s,int size)
{
	if(NULL==s)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		printf("请输入用户名:");
		fgets(s,size,stdin);
		if(s[strlen(s)-1]=='\n')
		{
			s[strlen(s)-1]='\0';
		}
		else
		{
			FLUSH;
		}
		if(strlen(s) >= 15)
		{
			printf("你输入的用户名过长,请重新输入!\n");
		}
		else if(strcmp(s,"admin")==0 || strcmp(s,"worker")==0)
		{
			printf("此用户名禁止注册,请重新输入!\n");
		}
		else
		{
			flag=0;
		}
	}
}

/*
	功能：注册密码
	参数：字符串地址 字符串长度
	返回值：字符串地址
*/
void input_pwd(char* s,int size)
{
	if(NULL==s)
	{
		return ;
	}
	int flag=1;
	while(flag)
	{
		printf("请输入密码:");
		getPassword(s);
		if(strlen(s) >= 15)
		{
			printf("你输入的密码过长,请重新输入!\n");
		}
		else if(strlen(s)<=5)
		{
			printf("你输入的密码过短,安全性低,请重新输入!\n");
		}
		else
		{
			flag=0;
		}
	}
}

/*
	功能：发送验证码
	参数：无
	返回值：0 成功 -1 失败
*/
int validata_code(void)
{
	char ary[100]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char generate[5]="";
	char entering[5]="";
	while(1)
	{
		//随机得到4位验证码
		srand(time(NULL));
		generate[0]=ary[rand()%26];
		generate[1]=ary[rand()%26+26];
		generate[2]=ary[rand()%10+52];
		generate[3]=ary[rand()%10+52];
		generate[4]='\0';
		
		printf("验证码:");
		printf("%s\n",generate);
		printf("请输入验证码:");
		scanf("%s",entering);
		
		if(strcmp(generate,entering)!=0)
		{
			printf("验证码错误,请重新输入!\n");
			if(entering[0]==27)
			{
				return -1;
			}
		}
		else
		{
			return 0;
		}
	}
}

/*
	功能：密码验证
	参数：user_pwd 密码
	返回值：0 正确 -1 不正确
*/
int pwd_verification(char* user_pwd)
{
	if(NULL==user_pwd)
	{
		return -1;
	}
	char pwd[LEN_PWD]={'\0'};
	printf("请再次输入密码:");
	getPassword(pwd);
	if(strcmp(user_pwd,pwd)==0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

//功能：密码隐藏
int getch()  
{  
	int c=0;  
	struct termios org_opts, new_opts;  
	int res=0;  

	res=tcgetattr(STDIN_FILENO, &org_opts);  
	assert(res==0);  
	memcpy(&new_opts, &org_opts, sizeof(new_opts));  
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT     | ECHOKE | ICRNL);  
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);  
	c=getchar();  
	res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);  
	assert(res==0);  
	return c;  
}  

void getPassword(char *pcPWD)
{
	int ch=0;
	int i=0;
	for(i=0;i<20;)
	{
		ch=getch();
		if(ch==-1)//当无键入时，跳出当前循环继续下一个循环
		{
			continue;
		}
		//127在键盘上是delete  8代表退格键backspace
		if((ch == 127 || ch == 8) && i>0)//当有键入时，按键delete或backspace时，删除一位
		{
			putchar('\b');	//这里是删除一个，通过输出回撤符 /b，回撤一格，
			putchar(' ');	//再显示空格符把刚才的*给盖住，
			putchar('\b');	//然后再 回撤一格等待录入。
			i--;			//减少一位
		}
		//10在键盘上代表换行(LF)，13代表回车(CR)
		//3.在不同平台，输入回车，getch()将返回不同数值，而getchar()统一返回10(即\n)
		//1)windows平台下ENTER键会产生两个转义字符 \r\n，因此getch返回13(\r)。
		//2)unix、 linux系统中ENTER键只产生 \n ，因此getch返回10(\n)。
		//3)MAC OS中ENTER键将产生 \r ，因此getch返回13(\r)。
		else if(ch==10 || ch == 13)//当键入的为换行时
		{
			pcPWD[i]='\0';//将字符串以'\0'结尾
			putchar('\n');
			return;
		}
		else if(i==0&&(ch==127 ||ch == 8))//当无键入时，按键delete或backspace时，产生警报
		{
			printf("\a");
		}
		else if(i<19)//当键入的数少于19位时每键入一个数打印一个星号覆盖
		{
			pcPWD[i]=(char)ch;
			putchar('*');
			i++;
		}
		else//当键入的数超过19位时，再次键入产生响铃
		{
			printf("\a");//响铃
		}
	}
}





