# SHELL学习笔记

#
*作者：SY*
*2017-1-24 09:55:39*
##

+ 知识点
	+ 编辑器
		+ 使用VI、VIM可以编写源代码。

	+ SHELL文件特点
		+ 以 `#!/bin/bash` 或者 `#!/bin/sh`作为第一行，表示他是shell可执行文件
		+ 文件编写完毕，使用 `chmod + x <filename>`增加可执行权限 

+ 符号
	+ `$@`
		表示所有命令行输入参数
		如：`./test 1 2 3`
		$@："1" "2" "3"

	+ `$*`
		表示将所有输入参数作为一个字符串
		如：`./test 1 2 3`
		$@:"1 2 3"
	+ `$#`
		表示输入参数的个数
		如：`./test 1 2 3`
		$#：3

	+ `$n`
		n=1,2,3...
		表示取命令行第n个参数	

	+ `"" ‘’`：使用引号可以防止*(通配符)扩展
		如：`echo *.sh`，其中*将被替换为文件名
		使用 `echo “*.sh”`，将打印 `*.sh`

	

+ 语法[syntax]
	+ 注释
		`#` 后面跟上的是注释 

	+ printf 
		格式：
		`printf "格式化字符串" 参数列表`
		解释：参数列表中间使用空格隔开
		例程：
		```C
		printf "%s = %d\n" "孙宇" 26
		```

	+ 变量
		格式：
		```C
		varname = value
		```
		解释：
		1. 默认情况下,SHELL的变量全部都是字符串
		2. 取出变量使用$varname
		3. `=`两边不能含有空格
		例程：
		```C
		value = 1 + 1
		echo $value
		```

	+ 表达式
		由于SHELL里面变量赋值默认是字符串，因此不能进行数学运算，需要使用C风格表达式
		格式：
		`((表达式))`
		例程：
		```C
		value=1
		((value+=1))
		echo $value
		```

	+ 小括号()
		小括号的3种用法：
		1. 命令组
		示例：
		```C
		a=1
		(a=2 ; echo $a)
		echo $a

		> 2
		> 1
		```
		2. 命令替换
		语法为 $(command)，替代传统的 “`command`”，可能有 Shell 不支持。
		命令替换是指 Shell 会预先扫描一遍脚本，发现命令替换的结构，将其中的命令执行一次，
		得到其标准输出，再将此输出放到原来命令替换的位置，执行替换后的脚本。
		3. 数组初始化
		示例：
		`arr=(1,2,3)`

		+ &&
		+ 格式
		```C
		语句1 && 语句2
		```
		解释：
		只有语句1为真，则执行语句2
	
		例程：
		```C
		1 #!/bin/sh
		2 
		3 path="/etc/rc.d/rc.local"
		4 [ -r $path ] && echo $path"是可读的文件"
		``` 
	+ ||
		+ 格式
		```C
		语句1 || 语句2
		```
		解释：
		只有语句1为假，才执行语句2
		例程：
		```C
		1 #!/bin/bash
		2 
		3 path="/etc/rc.d/rc.local"
		4 [ -x $path ] || echo $path"不可执行"
		5 
		6 path="/etc/vimrc"
		7 [ -x $path ] || echo $path"不可执行"
		```
	
	+ []
		解释：
		1. 两个符号左右都要有空格分隔
		2. [ ] 中字符串或者${}变量尽量使用"" 双引号扩住，避免值未定义引用而出错
	+ [[]]
		1. 	内部可以使用 &&  || 进行逻辑运算

