#!/bin/bash

#测试文件是否存在
filepath="/etc/rc.d/rc.local"
if [ -e $filepath ];
then
	echo $filepath "文件存在"
else
	echo $filepath "文件不存在"
fi

filepath="etc/123"
if [ -e $filepath ];
then
	echo $filepath "文件存在"
else
	echo $filepath "文件不存在"
fi

#测试是否是一个文件
filepath="/etc/rc.d/rc.local"
if [ -f $filepath ];
then
	echo $filepath "是一个文件"
else
	echo $filepath "不是一个文件"
fi

filepath="etc/rc.d"
if [ -f $filepath ];
then
	echo $filepath "是一个文件"
else
	echo $filepath "不是一个文件"
fi



