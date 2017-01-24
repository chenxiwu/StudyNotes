# Makefile学习笔记

#
*作者：SY*
*2017-1-19 15:36:39*
##

简介：Makefile可以打包处理程序，包括：编译、连接。
+ 规则
	1 格式
		目标[target] ... : 依赖[prerequisites] ...
		<TAB>命令[command]
		+ target：表示转换的目标文件
		+ prerequisites：表示依赖文件
		+ command：表示转换的命令

+ 命令
	1. 变量
		+ 声明变量：var = main.o
		+ 使用变量：$(var)或者${var}

	2. 参数
		+ -E：预处理后即停止，不进行编译，生成.i文件。
		+ -S：编译后即停止，生成.s文件。
		+ -c：编译指令，不连接，生成.o文件
		+ -o：连接指令，生成可执行文件。	
		+ -Wall：打印警告信息。
		+ -I：将指定路径作为第一个头文件路径。
		+ -g：产生调试信息
		+ -O：优化选项[-O1,-O2,-O3]，一般使用-O2。-O0代表不优化。
		+ -l：用来指定程序要链接的库
		+ -L：用来制指定库文件所在的目录名
		+ -C：切换到指定目录再执行 make 过程，makefile 在这个指定目录里面。

	3. 关键字
		+ wildcard：扩展通配符
			在Makefile规则中，通配符*. 会被自动展开。但在变量的定义和函数引用时，通配符将失效。
			这种情况下如果需要通配符有效，就需要使用函数“wildcard”。
			一般我们可以使用“$(wildcard *.c)”来获取工作目录下的所有的.c文件列表。
		+ notdir：去除路径
		+ patsubst：替换通配符
			格式：$(patsubst <pattern>,<replacement>,<text> ) 
			功能：查找<text>中的单词单词以“空格”、“Tab”或“回车”“换行”分隔. 是否符合模式<pattern>，
				如果匹配的话，则以<replacement>替换。这里，<pattern>可以包括通配符“%”，表示任意长度的字串。
				如果<replacement>中也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所代表的字串。
				可以用“\”来转义，以“\%”来表示真实含义的“%”字符. 
				返回：函数返回被替换过后的字符串。
			示例：
				$(patsubst %.c,%.o,x.c.c bar.c)
				把字串“x.c.c bar.c”符合模式[%.c]的单词替换成[%.o]，返回结果是“x.c.o bar.o”
	+ 符号
		+ `$@`：表示目标文件
		+ `$^`：表示所有依赖文件一般在生成目标文件时使用. 
		+ `$<`：表示第一个依赖文件一般在生成中间文件时使用. 

	+ 符号
		+ `=` ：是最基本的赋值，其值取决于整个Makefile展开后，变量的值。
		+ `:=`：是覆盖之前的值，其值取决于它在Makefile所在的位置。
		+ `?=`：是如果没有被赋值过就赋予等号后面的值
		+ `+=`：是添加等号后面的值	

	+ 扩展
		+ -std=gnu99，使用基于GNU扩展的标准

+ 编译
	1. 命令：arm-linux-gcc
		+ 针对arm平台进行编译
	2. 例程：
		+ arm-linux-gcc -o main main.c
		+ arm-linux-gcc main.c -o main

+ 连接
	1. 命令：arm-linux-ld
	2. 针对arm平台的连接
	3. 可以添加-T选项，指定连接地址信息，如arm-linux-ld -Ttext 	0x40000000 -o main.c main.elf

+ 常见错误
	1. 问题：编译器显示错误"led.S: file not recognized: File format not recognized"？
	> 原因：源文件：
	```C
	led.bin : led.S
	arm-linux-ld -Ttext 0x40000000 -o led.elf $^
	```
	> 解决：将led.S改为led.o
