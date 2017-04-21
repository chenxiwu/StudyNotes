#Linux学习笔记

#
*作者：SY*
*2016-8-28 10:13:13*
##

+ 学习步骤
	+ 基础知识：Linux常用命令 + 汇编 + Makefile + DNW + MiniCOM + SSH + VIM + 交叉编译器+连接脚本
	+ 裸机程序
	+ 移植U-boot
	+ 移植内核
	+ 移植根文件系统
	+ 移植网络文件系统
	+ 设备驱动

+ Linux文件目录
	+ 目录树
		opt：安装软件的目录

+ 命令集
	+ Linux-Ubuntu
		+ 切换用户
			+ 重置root密码：
				1. 输入 "sudo passwd root"
				2. 输入密码
		
			+ 切换为root用户
				1. 输入 "su root" 或者 输入 "su"
				2. 输入密码
			
			+ 切换为一般用户
				1. 输入 "su sy(用户名)"
		
		+ 软件
			+ 安装：输入"apt-get install + 软件名"
			+ 卸载：输入“apt-get purge + 软件名”
		
		+ 文件夹
			+ 新建文件夹
				1. 输入"mkdir + 名称"
			
			+ 删除空文件夹
				1. 输入"rmdir + 名称"
			
			+ 删除文件夹
				1. 输入"rm -rf + 名称"。 -r代表递归删除; -f代表不提示，强制删除;
			
		+ 文件
			+ 新建文件
				1. 输入"touch + 名称"
			
			+ 删除文件
				1. 输入"rm -rf + 名称"。 -r代表递归删除; -f代表不提示，强制删除;
		
		+ 解压缩
			+ 参数
				1. "z"：使用gzip处理
				2. "j"：使用bzip2处理
				3. "c"：压缩
				4. "x"：解压缩
				5. "f"：表示文件
			
			+ gzip
				1. 压缩文件：zcf
					格式：tar [参数] 目标文件 源文件
					例程：tar zcf xxx.tar.gz xxx.txt 	压缩文件
						  tar zcf xxx.tar.gz xxx/		压缩文件夹
				2. 解压缩文件：zxf
					格式：tar [参数] 源文件 目标文件
					例程：tar zxf xxx.tar.gz 			解压缩文件到当前目录
						  tar zxf xxx.tar.gz -C ../		解压缩到上层目录
			+ bzip2压缩率更高，速度更慢. 
				1. 压缩文件：-jcvf
				2. 解压缩文件：-jxvf
			
			+ zip
				1. 压缩文件
					zip 目标文件名 源文件名
				2. 解压缩文件
					unzip 源文件名

			+ unrar
				1. 解压缩
					`unrar x <filename>：`解压到当前路径
				
		+ 增加用户
			+ 新建用户
				1. useradd + [用户名]
				2. 新建用户并加入组 useradd + [-g] + [group] + [username]
				
			+ 增加密码
				1. passwd + [用户名]
			
			+ 删除用户
				1. userdel + [用户名]
			
			+ 增加组
				1. groupadd
			
			+ 删除组
				1. groupdel
			
			+ 给已有用户增加工作组
				1. usermod -G + [group] + [username]
			
			+ 从组中删除用户
				1. gpasswd -d + [username] + [group]
			
		+ 查看文件内容
			+ cat + [parameter] + filename
				1. -n：附加行号
			
			+ more + 文件名
				1. 按下“空格键”可以快速跳转到下一页。
			
			+ 逆序查看内容：tac + 文件名
			
			+ head + [OPTION] + [FILE]
				1. 查看前x行内容：head -nx file.txt
			
			+ tail + [OPTION] + [FILE]
				1. 查看倒数x行内容：tail -nx file.txt
			
		+ dpkg	
			+ -l：显示所有已安装的软件
			+ -P：删除一个软件包，包括配置信息
			
		+ 查看内核版本
			+ uname -r
			
		+ 查看发行版本
			+ cat /etc/issue
			+ lsb_release -a
		
		+ 打印开机信息
				1. dmesg
		
		+ 驱动模块
			+ 显示模块：lsmod
			+ 加载模块：insmod
			+ 卸载模块：rmmod
		
		+ 串口/USB有效端口
			+ 查询串口信息：dmesg | grep tty
		
		+ 添加环境变量
			+ 输入"sudo vim /etc/profile"
			+ 在文件末尾添加："export PATH=$PATH:/opt/FriendlyARM/toolschain/4.5.1/bin“
			+ 使环境变量立即生效："source /etc/profile"
			
		+ cp 
			+ cp + 源文件 + 目标文件：拷贝源文件到目标文件
			+ cp -R 源目录 + 目标目录：拷贝源目录到目标目录
		
		+ man
			描述：相当于帮助功能
				man的级别：
				1 ： 查看命令的帮助
				2 ： 查看可被内核调用的函数的帮助
				3 ： 查看函数和函数库的帮助
				4 ： 查看文件的帮助主要是/dev目录下的文件. 
				5 ： 查看配置文件的帮助
				6 ： 查看游戏的帮助
				7 ： 查看其它杂项的帮助
				8 ： 查看系统管理员可用命令的帮助
				9 ： 查看和内核相关文件的帮助
			用法：man + <level> + 关键字，其中级别省略表示级别1
			例程：man 3 open，查看open函数的用法。
		
		+ 清屏
			+ clear
			+ Ctrl + l
		
		+ mount挂载 / umount卸载
			+ 假如你有一张SD卡，显示为/dev/sdb1，想要打开SD卡查看里面的文件。(/mnt目录一般作为挂载目录)
				1. 在/mnt目录新建文件夹sdcard。执行命令：mount /dev/sdb1 /mnt/sdcard，这样就可以在该目录中打开SD卡。
					其中文件夹 sdcard 称作挂载点。
				2. 查看所有挂载设备：df -h
				3. 如果想要卸载设备，通过 umount /dev/sdb1 取消挂载。
				4. 卸载提示“device is busy"，可能是你当前处于挂载点内部，需要离开挂载目录，重新执行umount。
			
		+ 查找内容
			+ find
				1. 用法：find + [path] + [-option] + [parameter]
				2. 例程：find /etc -name *.local
			
			+ grep
				1. 查找文本文件中包含某个字符的语句
					用法：grep + [关键字] + [文件名]
		
		+ 链接
			+ 硬链接：ln + 源文件 + 链接文件
				1. 相当于拷贝一份源文件，并在两者之间建立链接
			
			+ 软链接：ln + [-s] + 源文件 + 链接文件
				1. 使用ls -l 查看文件格式时，前面显示l表示链接
				2. 相当于快捷方式
			
			+ 硬链接与软链接之间的区别
				1. 如果删除源文件，硬链接仍然存在，软链接将失效。
			
		+ 修改文件权限
			+ chmod 
				1. r：读 w：写 x：执行 -：无权限
				2. 增加权限：
					chmod + [+x] + [filename]
				3. 减少权限：
					chmod + [-x] + [filename]
				4. 增加所有者权限
					chmod + [u+x] + [filename]
				
				5. 另一种方式：
					chmod + 755 + [filename]
			
		+ 修改所有者
			+ chown
				1. chown + [username] + [filename]	
			
		+ 管道
			格式：命令1 | 命令2  ... | 命令n
			解释：将上一个命令执行结果交给下一个命令执行
			+ 连接符：|
				例程：ls -R /etc | more 通过|符号，可以连接两个操作，分页打印文件。
			
		+ 字符转换
			格式：col [-option]
			
		+ 重定向
			+ `>` ：表示定向输出到文件
			+ `>>`：表示追加内容到文件		
			
		+ 计算字数
			+ wc + filename
			
		+ 群发通知
			+ wall + 内容
			+ wall + `cmd`：表示将cmd执行的结果通知所有人
				
		+ 重定向输出
			+ ls > cmd.txt：表示将所有的文件名存储到cmd.txt文件中。
			+ ls >> cmd.txt：表示追加命令执行结果到cmd.txt
		
		+ 重定向输入
			+ wall < cmd.txt：表示从cmd.txt读取数据并群发消息。	
			
		+ 查看ip地址
			+ ifconfig
			+ ip address

		+ 查看当前进程
			+ ps -ef

		+ 杀死进程
			+ kill + 进程号
		
		+ 查看系统服务
			+ 列出所有系统服务：chkconfig --list
			+ 添加系统服务： chkconfig --add
		
		+ file
			+ `file filename`：查看文件类型及信息
		
		+ 回到上一次操作的目录
			+ cd -			
		
		+ 计算文件的行号
			+ 列出文件内容，添加行号：nl + filename
		
		+ shift
			+ 命令行参数移位：执行一次shift操作，参数列表向左移动一位，
			同时参数个数减一 
			格式：shift n #n表示移位n次
	
