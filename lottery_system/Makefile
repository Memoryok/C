#项目名称：彩票管理系统
#作    者：Memory
#开始时间：2019.09.12
#完成时间：2019.09.20
#调试时间：2019.09.22
#更新时间：2019.09.23
#项目周期：2019.09.12-2019.09.24
#项目语言：C语言
#项目环境：Linux系统
#当前版本：lottery_system 2.0


bin/lottery:lottery.c obj/admin.o obj/common.o obj/controller.o obj/game.o obj/issue_link.o obj/user.o obj/user_link.o obj/user_lottery.o obj/user_lottery_link.o obj/view.o obj/worker.o
	gcc lottery.c obj/admin.o obj/common.o obj/controller.o obj/game.o obj/issue_link.o obj/user.o obj/user_link.o obj/user_lottery.o obj/user_lottery_link.o obj/view.o obj/worker.o -o bin/lottery -Iinclude -Wall


obj/admin.o:src/admin.c
	gcc -c src/admin.c -o obj/admin.o -Iinclude -Wall
obj/common.o:src/common.c
	gcc -c src/common.c -o obj/common.o -Iinclude -Wall
obj/controller.o:src/controller.c
	gcc -c src/controller.c -o obj/controller.o -Iinclude -Wall
obj/game.o:src/game.c
	gcc -c src/game.c -o obj/game.o -Iinclude -Wall
obj/issue_link.o:src/issue_link.c
	gcc -c src/issue_link.c -o obj/issue_link.o -Iinclude -Wall
obj/user.o:src/user.c
	gcc -c src/user.c -o obj/user.o -Iinclude -Wall
obj/user_link.o:src/user_link.c
	gcc -c src/user_link.c -o obj/user_link.o -Iinclude -Wall
obj/user_lottery.o:src/user_lottery.c
	gcc -c src/user_lottery.c -o obj/user_lottery.o -Iinclude -Wall
obj/user_lottery_link.o:src/user_lottery_link.c
	gcc -c src/user_lottery_link.c -o obj/user_lottery_link.o -Iinclude -Wall
obj/view.o:src/view.c
	gcc -c src/view.c -o obj/view.o -Iinclude -Wall
obj/worker.o:src/worker.c
	gcc -c src/worker.c -o obj/worker.o -Iinclude -Wall


.PHONY:clean
clean:
	rm bin/*
	rm obj/*



	
	
	
