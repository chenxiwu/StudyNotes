# MySQL学习笔记

#
*作者：SY*
*2017-3-5 16:38:16*
##

+ 安装数据库
	1. 选择手动安装，选择X64
	2. 安装完毕，添加环境变量：`C:\Program Files\MySQL\MySQL Server 5.7\bin`
	3. 测试MySQL，命令行输入：`mysql -u root -p`，再输入密码，如果成功进入MySQL说明安装成功！


+ 常用操作
	+ 退出编辑状态
		1. MySQL默认使用`;`结束一行，如果未遇到`;`，当用户按下回车符。将显示->
		有两种方式可以取消提示符。
		+ 输入`\c`
		+ 输入`;`
	+ 显示当前数据库
		1. show databases;

	+ 退出数据库
		1. exit

	+ 进入数据库
		1. mysql -uroot -p
		2. 输入密码：********

	+ 新建数据库
		1. create database student;

	+ 删除数据库
		1. drop database student;

	+ 查看新建数据库的存储位置
		1. mysql> show variables like '%datadir%';