+ Linux-fedora
	+ 安装软件
		1. 输入"yum install + 软件名"
	
	+ 防火墙
		+ 打开防火墙	 
			+ systemctl start firewalld.service
		+ 关闭防火墙
			+ systemctl stop firewalld.service
			+ setenforce 0
		+ 开机启动防火墙
			+ systemctl enable firewalld.service
		+ 开机禁止防火墙
			+ systemctl disable firewalld.service
		+ 永久关闭防火墙
			+ 进入/etc/selinux/config 把SELINUX=enforcing   改成disabled就可以了，重启电脑，永久生效
		
	+ 查看发行版本
		1. lsb_release -a
		
	+ 查看已安装的内核
		1. rpm -qa | grep kernel	
		
	+ 删除内核移除启动项. 
		1. yum remove kernel-PAE-2.6.32.11-99.fc12.i686
		
	+ 缺少某个库文件时，反向查找依赖库
		1. yum whatprovides + 缺少的库
			例如：yum whatprovides libz.so.1

+ 链接脚本
	1. 文件格式
		+ 文件名：*.lds
		+ 在等号左右必须加空格
	
	1. 常见问题
		+ 问题：arm-linux-ld:tiny4412.lds:1: ignoring invalid character `\37777777757' in expression
		> 解决：文件 *.lds不能是[UTF-8]格式，通过vim创建*.lds文件可以正常连接。打开后是[ANSI/OEM - GBK]格式。
			
+ Kconfig
	1. Kconfig是内核的配置界面的源文件，通过配置该文件可以控制配置界面的显示
		+ 符号
			1. 类型
				+ bool：布尔类型，包含y/n两个选项
				+ tristate：三态类型，包含y/n/M，其中M=模块
		
		+ select
			1. 表示反向依赖，选择该选项，将同时选中依赖的选项。
		
		+ default
			1. 默认选择
		
		+ help
			1. 帮助文档
		
		+ depends on
			1. 表示依赖条件，只有依赖的选项存在后，才能显示该选项


+ 设备驱动	
	+ Fedora平台
		+ 构建内核树
			1. 输入"yum install kernel-devel"
			2. 内核路径：/usr/src/kernels
	
	+ Ubuntu平台
		+ 配置编译环境
			1. 输入apt-get install module-assistant

	+ Tiny4412平台
		+ 步骤
			1. 本节准备介绍ARM开发板Tiny4412的驱动开发，并非裸机驱动，而是基于Linux操作系统的驱动程序。
			友善之臂已经将驱动程序和内核一起编译，我们为了学习底层驱动程序，因此采用动态加载的方式编写驱动代码。
			2. 驱动程序是依赖于具体某一个内核版本的，因此我们必须准备一份与开发板内核版本一致的Linux源码，在光盘中
				文件名：“Linux-3.5-20151029.tgz”。解压。
			3. 输入 cp tiny4412_linux_defconfig .config
			4. 输入 make 编译内核
			5. 输入 make modules_install，将编译生成的modules添加到电脑端内核目录 /lib/modules/3.5.0-FriendlyARM
			6. 编写驱动源文件及Makefile，生成xxx.ko文件
			7. 通过ssh/
			8. 等方式传输到开发板。
			8. 在开发板中，输入insmod xxx.ko加载驱动
			9. 通过dmesg | tail -10，查看最后10个加载的驱动，看是否加载成功。也可以使用lsmod查看。
			10. 通过rmmod xxx 即可卸载驱动。
			11. 编写相应的应用层文件，调用编写的驱动程序，验证驱动是否正常工作。
			
	+ 常见问题
		+ 问题：在开发板中使用modinfo xxx.ko，提示：modinfo: can't open '/lib/modules/3.5.0-FriendlyARM/modules.dep': No such file or directory
		> 解决：进入/lib/modules/3.5.0-FriendlyARM/,输入cp modules.dep.bb modules.dep
		
		+ 问题：在开发板中，通过insmod可以成功加载驱动，通过rmmod不能卸载驱动，lsmod仍然可以找到驱动？
		> 解决：编写一个rmmod的驱动程序，通过arm-linux-gcc -static -o rmmod rmmod.c 编译，将文件传输到开发板./sbin目录下。
			再次使用rmmod即可成功卸载驱动。
		
		+ 问题：编写led驱动，下载到开发板，使用insmod提示：insmod: can't insert 'bsp_led.ko': Device or resource busy
		> 原因：
			1. 使用dmesg | tail -10，可以发现程序执行 gpio_reques() 失败，由于开发板默认已经配置led引脚，因此请求失败。
			2. 如果采用静态分配的ID，可能存在冲突。
		> 解决：
			1. 去掉 gpio_reques() gpio_free()相关语句。
			2. 修改主ID号，直至不产生冲突。
		
		+ 问题：测试LED驱动时，友善之臂已经在内核中添加LED驱动程序，以及应用程序，干扰了试验结果，怎么解决？
		> 解决：进入 /etc/init.d，打开rc.S文件，找到语句/etc/rc.d/init.d/leds start 前面添加#，即可解决。

+ 概念
	+ 设备类型
		1. Linux中一切皆是文件！
		2. Linux将设备分为3类，字符设备，块设备，网络设备。
		3. 任何一种设备类型都可以在/dev目录中，对应一个文件。
	
	+ 字符设备
		1. 是指只能一个字节一个字节读写的设备，不能随机读取设备内存中的某一数据，读取数据需要按照先后数据。字符设备是面向流的设备，常见的字符设备有鼠标、键盘、串口、控制台和LED设备等。
		2. 设备号
			+ 分为主设备号，和次设备号。
			+ 一个完整的设备号为无符号32位整形，其中主设备号为高12位，次设备号为低20位。
			+ 设备号可以静态申请，也可以动态申请。
			+ 加载驱动后，向内核注册设备，可以使用cat /proc/devices查看分配的主设备号

	+ 块设备
		1. 是指可以从设备的任意位置读取一定长度数据的设备。块设备包括硬盘、磁盘、U盘和SD卡等。
	
	+ 网络设备
		1. 包括常见的以太网。
	
	+ 符号：
		1. 在Makefile中，常见的符号：
			+ obj-m：表示编译成模块
			+ boj-y：表示编译进内核
			+ obj-n：表示不编译进内核	
+ Linux
	首先需要能进入U-Boot环境，参考“烧录Uboot到eMMC”
	+ 生成zImage
		1. 将内核源文件解压缩。得到文件夹“linux-3.5”
		2. 进入"linux-3.5"，输入 cp tiny4412_linux_defconfig .config
		3. 输入make menuconfig，在Linux内核配置界面，必须关闭trustZone，否则进不了系统。具体目录在：System Type->Support TrustZone-enabled Trusted Exception Environment
			取消勾选。
		4. 输入make
		5. 遇到警告：
		```C
		Can't use 'defined(@array)' (Maybe you should just omit the defined()?) at kernel/timeconst.pl line 373
		解决：删除
			@val = @{$canned_values{$hz}};
			if (!defined(@val)) {
			@val = compute_values($hz)?
			} 
			在output前面加入
			$cv = $canned_values{$hz};
			@val = defined($cv) ? @$cv : compute_values($hz);
		```
		6. 等待结束，在./arch/arm/boot目录得到zImage文件。

+ 烧录Linux
	+ 生成uImage
		+ 方式一 
			1. 进入uboot文件夹，找到./tools目录中mkimage文件，将该文件复制到/usr/local/bin文件夹中。
			2. 进入./linux-3.5 目录下，输入 make uImage
			3. 在./arch/arm/boot目录下，可以发现uImage映像文件。
		
		+ 方式二
			1. 进入uboot文件夹，找到./tools目录中mkimage文件，将该文件复制到/usr/local/bin文件夹中。
			2. 进入./linux-3.5 目录下，输入 
			```C
			mkimage -A arm -O linux -T kernel -C none -a 40008000 -e 40008000  -n linux-3.5.0 -d arch/arm/boot/zImage uImage
			``` 
			这样就在当前目录生成uImage文件。
	
	+ 将uImage发送到uboot
		1. 进入uboot环境，通过dnw发送uImage到内存地址0x40008000,该地址在uboot环境下，输入printenv可以看到。
		2. bootm 40008000进入内核。
		3. 实测这种方式不能进入系统。	
			
	+ 使用fastboot烧录内核
		1. 参考博文：http://blog.csdn.net/lizuobin2/article/details/52825033
		大致流程：
			1. 格式化eMMC
				fdisk -c 1 320 2057 520		
			2. 格式化分区
				fatformat mmc 1:1
				fatformat mmc 1:2
				fatformat mmc 1:3
				fatformat mmc 1:4
			3. bl1.bin, bl2.bin, u-boot.bin, tzsw.bin烧录到eMMC中
			4. 将拨动开关拨到eMMC启动，进入U-Boot	
			4. 设置环境变量
				> setenv bootargs root=/dev/mmcblk0p1 rootfstype=ext4 console=ttySAC0,115200 init=/linuxrc ctp=2 skipcali=y
				 或者setenv bootargs console=ttySAC0,115200n8 noinitrd root=/dev/mmcblk0p1 rw rootfstype=ext4 init=/linuxrc lcd=S700 ctp=2
				> saveenv
			5. 输入fastboot，进入fastboot环境
			6. 在电脑端Linux，输入：
				> fastboot flash kernel zImage (来自Linux make后的镜像)
				> fastboot flash fat rootfs_qtopia_qt4.img来自光盘Linxu文件夹. 
				> fastboot flash ramdisk ramdisk-u.img来自光盘Linxu文件夹. 
			7. 输入reset重启开发板，成功烧录Linux
			
+ android
	+ 生成zImage
		1. 将内核源文件解压缩。得到文件夹“linux-3.0.86-20150324.tgz”
		2. 进入"linux-3.0.86"，输入 cp tiny4412_android_defconfig .config
		3. 进入make menuconfig 关闭trust zone
		4. 输入 make (或者make -j4，加快编译速度. 
		5. 等待结束，在./arch/arm/boot目录得到zImage文件。

	+ 烧录安卓
		+ 参考博文：http://blog.csdn.net/lizuobin2/article/details/52825033
		大致流程：
			1. 格式化eMMC
				fdisk -c 1 320 2057 520		
			2. 格式化分区
				fatformat mmc 1:1
				fatformat mmc 1:2
				fatformat mmc 1:3
				fatformat mmc 1:4
			3. bl1.bin, bl2.bin, u-boot.bin, tzsw.bin烧录到eMMC中
			4. 将拨动开关拨到eMMC启动，进入U-Boot	
			4. 设置环境变量
				> setenv bootargs console=ttySAC0,115200n8 androidboot.console=ttySAC0 uhost0=n ctp=2 skipcali=y vmalloc=512m lcd=S70
				> saveenv
			5. 输入fastboot，进入fastboot环境
			6. 在电脑端Linux，输入：
				> fastboot flash kernel zImage (来自Linux make后的镜像)
				> fastboot flash system system.img来自光盘android4.1.2文件夹. 
				> fastboot flash ramdisk ramdisk-u.img来自光盘android4.1.2文件夹. 
			7. 输入reset重启开发板，成功烧录android
	

+ 根文件系统
	+ busybox
		1. 从以下网址下载“https://busybox.net/”，版本：1.25.1
		2. 解压后，输入make menuconfig，
			+ 弹出错误：“ecipe for target 'scripts/kconfig/lxdialog/checklist.o' failed”
				解决：fedora：输入yum install ncurses-devel
					  ubuntu:输入apt-get install libncurses5-dev
			再次运行，打开菜单项：
			+ 输入：make menuconfig，选择busybox settings->build options，
				选择静态库; 进入cross compiler prefix，输入arm-linux-
			+ 进入 Installation Options->busybox installation prefix，输入路径：/home/sy/Docments/rootfs/ 
			+ 一些错误，参考：“arm-linux-gcc4.4.3编译busybox-1.25.pdf”
			+ 还有一个错误，“recipe for target 'docs/busybox.net/BusyBox.html' failed”，根据错误提示文件名及页码
				进入./Makefile.custom，屏蔽掉166~169行。
			+ 再次编译，成功。
			+ 输入make install，前提是路径在make menuconfig已设置。

+ NFS网络文件系统
	+ 主机Linxu
		+ 构建网络文件系统 
			1. 将光盘文件”rootfs_qtopia_qt4.zip“解压缩到 /home/sy/Documents/目录下
			2. 安装网络系统程序，yum install nfs-utils
			3. 打开vim /etc/exports，输入 /home/sy/Documents/rootfs_qtopia_qt4 *(rw,sync,no_root_squash)
			4. 关闭防火墙：systemctl stop firewalld.service
			5. 启动网络文件系统 systemctl start nfs-server.service 
			6. 查看网络文件系统状态 systemctl status nfs-server.service
			7. 查看本机IP地址：ifconfig 为192.168.2.150
		
		+ 测试网络文件系统
			1. 新建挂载文件系统的文件夹mkdir rootfs， chmod 777 /rootfs
			2. 挂载网络文件系统:mount 192.168.2.150:/home/sy/Documents/rootfs_qtopia_qt4/ /home/sy/Documents/rootfs/
			3. 在目录/home/sy/Documents/rootfs 即可看到/home/sy/Documents/rootfs_qtopia_qt4/目录所有的文件了，
				说明网络文件系统构建成功
			4. 查看当前挂载的网络文件系统，nfsstat -m
			5. 卸载网络文件系统：umount -f /home/sy/Documents/rootfs，如果不卸载，在开发板上将一直处理等待状态。
	
	+ MiniTools软件
		+ 步骤
			1. 在SD卡的FriendlyARM.ini文件中，添加USB-Mode=Yes
			2. 将开发板拨盘调到SD卡启动，此时软件显示开发板已连接。进入Linux页，在Kernel CommandLine前面打钩，
				填写：console=ttySAC0 root=/dev/nfs nfsroot=192.168.2.150:/home/sy/Documents/rootfs_qtopia_qt4 
						ip=192.168.2.7
				console：表示内核启动后使用串口输出信息，否则使用液晶屏。
				root：表示采用NFS的方式挂载文件系统，否则使用开发板自带的文件系统
				nfsroot：表示开发板需要挂载的文件系统的主机IP以及目录。必须和/etc/exports文件中的路径一致
				ip：表示将开发板分配一个IP地址。
			3. 烧录到开发板。
	
		+ 步骤：
			1. 如果不是使用superboot，而是uboot设置环境变量，那么需要在uboot界面输入
				setenv bootargs console=ttySAC0 root=/dev/nfs nfsroot=192.168.2.150:/home/sy/Documents/rootfs_qtopia_qt4 ip=192.168.2.7
			2. saveenv保存环境变量
	
	+ 开发板Linux
		1. 将开发板的开关打到flash启动，重新开机，即可启动内核，进入NFS网络文件系统中
		

+ MiniTools
	+ MiniTools的安装
		1. 问题：操作系统为Windows10，安装“MiniToolsSetup-Windows-20150528”完毕后，连接开发板提示不能连接？
			+ 打开任务管理器，在“其他设备”栏显示“Android 1.0”图标,图标右下角有一个感叹号标志，说明驱动未安装成功。
			经过多次尝试后，最终通过“驱动精灵”自动安装成功！

+ dnw
	简介：dnw用来从Linux向开发板内存下载固件，通过USB进行传输，开发板需要烧录U-Boot，将开发板与电脑通过串口连接。
	+ 使用步骤
		+ 准备dnw软件，从 https://github.com/Qunero/dnw4linux，选择Download ZIP，下载"dnw4linux-master.zip"到本地。
		+ 使用secureCRT发送到服务器后，通过unzip解压缩，生成两个主要的文件夹：
			1. 其中"secbulk_driver"为USB驱动，由于每个人的Linux内核可能不一样，因此需要根据自己的内核重新编译动态链接库文件(.ko)，
				查看路径"/lib/modules/xxx"是否有内核，如果没有，通过输入"yum install kernel-devel"，构建内核树。
			2. 输入make即可自动编译，生成sebulk_driver.ko动态链接库文件。
			3. 将编译出来的.ko文件，加载进内核，输入"insmod sebulk_dricer.ko"，如果不报错，输入lsmod，查看文件是否已经在
				其中。
			4. 由于动态链接库文件，在下次开机时需要再次加载，为了减少麻烦，可以进入路径“/etc/rc.d/rc.local”，在后面添加
				insmod /home/sy/Documents/dnw/src/driver/secbulk.ko，将动态链接库开机自动加载进内核。
			5. 再回到"dnw_src"文件夹，输入make可以编译出来dnw可执行文件，为了方便在任意目录使用./dnw发送数据，可以通过make install命令
				将dnw文件传送到"usr/sbin"目录。
		+ 在开发板进入u-boot时，按下空格键，输入dnw + 程序运行内存地址(与程序连接地址一致)，此时usb驱动自动加载，开发板等待接收文件...
		+ 在Linux中，输入lsusb,可以看到三星的USB设备被发现，如果使用虚拟机，没找到USB设备，必须进入vmware连接USB设备。
		+ 进入烧录文件目录，输入dnw + 烧录文件，即可传输数据。
		+ 如果USB驱动出现错误，检查secbulk.c中的
			#define		DOWNLOAD_USB_ID_MAJOR		0x04e8
			#define		DOWNLOAD_USB_ID_MINOR		0x1234
			是否与你得USB的ID匹配，通过lsusb可以观察。

+ MiniCOM
	+ dmesg | grep tty

+ secureCRT
	+ 传输文件
		+ Windows远程登录Linux服务器
			1. 打开secure CRT软件，点击“快速连接”
			2. 填写参数：
				协议：SSH2 	主机名：192.168.1.129服务器IP. 
			 	端口：22	用户名：syLinux用户名. 
			 点击“连接”。
			3. 弹出密码输入窗，输入用户密码。
			4. 如果连接不上，首先检查用户名、密码。
			5. 再者到虚拟机中的终端，输入“netstat -tlp”，如果显示“tcp6 0 0 *:ssh *:* LISTEN -”表示服务器SSH服务已打开！
			6. 如果Server-SSH未打开，输入“/etc/init.d/ssh restart”开启服务。
		
		+ Secure CRT配置文件传输
			1. 依次点击“Options”-"Session Options"-“X/Y/Zmodem”，填写上传、下载相应的目录。
		
		+ Ubuntu中支持ZModem协议
			1. 输入“apt-get install lrzsz”
			2. 如果提示"command not found"，输入"apt-get update"
		
		+ 文件上传/下载
			1. 上传：指的是客户端传送文件给Linux服务器。
				在secure CRT中定位将要上传到服务器的位置，输入"rz"命令，在弹出的对话框中选择待发送的文件，点击发送。
			2. 下载：指的是客户端从服务器接收文件。
				在secure CRT中定位需要接收的文件的目录，输入"sz + 文件名"，即可收到服务器发送的文件。
		
	+ 显示中文乱码
		1. 依次：[Options]-[Session Options]-[Appearance]-[Character encoding]，选择 UTF-8
		2. 如果依然乱码：则编写代码的文本编辑器不是UTF-8进行编码，比如UltraEdit，依次进入[高级]-[设置]-[新文件创建]-[编码类型]-[将新文件创建成UTF-8]
		3. 可能Linux使用的默认编码不是UTF-8。
	
	+ 快捷键
		+ 快速切换标签页
			1. Ctrl + Tab
		
	+ 小技巧
		+ 在secureCRT中登录Fedora，怎么实现语法高亮？
			1. 打开secureCTR，依次进入"Options-Session Options"，找到Emulation选项卡，
				+ 选择Terminal为"Linux"
				+ 选择ANSI Color
				+ 选择Use color scheme
			2. 找到Appearance选项卡，选择<Current color scheme>为 “Traditional”。
			3. 找到ANSI Color选项卡，将<Use global ANSI color setting>去掉勾选，修改深蓝色为浅蓝色。
		

+ FTP
	简介：FTP可以方便的在主机和Linux服务器、Linux服务器和开发板之间传输文件。

	+ Linux服务器配置FTP服务
		+ 安装vsftpd软件
			1. 输入：apt-get install vsftpd
			2. 输入：gedit /etc/vsftpd.conf
			3. 找到：#local_enable=YES #write_enable=YES ,将#去掉、保存。
			4. 输入：/etc/init.d/vsftpd start 开启FTP服务，以后启动系统时，FTP服务自动启动。
	
		+ 安装FlashFXP
			1. 输入IP、端口、用户名、密码即可登录Linux服务器
			2. 依次进入“站点”-“站点管理器”-“选项”-“字符编码”，将编码改为“UTF-8”,解决乱码问题。
			3. 重启软件。
	
		+ FTP常用命令
			1. 打开服务：ftp + [目标主机IP]
			2. 打开连接：open + [目标主机IP]
			3. 上传文件：put + [本地路径] + [远程路径]
			4. 批量上传文件：mput + [*.*]
			5. 下载文件：get + [远程路径] + [本地路径]
			6. 批量下载文件：mget + [*.*]
			7. 断开连接：bye 或 exit
			
		+ FTP 常用服务
			+ 打开ftp
				1. service vsftpd start
				2. systemctl start vsftpd
			+ 关闭ftp
				1. service vsftpd stop
				2. systemctl stop vsftpd
			+ 重启ftp
				1. service sshd restart
				2. systemctl restart sshd.service
			+ 查看ftp状态
				1. service vsftpd status
				2. systemctl status vsftpd
		
		+ 匿名用户
			+ 只要在 `/etc/vsftpd/vsftpd.conf`文件中配置：`anonymous_enable = YES`，就可以使用用户名：`anonymous`登录lInux。
			+ 匿名用户登录默认主目录：/var/ftp/
						
			
	+ 常见问题：
		+ 问题：FTP不能上传文件，提示“425 Can't open passive connection: Permission denied. Passive mode refused.”？
		> 原因：FTP主动模式造成的。一般FTP默认为被动模式，这两种模式发起连接的方向截然相反，
		主动模式是从服务器端向客户端发起；被动模式是客户端向服务器端发起连接，由于本地(客户端)存在防火墙，
		一般主动模式很难成功。
		> 解决：在电脑端ftp窗口输入：
			ftp>passive
			passive mode off

		+ 问题：使用SecureCRT连接linux的ftp服务器，登录时间过长？
		> 原因：DNS反向解析造成的。
		> 解决：
			1. 打开文件：`vim /etc/ssh/sshd_config`添加内容：`useDNS no`重启ftp服务器：`systemctl restart sshd.service`
			2. 如果还不行，打开文件：`vim /etc/vsftpd/vsftpd.conf`，添加`reverse_lookup_enable=NO`，重启ftp服务器。
		
		+ 问题：不能使用root用户登录ftp？
	  	> 解决：
			1. 打开文件`vim /etc/vsftpd/ftpusers`在root前面加#
			2. 打开文件`vim /etc/vsftpd/user_list`在root前面加#
			3. 输入`systemctl restart vsftpd.service`重启ftp服务器

	+ Fedora
		+ 安装ftp：yum -y install vsftpd
		+ 修改配置文件：vim /etc/vsftpd/vsftpd.conf，
			1. 把write_enable = YES,前面的#去掉。
			2. 把ascii_upload_enable=YES,前面的#去掉
			3. 把ascii_download_enable=YES,前面的#去掉
			4. 在listen_ipv6前面加上#
			5. 把listen=YES前面的#去掉
		+ 重启vsftpd服务
			1. systemctl start vsftpd.service
			2. systemctl enable vsftpd.service
+ SSH			
	+ SSH服务
		+ 更新源列表
			1. 输入"sudo apt-get update"
		
		+ 安装ssh
			1. 输入"sudo apt-get install openssh-server"
		
		+ 查看ssh服务
			1. 输入"sudo ps -e | grep ssh"
				如果有"sshd"表示服务已经启动
		
		+ 开启ssh服务
			1. 输入"sudo service ssh start"
		
		+ 关闭ssh服务
			1. 输入“sudo service ssh stop"
		
		+ 查看ssh状态
			1. 输入"sudo service ssh status"
	
	+ Fedora
		+ 打开ssh
			1. service sshd start
		
		+ 停止ssh
			1. service sshd stop
		
		+ 重新打开
			1. service sshd restart
		
		+ 设置开机自启动
			1. systemctl enable sshd.service
	
			
+ 搭建交叉编译器	
	简介：我们编写的程序不能在开发板中直接编译，因此需要交叉编译器，在主机中编译，然后传输到开发板中执行。
	流程大致为：我们在Linux中编写程序，通过Makefile文件，编译连接为可执行文件。通过
		1. 串口
		2. FTP协议
		3. 挂载U盘
		等形式，将可执行文件传输到开发板。

	+ 步骤：
		+ 解压缩包
			+ 将"arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz"拷贝到linux任意目录，输入
			"tar xvzf arm-linux-gcc-4.5.1-v6-vfp-20101103.tgz –C /"。
		
			+ 添加环境变量
				1. 输入"sudo vim /etc/profile"
				2. 添加"export PATH=$PATH:/opt/FriendlyARM/toolschain/4.5.1/bin"
				3. 输入"source /etc/profile"
				4. 输入"echo $PATH"，如果显示上述路径则添加成功！
		
			+ 安装64位程序
				1. 输入“sudo apt-get install lsb-core”
			
			+ 查看gcc版本
				1. 输入"arm-linux-gcc -v"
	
+ Fedora
	+ 输入arm-linux-gcc -v，弹出错误：“bash: /opt/FriendlyARM/toolschain/4.5.1/bin/arm-linux-gcc: 
	/lib/ld-linux.so.2: bad ELF interpreter: No such file or directory”，原因是64位的系统安装了32的软件，
	需要安装相应的库，输入"yum install glibc.i686"

+ Linux常见问题
	+ 问题：在登录界面，输入用户名，密码正确，但是进不了系统？
	> 原因：/etc/profile 文件内容错误。例如：输入export PATH = PATH:/xxxxxx，就会进不了系统，正确输入：export PATH = $PATH:/xxx
	> 解决：因为进不了系统，可以通过SSH访问系统，但是输入命令都是无效的，
	可以输入：export PATH=/usr/local/sbin:/usr/local/bin:/sbin:/bin:/usr/sbin:/usr/bin:/root/bin
	临时设置环境变量，便可以正常进入系统了。
	
	+ ubuntu怎么安装中文输入法？
		1. 打开“语言支持”选项卡，选择键盘输入法系统：fcitx。如果没有此选项，打开终端，输入“im-config”，找到fcitx选项，点击OK。
		2. 登出账户后，在“文本输入”选项卡即可看到中文输入法。	
		
	+ fedora怎么设置开机自启动程序？
		1. 参考 http://www.linuxdiyf.com/linux/12669.html
		2. 命令行输入 `vim /usr/lib/systemd/system/rc-local.service` 添加语句：
		```C
		[Install]
		WantedBy=multi-user.target
		```
		3. 输入 `systemctl enable rc-local.service`
		4. 在 `/etc/rc.d/`目录下创建文件`rc.local`，内容如下：
		```C
		#!/bin/bash

		# 下面添加开机自启动脚本
		```

+ Tiny4412常见问题
	+ 动态链接库丢失
		+ 问题：在开发板上运行可执行程序，BASH提示："No such file or directory"？
		> 原因：缺少动态链接库(.so)。
		> 解决：
			1. 输入命令"readelf -a + [可执行文件]"，
				屏幕打印："[Requesting program interpreter: /lib/ld-linux.so.3]"。可见缺少“ld-linux.so.3”库文件。
			2. 参考博文"http://blog.csdn.net/harry_helei/article/details/5740456"
				从网站"http://www.scratchbox.org/download/files/sbox-releases/stable/tarball/"下载文件
				"scratchbox-toolchain-cs2009q1-eglibc2.8-armv7-1.0.15-9-i386.tar.gz"，解压后，从以下路径
				"scratchbox/compilers/cs2009q1-eglibc2.8-armv7/arm-none-linux-gnueabi/libc/lib/"取出文件
				"ld-2.8.so"，而“ld-linux.so.3”是"ld-2.8.so"的快捷方式。
			3. 将该文件传送到开发板路径"\lib"目录下，改变权限"chmod 777 ld-2.8.so"。
			4. 使用命令："ln -s ld-2.8.so ld-linux.so.3"创建快捷方式。
			5. 再次运行可执行文件，BASH提示："./main: error while loading shared libraries: libc.so.6: 
					cannot open shared object file: No such file or directory"，表示又缺少动态链接库。
			6. 从刚才下载文件的路径，提取库"libc.so.6"，将文件传输到开发板路径"\lib"目录下。
			7. 改变权限"chmod 777 libc.so.6"。
			8. 再次运行可执行文件，打印出："Hello Word!"，程序正常。
				
	+ Uboot不能成功进入
		+ 问题：将Uboot烧录到SD后，串口打印OK，并没有打印Uboot信息？
		> 原因：由于友善之臂更换了eMMC，因此需要使用新的Uboot。
		> 解决：使用名称："uboot_tiny4412_0929.tar.gz"的Uboot
	
	+ 无法识别SD读卡器	
		+ 问题：使用“fdisk -l”命令无法侦测SD读卡器？
		> 原因：
			1. fedora安装在虚拟机VMware中，插入U盘后，电脑端可以显示U盘，虚拟机右下角可以检测到U盘插入。
			2. 使用命令"fdisk -l"无法检测到U盘。
			3. 使用“lsusb”也未找到设备。
			4. 将虚拟机“设置-USB控制器”，设置为USB兼容性：USB3.0依然没用
			5. 通过点击“虚拟机-可移动设备-U盘名”，点击“连接”，虚拟机提示USB驱动错误。
			6. 格式化U盘，无效。
		> 解决：
			通过安装新版本的虚拟机“VMware-workstation-full-12.5.0-4352439.exe”，重新插入U盘，
			点击“虚拟机-可移动设备-U盘名”，点击“连接”，此时电脑端U盘消失，使用“fdisk -l”检测到U盘！
			再次插拔U盘后，电脑端不再显示U盘了。
		> 总结：
			U盘只能被一台主机使用，如果想在虚拟机使用，必须通过虚拟机设置连接U盘！
		
	+ 问题：使用SD-Flasher.exe小软件无法 ReLayout？
	> 解决：点击ReLayout按钮，提示失败，再次点击ReLayout按钮即可成功！
	
	+ 问题：输入su时，提示su: must be suid to work properly？
	> 原因：嵌入式文件系统一般用户执行su root切换根用户提示错误：
		su: must be suid to work properly
	> 解决：chmod 4755 ./bin/busybox。
	> 解释：chmod 4755与chmod 755 的区别在于开头多了一位，这个4表示其他用户执行文件时，具有与所有者相当的权限。
		

+ Tiny4412裸机编程
	+ 裸机烧录步骤：
		1. 三星的4412处理器，上电后执行固化在ROM中的BootLoad0，该BootLoad做出相应的初始化步骤后，选择从SD卡或者其他外设启动，
		2. 我们选择SD卡启动后，程序便把SD卡中第512字节SD卡：512字节为1块，前面的第一个块用于建立分区表. 开始的8K字节拷贝到
			内存iRAM [iRAM基地址 + 5K(堆栈等) = 0x02020000 + 0x1400 = 0x02021400]中执行，
			这8K字节便是BootLoader1，由三星提供，文件名为：E4412_N.bl1.bin。其中，该文件的前16个字节用于提供校验信息，
			处理器将8K字节由SD卡拷贝到内存后，校验成功后，执行BL1。
		3. BL1从SD卡(512 + 8K)的位置拷贝16K字节到iRAM [iRAM基地址 + 5K(堆栈等) + 8K(BL1) = 0x02020000 + 0x1400 + 0x2000 = 0x02023400]，
			然后执行，我们的裸机程序便是连接到当前地址。
		4. BootLoader2的前14K-4个字节用于存储数据，后面4个字节用于存储校验和。	
		5. 上述提到的地址可以参考：
			Exynos 4412 SCP_Users Manual_Ver.0.10.00_Preliminary0.pdf，Memory Map部分。
			Android_Exynos4412_iROM_Secure_Booting_Guide_Ver.1.00.00.pdf，24页。、
			uboot_tiny4412_0929.tar.gz，裸机的脚本文件便是基于此进行改造。
		6. 进入"uboot_tiny4412_0929-sd_fuse"文件夹，输入vim V310-EVT1-mkbl2.c，该文件是生成mkbl2的源文件，我们的裸机程序便是使用mkbl2烧录到SD卡bl2位置。
			由于我们的裸机程序一般小于14k字节，而源程序要求必须大于14K字节，需要修改源程序。然后make编译出mkbl2文件。
		7. 进入tiny4412文件夹，修改烧录脚本sd_fusing.sh，将bl2的源程序设置为我们编写的裸机源程序。
		8. 插入SD卡，输入fdisk-l，查看sd卡已被检测，输入./sd_fusing.sh /dev/sdb即可自动烧录。
		9. 将SD卡插入到开发板，即可看到程序在运行。
	
	+ 总结：
		1. 重定位：程序的连接地址和烧录地址可以不一致，进入BootLoader1后，处理器从SD卡将BootLoader2的数据拷贝到指定地址，并跳转到该地址运行，
			如果程序的连接地址与该地址不一致，就需要重定位过程，将当前物理地址的程序搬运到连接地址处，然后跳转到连接地址运行。
		2. 在Makefile里，源文件的放置位置决定了连接时在文本段的位置。我们的程序一般从_start开始运行，因此需要将startup.S放在首位置。		
	
+ Tomcat
	+ 安装
		+ 进入网站 http://tomcat.apache.org/ 下载文件Tomcat8，找到 Binary Distributions 菜单下的Core：选择 tar.gz (pgp, md5, sha1)下载。
		+ 通过ssh传输到Linux /usr/local/目录，解压到当前目录
		+ 修改文件名：mv apache-tomcat-8.0.39 tomcat8
		+ 进入/bin目录，执行 ./startup.sh
		+ 输入 ps -ef | grep tomcat，查看是否进程已经启动。
		+ 在Windows浏览器中运行，`http://<Linux IP>:8080`，如果可以访问表示启动Tomcat成功！
		
	+ 开机自启动
		+ 打开`vim /etc/rc.d/rc.local`，添加：
		```C
		export JRE_HOME=/usr/lib/jvm/jdk1.7.0.79
		/usr/local/tomcat8/bin/startup.sh
		```
		注意：在`etc/profile`文件中已经设置JRE_HOME变量，在这里仍然需要再设置一次，因为 profile文件在用户登录后才起作用，
		而开机自启动程序在用户登录之前就已经启动了。
		