+ 流程控制	
	+ if语句
		格式：
		```C
		if
			判断命令，可以有很多个，真假取最后的返回值
		then
			如果前述为真做什么
		elif
			可以再来个判断
		then
			如果前述为真做什么
		else
			如果全都不行做什么
		fi
		```
		解释：
		大部分情况下，可以使用[ ... ]进行条件测试语句
		`-e filename` 如果 filename存在，则为真
		`-d filename` 如果 filename为目录，则为真 
		`-f filename` 如果 filename为常规文件，则为真
		`-L filename` 如果 filename为符号链接，则为真
		`-r filename` 如果 filename可读，则为真 
		`-w filename` 如果 filename可写，则为真 
		`-x filename` 如果 filename可执行，则为真
		`-s filename` 如果文件长度不为0，则为真
		`-h filename` 如果文件是软链接，则为真
		`"$a" == "$b"`如果a和b相等，则为真
		`-n "$var"`   判断 $var 变量是否有值
		`filename1 -nt filename2` 如果 filename1比filename2新，则为真。
		`filename1 -ot filename2` 如果 filename1比 filename2旧，则为真。
		`-eq` 等于
		`-ne` 不等于
		`-gt` 大于
		`-ge` 大于等于
		`-lt` 小于
		`-le` 小于等于
		至于！号那就是取非
		例程：
		```C
		1 #!/bin/bash
		2 
		3 #测试文件是否存在
		4 filepath="/etc/rc.d/rc.local"
		5 if [ -e $filepath ];
		6 then
		7     echo $filepath "文件存在"
		8 else
		9     echo $filepath "文件不存在"
		10 fi
		11 
		12 filepath="etc/123"
		13 if [ -e $filepath ];
		14 then
		15     echo $filepath "文件存在"
		16 else
		17     echo $filepath "文件不存在"
		18 fi
		```

	+ case语句
		格式：
		```C
		case $变量 in
		语句1)
		;;
		语句2)
		;;
		esac
		```
		解释：
		case表达式可以用来匹配一个给定的字符串，而不是数字
		例程：
		```C
		1 #!/bin/bash
		2 
		3 file_type=$(file $1)
		4 case $file_type in
		5 "$1: RAR archive data,"*)
		6     unrar x $1;;
		7 "$1: Zip archive data,"*)
		8     unzip $1;;
		9 *)
		10     echo "不支持该种格式的压缩文件";;
		11 esac
		```
		其中 `$1`代表命令行中的第一个参数

	+ Select选择语句
		格式：
		```C
		select var in item1 item2 item3: do
		...
		break;
		done
		```
		解释：
		选择其中一个选项，回车确认！
		例程：
		```C
		1 #!/bin/bash
		2 
		3 echo "what is your favorite OS:"
		4 
		5 select var in "Linux" "Windows" "MAC" "Other";
		6 do
		7 break;
		8 done
		9 
		10 echo "you select OS is $var !"
		```
		显示：
		```C
		[root@SY shell]# ./select.sh  
		what is your favorite OS:
		1) Linux
		2) Windows
		3) MAC
		4) Other
		#? 2
		you select OS is Windows!
		```
		
	+ while
		格式：
		```C
		while ...; do
		...
		done
		```
		解释：一直循环，直至条件为假，或者遇到break跳出循环
		例程：
		```C
		1 #!/bin/bash
		2 
		3 val=0
		4 while ((val < 5)); do
		5 ((val++))
		6 echo $val
		7 done 
		```
		结果：
		```C
		1
		2
		3
		4
		5
		```

	+ for
	格式：
	```C
	for var in item1 item2 item3; do
	...
	done
	```
	解释：
	for循环会查看一个字符串列表（字符串用空格分隔），并将其赋给一个变量
	示例：
	```C
	1 #!/bin/bash
	2 
	3 for var in 1 2 3; do
	4 echo $var
	5 done
	```
	结果：
	```C
	1
	2
	3
	```

+ 帮助文档（Here Document）
	+ 格式
	```C
	<< 提示符
	...
	提示符
	```
	例程
	```C
	1 #!/bin/bash
	2 
	3 if [ $# -lt 2 ]; then
	4 cat << HELP
	5 you have to input one parameter!
	6 FORMATE: ./help para1 para2
	7 HELP
	8 
	9 exit 0
	10 
	11 else
	12 echo "输入正确, Bye!"
	13 fi
	```
	结果：
	```C
	[root@SY shell]# ./help.sh 1 
	you have to input one parameter!
	FORMATE: ./help para1 para2
	```

+ 函数
	格式：
	```C
	func() {
	...
	}
	```
	例程
	```C
	1 #!/bin/bash
	2 
	3 help() {
	4 cat << HELP
	5 titlebar -- change the name of an xterm
	6 
	7 USAGE:
	8     titlebar [-h] "string_for_titlebar"
	9 OPTION: 
	10     -h: help documents
	11 EXAMPLE:
	12     titlebar "SY"
	13 HELP
	14 
	15 exit 0
	16 }
	17 
	18 if [[ $1 == '' || $1 == "help" ]]; then
	19     help
	20 fi
	21 
	22 echo "Change the titlebar to "$1!
	```

	
	 	


