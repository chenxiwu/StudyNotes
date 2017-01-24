#!/bin/bash

file_type=$(file $1)
case $file_type in
"$1: RAR archive data,"*)
	unrar x $1;;
"$1: Zip archive data,"*)
	unzip $1;;
*)
	echo "不支持该种格式的压缩文件";;
esac