+ Mysql
	+ 安装
		+ 进入网站 https://www.mysql.com/ ，选择 Downloads->Community-> MySQL Community Server->Fedora
		选择Fedora 24 (x86, 64-bit), RPM Bundle，下载到本地。
		+ 传输到linux，解压缩 ` tar xf mysql-5.7.17-1.fc24.x86_64.rpm-bundle.tar`
		+ 输入 `rpm -ivh *`将所有文件一起安装
		+ 如果遇到依赖库问题，通过 `yum install + <库名>` 安装
		+ 安装完成
		+ 输入 `systemctl status mysqld.service` 查看Mysql状态
		+ 输入 `systemctl start mysqld.service` 启动 Mysql服务
		
	+ 问题
		+ 问题：`ERROR 1045 (28000): Access denied for user 'root'@'localhost' (using password: NO)`
		> 解决：
			1. 输入 `vim /etc/my.cnf`，在文件后面添加 `skip-grant-tables`，可以免密码登录。
			2. 输入 `systemctl restart mysqld.service`重启Mysql服务
			3. 输入 `mysql`，进入mysql
			4. 输入 `USE mysql`
			5. 输入 `update mysql.user set authentication_string=password('新密码') where user='root'; `
			6. flush privileges;
			7. quit
			8. 去掉 `skip-grant-tables` 
			9. 输入 `mysql -u root -p`，登录mysql。 其中[-u]代表user，[-p]代表password 
		
		+ 问题：`输入：mysql> show databases；`,弹出`ERROR 1820 (HY000): You must reset your password using ALTER USER statement before executing this statement.`
		> 解决：
			1. 输入 `set password=password('密码<需要8位以上，包含大小写字母、数字、符号>');`
		
+ QT
	+ 安装
		1. 从QT官网下载QT5，https://www.qt.io/download-open-source/#section-2
		2. 按照官方的帮助文档，安装QT。参考： http://doc.qt.io/qt-5/linux.html
		3. Ubuntu：`sudo apt-get install build-essential libgl1-mesa-dev`
		4. Fedora：
		```C
		sudo yum groupinstall "C Development Tools and Libraries"
		sudo yum install mesa-libGL-devel
		```


	
+ 知识点
	+ `dd iflag=dsync oflag=dsync if=./E4412_D.bl1.bin of=$1 seek=$signed_bl1_position`：
		1. 表示从if指定的位置，读取内容到缓冲区。然后写入到of指定的设备的seek偏移量的位置。


