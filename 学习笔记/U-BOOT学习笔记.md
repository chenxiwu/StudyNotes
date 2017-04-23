# U-BOOT学习笔记

#
*作者：SY*
*2017-1-16 20:18:16*
##

+ 源码
	+ 在Linux中输入 `git clone git://git.denx.de/u-boot.git`
		或者 `git clone http://git.denx.de/u-boot.git` 获取源码
		如果在Windows中获取源码，传输到Linux中可能会存在'\r\n'格式不兼容的问题
	+ 从FTP站点下载： ftp://ftp.denx.de/pub/u-boot/	

+ 烧录U-BOOT
	1. 烧录Uboot到SD卡
		+ 步骤
			1. 将文件"uboot_tiny4412_0929.tar.gz"，发送到虚拟机中的Linux中。
			2. 解压缩文件：tar zxf uboot_tiny4412_0929.tar.gz
			3. [裸机执行]由于需要用到硬件真实的地址，需要关闭MMU。打开文件：
			vim ./include/configs/tiny4412.h，将
			#define CONFIG_ENABLE_MMU 修改为 #undef CONFIG_ENABLE_MMU
			4. [裸机执行]修改Uboot的连接地址。打开文件vim 
			./board/samsung/tiny4412/config.mk，将
			CONFIG_SYS_TEXT_BASE = 0xC3E00000修改为0x43E00000
			5. 回到主目录：make tiny4412_config
			6. make  ，生成文件u-boot.bin
			7. 进入目录：cd sd_fuse，输入make，生成mkbl2文件
			8. 进入目录：cd tiny4412，将SD卡插入电脑，输入fdisk -l，出现设备标识，sdb1
			9. 输入 ./sd_fusing.sh /dev/sdb
		
	2. 烧录Uboot到eMMC
		+ 擦除eMMC
			1. 首先U-Boot需要能够从SD卡启动，进入命令行。
			2. 输入 mmcinfo0，则打印SD卡信息。
			3. 输入 mmcinfo1，则打印eMMC信息。
			3. 输入 fdisk -p 0，显示SD卡只有一个分区。
			4. 输入 fdisk -p 1，显示eMMC有4个分区。
				显示partion 1:407 2:608 3:2057 4:520
				分别表示：分区1 是FAE分区， 分区2 是给system的，分区3是user-data, 分区4 是 cache。
			5. 输入 fdisk -c 1 608 2057 520，下面开始正式格式化。
			6. 输入 fatformat mmc 1:1，格式化第一个分区为fat32格式
			7. 输入 ext3format mmc 1:2，格式化第二个分区为ext3格式
			8. 输入 ext3format mmc 1:3，格式化第三个分区为ext3格式
			9. 输入 ext3format mmc 1:4，格式化第四个分区为ext3格式
			
		+ 烧录U-Boot到eMMC
			1. 输入 emmc open 1，打开eMMC设备第一个分区。
			2. dnw 70003000，注意该地址范围：40000000 ~ 7FFFFFFF，共1G地址空间，该地址为物理内存地址，在MMU关闭的情况下。
			3. 在Linux主机中输入 dnw E4412_N.bl1.bin，传送该文件到内存地址70003000.
			4. U-Boot收到数据后，输入 mmc write 1 0x70003000 0 0x10，表示：从内存地址0x70003000开始读取16块1块=512字节. ，
				写入到设备1已知是eMMC. 中，起始地址为0，写入大小0x10(16)块。
			5. 在Linux主机中输入 dnw bl2.bin，传送该文件到内存地址70003000.
			6. U-Boot收到数据后，输入 mmc write 1 0x70003000 0x10 0x1C，表示：从内存地址0x70003000开始读取28块1块=512字节. ，
				写入到设备1已知是eMMC. 中，起始地址为0x10，写入大小0x1C(14K = 28块 = 0x1C)块。
			7. 在Linux主机中输入 dnw u-boot.bin，传送该文件到内存地址70003000.
			8. U-Boot收到数据后，输入 mmc write 1 0x70003000 0x30 0x21D，表示：从内存地址0x70003000开始读取506块实际大小约252K，按照253K拷贝数据. ，
				写入到设备1已知是eMMC. 中，起始地址为0x30由于第二块需要占用空间16K，8+16=24K. ，写入大小0x21D(541)块。
			9. 在Linux主机中输入 dnw E4412_tzsw.bin，传送该文件到内存地址70003000.
			10. U-Boot收到数据后，输入 mmc write 1 0x70003000 0x2C0 0xB8，表示：从内存地址0x70003000开始读取184块实际大小92K. ，
				写入到设备1已知是eMMC. 中，起始地址为0x2C0由于第三块需要占用空间253K，8+16+253=277K. ，写入大小0xB8(184)块。
			11. 至此，数据写入完毕。输入emmc close 1，关闭设备。
	
+ 尝试移植U-BOOT
	> 在三星提供的源码基础上移植U-BOOT到友善之臂的Tiny4412开发板。文件名：`u-boot-samsung-dev.rar`
	+ 移植步骤[带有mkconfig文件]：
		1. 将文件`u-boot-samsung-dev.rar`拷贝到linux中
		
		2. 输入 `unrar x u-boot-samsung-dev.rar`解压源码。
		
		3. 进入主目录中，找到 `boards.cfg` 文件，添加以下内容：
		` tiny4412                     arm         armv7       tiny4412            samsung        exynos`
		这个文件就是开发板的配置文件，格式为： `Target  Architecture  CPU  Board [VENDOR] [SOC]`
		
		4. 进入到 `board/samsung` 目录，拷贝文件 `[root@SY samsung]# cp -r smdk4212/ tiny4412`
		
		5. 进入到 tiny4412/ 目录，将所有的smdk4212改为tiny4412
		
		6. 输入 `make tiny4412_config`，提示：
		```C
		[root@SY u-boot_tiny4412_170205]# make tiny4412_config
		make: execvp: /home/sy/Documents/u-boot_tiny4412_170205/mkconfig: Permission denied
		Makefile:551: recipe for target 'tiny4412_config' failed
		make: *** [tiny4412_config] Error 127
		```
		说明mkconfig文件没有可执行权限。
		输入`[root@SY u-boot_tiny4412_170205]# chmod 755 mkconfig`
		输入 `make tiny4412_config`提示：
		```C
		[root@SY u-boot_tiny4412_170205]# make tiny4412_config
		Configuring for tiny4412 board...
		```
		配置完毕。
		
		7. 输入 `make` 提示：
		```C
		/home/sy/Documents/u-boot_tiny4412_170205/include/config.h:4:30: 
		fatal error: configs/tiny4412.h: No such file or directory compilation terminated.
		```
		进入目录 `include/configs/`，输入：`[root@SY configs]# cp smdk4412.h tiny4412.h`
		将系统频率改为：
		```C
		/* APLL : 1.4GHz */
 		#define CONFIG_CLK_ARM_1200_APLL_1400
		```
		8. 输入 `make` 提示：
		```C
		make: execvp: /home/sy/Documents/u-boot_tiny4412_170205/tools/setlocalversion
		: Permission denied
		```
		输入 `[root@SY u-boot_tiny4412_170205]# chmod 755 tools/setlocalversion `增加可执行权限。
		
		9. 输入 `make` 提示：
		```C
		[root@SY u-boot_tiny4412_170205]# make
		Generating include/generated/generic-asm-offsets.h
		tools/scripts/make-asm-offsets lib/asm-offsets.s
		include/generated/generic-asm-offsets.h
		make: execvp: tools/scripts/make-asm-offsets: Permission denied
		Makefile:506: recipe for target 'include/generated/generic-asm-offsets.h' failed
		make: *** [include/generated/generic-asm-offsets.h] Error 127
		```
		输入 `[root@SY u-boot_tiny4412_170205]# chmod 755 tools/scripts/make-asm-offsets`
		10. 输入 `make` 提示：

		因为没有指定交叉编译器。打开主目录的Makefile文件，添加：
		```C  
		 158 # set default to nothing for native builds
		 159 ifeq ($(HOSTARCH),$(ARCH))
		 160 CROSS_COMPILE ?=
		 161 endif
		 162 
		 163 CROSS_COMPILE ?= arm-linux-
		```
		继续编译...
		
		1. 根目录的mkconfig就是某一块开发板的配置文件。
			使用 ./mkconfig + 参数 可以生成开发板对应的配置文件。
		2. 参数格式参考mkconfig提示：
			`Parameters:  Target  Architecture  CPU  Board [VENDOR] [SOC]`
			其中在board.cfg文件中已经列举出来可以直接使用。
		如：` ./mkconfig smdk4212 arm armv7 smdk4212 samsung exynos`
		

	+ 移植步骤[带有Kbuild文件，类似Linux内核可配置]：
		1. 在目录 `board/samsung/`目录中，使用goni开发板。
			对应的配置文件在 `configs/s5p_goni_defconfig`。
		2. 在U-BOOT根目录执行`make s5p_goni_defconfig`，将在根目录生成.config文件
		3. 执行`make`开始编译
		4. 出现错误：
		`lib/asm-offsets.c:1:0: error: bad value (armv5) for -march= switch`，
		因为没有指定交叉编译器。打开主目录的Makefile文件，添加：
			```C  
			243 # set default to nothing for native builds
			244 ifeq ($(HOSTARCH),$(ARCH))
			245 CROSS_COMPILE ?=
			246 endif
			247 
			248 CROSS_COMPILE ?= arm-linux-`
			```
			继续编译...
		5. 出现错误：
		```C
		./scripts/dtc-version.sh: line 17: dtc: command not found
		./scripts/dtc-version.sh: line 18: dtc: command not found
		*** Your dtc is too old, please upgrade to dtc 1.4 or newer
		Makefile:1371: recipe for target 'checkdtc' failed
		```
		解决：输入`apt-get install libssl-dev`或者进入网站 https://centos.pkgs.org/6/epel-i386/dtc-1.4.0-1.el6.i686.rpm.html
		下载安装包安装。继续编译...完成！

+ 移植U-BOOT（2017-4-21 21:18:35）
	+ 环境
		1. 在Windows10中使用虚拟机VMWare[VMware® Workstation 12 Pro,12.5.0 build-4352439]
		2. 在虚拟机中安装Ubuntu[Linux ubuntu 4.8.0-46-generic 
		#49~16.04.1-Ubuntu SMP Fri Mar 31 14:50:48 UTC 2017 i686 i686 i686 GNU/Linux]
		3. 编译器：友善之臂提供的编译器 arm-linux-gcc-4.5.1-v6-vfp-20120301.tgz
		4. 开发板：Tiny4412/Super4412SDK 1506
	+ 下载U-BOOT
		1. 到网站 ftp://ftp.denx.de/pub/u-boot/ ，下载最新版U-BOOT（u-boot-2017.03.tar.bz2）
	+ 解压缩文件
		```C
		root@ubuntu:/opt/share# tar jxf u-boot-2017.03.tar.bz2 -C ../
		root@ubuntu:/opt/share# cd ..
		root@ubuntu:/opt# cd u-boot-2017.03
		root@ubuntu:/opt/u-boot-2017.03# ls
		api    cmd        configs  drivers   fs       Kconfig   MAINTAINERS  post     snapshot.commit
		arch   common     disk     dts       include  lib       Makefile     README   test
		board  config.mk  doc      examples  Kbuild   Licenses  net          scripts  tools
		```
	+ 创建版本控制
		```C
		root@ubuntu:/opt/u-boot-2017.03# git config --global user.email "1530454315@qq.com"
		root@ubuntu:/opt/u-boot-2017.03# git config --global user.name "SY"
		root@ubuntu:/opt/u-boot-2017.03# git init
		Initialized empty Git repository in /opt/u-boot-2017.03/.git/
		root@ubuntu:/opt/u-boot-2017.03# git add -A
		root@ubuntu:/opt/u-boot-2017.03# git commit -m "2017-4-21 21:33:33[初始版本]"
		root@ubuntu:/opt/u-boot-2017.03# git status
		On branch master
		nothing to commit, working directory clean
		```
	+ 参考
		[1] Android_Exynos4412_iROM_Secure_Booting_Guide_Ver.1.00.00.pdf
		[2] Exynos 4412 SCP_Users Manual_Ver.0.10.00_Preliminary0.pdf 
		[3] Tiny4412-1412-Schematic.pdf
		[4] Tiny4412SDK-1506-Schematic.pdf
	+ 选择类似的控制板
		1. 对于exynos4412来说，系统上电后，从IROM中读取BL0的代码到IRAM中，
		BL0的大小为5KByte，由三星提供。
		2. IRAM地址范围：0x02020000~0x02060000，共256KByte
		3. 主要完成关闭看门狗、失能中断、失能MMU等工作
		4. BL0读取OM引脚，判断从哪个外设读取BL1代码
		5. 根据友善之臂设计的OM引脚配置，支持SD/eMMC启动。将拨码开关拨到SD卡启动方式
		6. BL0将SD卡中的BL1代码段，拷贝到IRAM地址0x02021400的位置，大小为8KByte，
		校验成功后，程序由BL0跳转到BL1中执行。
		7. BL1由三星提供，文件名为：E4412_N.bl1.bin
		8. BL1主要任务是初始化中断，和SVC栈。从SD卡拷贝和校验BL2代码段，如果无差错
		则跳转到BL2中执行。
		9. BL2为用户提供，大小为16KByte，起始地址为0x02023400
		10. BL2的主要任务是初始化外部的SDRAM，同时拷贝并校验U-BOOT代码到SDRAM，
		然后跳转执行。
		11. 对应于U-BOOT中生成的SPL文件，因此需要选择一个开发板支持生成SPL文件
		12. root@ubuntu:/opt/u-boot-2017.03/board/samsung/origen# 目录下有一个
		tools工具，该mkorigenspl.c编译后会生成最终的BL2文件。
	+ SPL
		1. Note: "SPL" stands for "Secondary Program Loader"，可以理解为：SPL
		用于引导U-BOOT执行。由于现在的U-BOOT占用空间越来越大，对于一些小容量内存的
		芯片，已经不能运行整个U-BOOT，因此，需要在SPL中初始化必要的外设和SDRAM，
		然后拷贝U-BOOT到SDRAM中运行。 
	+ 移植步骤
		1. 拷贝文件
		```C
		root@ubuntu:/opt/u-boot-2017.03# cd board/samsung/
		root@ubuntu:/opt/u-boot-2017.03/board/samsung# ls
		arndale  espresso7420  odroid  smdk5250  smdkc100  trats   universal_c210
		common   goni          origen  smdk5420  smdkv310  trats2
		root@ubuntu:/opt/u-boot-2017.03/board/samsung# cp -R origen/ tiny4412
		root@ubuntu:/opt/u-boot-2017.03/board/samsung# cd tiny4412/
		root@ubuntu:/opt/u-boot-2017.03/board/samsung/tiny4412# ls
		Kconfig  MAINTAINERS  Makefile  origen.c  tools
		```
		2. 修改 ./board/samsung/tiny4412/Kconfig
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff d41eed board/samsung/tiny4412/Kconfig 
		diff --git a/board/samsung/tiny4412/Kconfig b/board/samsung/tiny4412/Kconfig
		index 63e3efe..06a7905 100644
		--- a/board/samsung/tiny4412/Kconfig
		+++ b/board/samsung/tiny4412/Kconfig
		@@ -1,12 +1,12 @@
		-if TARGET_ORIGEN
		+if TARGET_TINY4412
		 
		 config SYS_BOARD
		-       default "origen"
		+       default "tiny4412"
		 
		 config SYS_VENDOR
		        default "samsung"
		 
		 config SYS_CONFIG_NAME
		-       default "origen"
		+       default "tiny4412"
		 
		 endif
		```
		3. 修改 ./board/samsung/tiny4412/MAINTAINERS
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/board/samsung/origen/ board/samsung/tiny4412/MAINTAINERS 
		diff --git a/../temp/u-boot-2017.03/board/samsung/origen/MAINTAINERS b/board/samsung/tiny4412/MAINTAINERS
		index 8bf373e..5de019c 100644
		--- a/../temp/u-boot-2017.03/board/samsung/origen/MAINTAINERS
		+++ b/board/samsung/tiny4412/MAINTAINERS
		@@ -1,6 +1,6 @@
		-ORIGEN BOARD
		-M:     Chander Kashyap <k.chander@samsung.com>
		+TINY4412 BOARD
		+M:     Chander SY <1530454315@qq.com>
		 S:     Maintained
		-F:     board/samsung/origen/
		-F:     include/configs/origen.h
		-F:     configs/origen_defconfig
		+F:     board/samsung/tiny4412/
		+F:     include/configs/tiny4412.h
		+F:     configs/tiny4412_defconfig
		```
		4. 修改 ./board/samsung/tiny4412/Makefile
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff d41eed board/samsung/tiny4412/Makefile 
		diff --git a/board/samsung/tiny4412/Makefile b/board/samsung/tiny4412/Makefile
		index 1add9fe..0beabeb 100644
		--- a/board/samsung/tiny4412/Makefile
		+++ b/board/samsung/tiny4412/Makefile
		@@ -8,7 +8,7 @@ ifdef CONFIG_SPL_BUILD
		 # necessary to create built-in.o
		 obj- := __dummy__.o
		 
		-hostprogs-y := tools/mkorigenspl
		+hostprogs-y := tools/mktiny4412spl
		 always := $(hostprogs-y)
		 
		 # omit -O2 option to suppress
		@@ -16,7 +16,7 @@ always := $(hostprogs-y)
		 #
		 # TODO:
		 # Fix the root cause in tools/mkorigenspl.c and delete the following work-around
		-$(obj)/tools/mkorigenspl: HOSTCFLAGS:=$(filter-out -O2,$(HOSTCFLAGS))
		+$(obj)/tools/mktiny4412spl: HOSTCFLAGS:=$(filter-out -O2,$(HOSTCFLAGS))
		 else
		-obj-y  += origen.o
		+obj-y  += tiny4412.o
		 endif
		```
		5. 修改 ./board/samsung/tiny4412/tiny4412.c
		```C
		git diff ../temp/u-boot-2017.03/board/samsung/origen/origen.c board/samsung/tiny4412/tiny4412.c
		只修改文件名
		```
		6. 修改 ./board/samsung/tiny4412/mktiny4412spl.c
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/board/
		samsung/origen/tools/mkorigenspl.c 
		board/samsung/tiny4412/tools/mktiny4412spl.c 
		diff --git a/../temp/u-boot-2017.03/board/samsung/origen/tools/
		mkorigenspl.c b/board/samsung/tiny4412/tools/mktiny4412spl.c
		index 7b5d93b..ea61635 100644
		--- a/../temp/u-boot-2017.03/board/samsung/origen/tools/mkorigenspl.c
		+++ b/board/samsung/tiny4412/tools/mktiny4412spl.c
		@@ -12,12 +12,10 @@
		 #include <string.h>
		 #include <sys/stat.h>
		 
		+#define CHECKSUM_OFFSET                (14*1024-4)
		 #define BUFSIZE                        (16*1024)
		-#define IMG_SIZE               (16*1024)
		-#define SPL_HEADER_SIZE                16
		 #define FILE_PERM              (S_IRUSR | S_IWUSR | S_IRGRP \
		                                | S_IWGRP | S_IROTH | S_IWOTH)
		-#define SPL_HEADER             "S5PC210 HEADER  "
		 /*
		 * Requirement:
		 * IROM code reads first 14K bytes from boot device.
		@@ -26,10 +24,10 @@
		 *
		 * This function takes two filenames:
		 * IN  "u-boot-spl.bin" and
		-* OUT "$(BOARD)-spl.bin as filenames.
		+* OUT "u-boot-mmc-spl.bin" as filenames.
		 * It reads the "u-boot-spl.bin" in 16K buffer.
		 * It calculates checksum of 14K-4 Bytes and stores at 14K-4 offset in buffer.
		-* It writes the buffer to "$(BOARD)-spl.bin" file.
		+* It writes the buffer to "u-boot-mmc-spl.bin" file.
		 */
		 
		 int main(int argc, char **argv)
		@@ -63,12 +61,9 @@ int main(int argc, char **argv)
		        len = lseek(ifd, 0, SEEK_END);
		        lseek(ifd, 0, SEEK_SET);
		 
		-       memcpy(&buffer[0], SPL_HEADER, SPL_HEADER_SIZE);
		+       count = (len < CHECKSUM_OFFSET) ? len : CHECKSUM_OFFSET;
		 
		-       count = (len < (IMG_SIZE - SPL_HEADER_SIZE))
		-               ? len : (IMG_SIZE - SPL_HEADER_SIZE);
		-
		-       if (read(ifd, buffer + SPL_HEADER_SIZE, count) != count) {
		+       if (read(ifd, buffer, count) != count) {
		                fprintf(stderr, "%s: Can't read %s: %s\n",
		                        argv[0], argv[1], strerror(errno));
		 
		@@ -80,14 +75,10 @@ int main(int argc, char **argv)
		                exit(EXIT_FAILURE);
		        }
		 
		-       for (i = 0; i < IMG_SIZE - SPL_HEADER_SIZE; i++)
		-               checksum += buffer[i+16];
		-
		-       *(unsigned long *)buffer ^= 0x1f;
		-       *(unsigned long *)(buffer+4) ^= checksum;
		+       for (i = 0, checksum = 0; i < CHECKSUM_OFFSET; i++)
		+               checksum += buffer[i];
		 
		-       for (i = 1; i < SPL_HEADER_SIZE; i++)
		-               buffer[i] ^= buffer[i-1];
		+       memcpy(&buffer[CHECKSUM_OFFSET], &checksum, sizeof(checksum));
		 
		        if (write(ofd, buffer, BUFSIZE) != BUFSIZE) {
		                fprintf(stderr, "%s: Can't write %s: %s\n",
		(END)	
		```
		7. 修改 ./include/configs/tiny4412.h
		```C
		root@ubuntu:/opt/u-boot-2017.03# cp include/configs/origen.h include/configs/tiny4412.h
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03
		/include/configs/origen.h include/configs/tiny4412.h  
		diff --git a/../temp/u-boot-2017.03/include/configs/origen.h 
		b/include/configs/tiny4412.h
		index 26fe402..c8990a3 100644
		--- a/../temp/u-boot-2017.03/include/configs/origen.h
		+++ b/include/configs/tiny4412.h
		@@ -6,14 +6,24 @@
		  * SPDX-License-Identifier:    GPL-2.0+
		  */
		 
		-#ifndef __CONFIG_ORIGEN_H
		-#define __CONFIG_ORIGEN_H
		+#ifndef __CONFIG_TINY4412_H
		+#define __CONFIG_TINY4412_H
		 
		 #include <configs/exynos4-common.h>
		 
		 /* High Level Configuration Options */
		-#define CONFIG_EXYNOS4210              1       /* which is a EXYNOS4210 SoC */
		-#define CONFIG_ORIGEN                  1       /* working with ORIGEN*/
		+#define CONFIG_EXYNOS4412                  1    /* which is a EXYNOS4412 SoC */
		+#define CONFIG_TINY4412                        1        /* working with ORIGEN*/
		+
		+/* DEBUG UART */
		+
		+#define CONFIG_DEBUG_UART                      1       
		+#define CONFIG_SPL_SERIAL_SUPPORT      1
		+#define CONFIG_SPL_GPIO_SUPPORT                1
		+#define CONFIG_DEBUG_UART_S5P          1
		+#define CONFIG_DEBUG_UART_BASE         0x13800000
		+#define CONFIG_DEBUG_UART_CLOCK                (100000000)
		+
		 
		 #define CONFIG_SYS_DCACHE_OFF          1
		 
		@@ -28,16 +38,16 @@
		 #define CONFIG_SYS_MEMTEST_END         (CONFIG_SYS_SDRAM_BASE + 0x6000000)
		 #define CONFIG_SYS_LOAD_ADDR           (CONFIG_SYS_SDRAM_BASE + 0x3E00000)
		 
		-#define CONFIG_SYS_TEXT_BASE           0x43E00000
		+#define CONFIG_SYS_TEXT_BASE           0x43E00000 
		 
		-#define CONFIG_MACH_TYPE               MACH_TYPE_ORIGEN
		+#define CONFIG_MACH_TYPE               MACH_TYPE_TINY4412
		 
		 /* select serial console configuration */
		-#define CONFIG_SERIAL2
		+#define CONFIG_SERIAL0
		 #define CONFIG_BAUDRATE                        115200
		 
		 /* Console configuration */
		-#define CONFIG_DEFAULT_CONSOLE         "console=ttySAC1,115200n8\0"
		+#define CONFIG_DEFAULT_CONSOLE         "console=ttySAC0,115200n8\0"
		 
		 #define CONFIG_SYS_MEM_TOP_HIDE        (1 << 20)       /* ram console */
		 
		@@ -52,14 +62,14 @@
		 
		 /* MMC SPL */
		 #define COPY_BL2_FNPTR_ADDR    0x02020030
		-#define CONFIG_SPL_TEXT_BASE   0x02021410
		+#define CONFIG_SPL_TEXT_BASE   0x02023400
		 
		 #define CONFIG_EXTRA_ENV_SETTINGS \
		        "loadaddr=0x40007000\0" \
		        "rdaddr=0x48000000\0" \
		        "kerneladdr=0x40007000\0" \
		        "ramdiskaddr=0x48000000\0" \
		-       "console=ttySAC2,115200n8\0" \
		+       "console=ttySAC0,115200n8\0" \
		        "mmcdev=0\0" \
		        "bootenv=uEnv.txt\0" \
		        "loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
		@@ -94,17 +104,16 @@
		 #define CONFIG_SYS_MMC_ENV_DEV         0
		 #define CONFIG_ENV_SIZE                        (16 << 10)      /* 16 KB */
		 #define RESERVE_BLOCK_SIZE             (512)
		-#define BL1_SIZE                       (16 << 10) /*16 K reserved for BL1*/
		+#define BL1_SIZE                       (8 << 10) /* 8K reserved for BL1*/
		 #define CONFIG_ENV_OFFSET              (RESERVE_BLOCK_SIZE + BL1_SIZE)
		 
		 #define CONFIG_SPL_LDSCRIPT    "board/samsung/common/exynos-uboot-spl.lds"
		 #define CONFIG_SPL_MAX_FOOTPRINT       (14 * 1024)
		 
		-#define CONFIG_SYS_INIT_SP_ADDR                0x02040000
		+#define CONFIG_SYS_INIT_SP_ADDR                0x02040000 
		 
		 /* U-Boot copy size from boot Media to DRAM.*/
		 #define COPY_BL2_SIZE          0x80000
		 #define BL2_START_OFFSET       ((CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)/512)
		 #define BL2_SIZE_BLOC_COUNT    (COPY_BL2_SIZE/512)
		-
		 #endif /* __CONFIG_H */

		```
		8. 修改 ./configs/tiny4412_defconfig
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/configs/origen_defconfig configs/tiny4412_defconfig
		diff --git a/../temp/u-boot-2017.03/configs/origen_defconfig b/configs/tiny4412_defconfig
		index dfb08fb..0da8adf 100644
		--- a/../temp/u-boot-2017.03/configs/origen_defconfig
		+++ b/configs/tiny4412_defconfig
		@@ -1,14 +1,14 @@
		 CONFIG_ARM=y
		 CONFIG_ARCH_EXYNOS=y
		 CONFIG_ARCH_EXYNOS4=y
		-CONFIG_TARGET_ORIGEN=y
		-CONFIG_IDENT_STRING=" for ORIGEN"
		-CONFIG_DEFAULT_DEVICE_TREE="exynos4210-origen"
		+CONFIG_TARGET_TINY4412=y
		+CONFIG_IDENT_STRING=" for TINY4412"
		+CONFIG_DEFAULT_DEVICE_TREE="exynos4412-tiny4412"
		 CONFIG_SYS_CONSOLE_IS_IN_ENV=y
		 CONFIG_SYS_CONSOLE_INFO_QUIET=y
		 CONFIG_SPL=y
		 CONFIG_HUSH_PARSER=y
		-CONFIG_SYS_PROMPT="ORIGEN # "
		+CONFIG_SYS_PROMPT="TINY4412# "
		 CONFIG_CMD_BOOTZ=y
		 # CONFIG_CMD_IMLS is not set
		 # CONFIG_CMD_XIMG is not set
		@@ -44,3 +44,5 @@ CONFIG_USB_GADGET_DOWNLOAD=y
		 CONFIG_G_DNL_MANUFACTURER="Samsung"
		 CONFIG_G_DNL_VENDOR_NUM=0x04e8
		 CONFIG_G_DNL_PRODUCT_NUM=0x6601
		+
		+
		```
		9. 修改 ./arch/arm/mach-exynos/Kconfig
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/
		arch/arm/mach-exynos/Kconfig arch/arm/mach-exynos/Kconfig 
		diff --git a/../temp/u-boot-2017.03/arch/arm/mach-exynos/Kconfig 
		b/arch/arm/mach-exynos/Kconfig
		index 46981a5..fc29d0a 100644
		--- a/../temp/u-boot-2017.03/arch/arm/mach-exynos/Kconfig
		+++ b/arch/arm/mach-exynos/Kconfig
		@@ -59,6 +59,10 @@ config TARGET_TRATS2
		 config TARGET_ODROID
		        bool "Exynos4412 Odroid board"
		 
		+config TARGET_TINY4412
		+       bool "Exynos4412 Tiny4412 board"
		+       select SUPPORT_SPL
		+
		 endchoice
		 endif
		 
		@@ -155,5 +159,6 @@ source "board/samsung/arndale/Kconfig"
		 source "board/samsung/smdk5250/Kconfig"
		 source "board/samsung/smdk5420/Kconfig"
		 source "board/samsung/espresso7420/Kconfig"
		+source "board/samsung/tiny4412/Kconfig"
		 
		 endif
		```
		10. 修改 ./arch/arm/mach-exynos/Makefile
		```C
		root@ubuntu:/opt/u-boot-2017.03# cp ../u-boot-2017.03_bkp/arch/arm
		/mach-exynos/clock_init_exynos4412.c arch/arm/mach-exynos/
		root@ubuntu:/opt/u-boot-2017.03# cp ../u-boot-2017.03_bkp/arch/arm
		/mach-exynos/dmc_init_exynos4412.c arch/arm/mach-exynos/ 
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03
		/arch/arm/mach-exynos/Makefile arch/arm/mach-exynos/Makefile 
		diff --git a/../temp/u-boot-2017.03/arch/arm/mach-exynos/Makefile 
		b/arch/arm/mach-exynos/Makefile
		index 0cc6c32..f2cd76d 100644
		--- a/../temp/u-boot-2017.03/arch/arm/mach-exynos/Makefile
		+++ b/arch/arm/mach-exynos/Makefile
		@@ -15,6 +15,7 @@ ifdef CONFIG_SPL_BUILD
		 obj-$(CONFIG_EXYNOS5)  += clock_init_exynos5.o
		 obj-$(CONFIG_EXYNOS5)  += dmc_common.o dmc_init_ddr3.o
		 obj-$(CONFIG_EXYNOS4210)+= dmc_init_exynos4.o clock_init_exynos4.o
		+obj-$(CONFIG_EXYNOS4412)+= dmc_init_exynos4412.o clock_init_exynos4412.o
		 obj-y  += spl_boot.o tzpc.o
		 obj-y  += lowlevel_init.o
		 endif
		```
		11. 修改 ./arch/arm/mach-exynos/exynos4_setup.h
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/arch
		/arm/mach-exynos/exynos4_setup.h arch/arm/mach-exynos/exynos4_setup.h 
		diff --git a/../temp/u-boot-2017.03/arch/arm/mach-exynos/exynos4_setup.h 
		b/arch/arm/mach-exynos/exynos4_setup.h
		index 9f29d94..f4e2c8b 100644
		--- a/../temp/u-boot-2017.03/arch/arm/mach-exynos/exynos4_setup.h
		+++ b/arch/arm/mach-exynos/exynos4_setup.h
		@@ -6,8 +6,8 @@
		  * SPDX-License-Identifier:    GPL-2.0+
		  */
		 
		-#ifndef _ORIGEN_SETUP_H
		-#define _ORIGEN_SETUP_H
		+#ifndef _EXYNOS4_SETUP_H
		+#define _EXYNOS4_SETUP_H
		 
		 #include <config.h>
		 #include <asm/arch/cpu.h>
		@@ -434,7 +434,7 @@ struct mem_timings {
		 #define ABP_SFR_SLV1_SINGLE_ADDRMAP_START_OFFSET       0x828
		 #define ABP_SFR_SLV1_SINGLE_ADDRMAP_END_OFFSET 0x830
		 
		-#ifdef CONFIG_ORIGEN
		+#ifdef CONFIG_TINY4412
		 /* Interleave: 2Bit, Interleave_bit1: 0x15, Interleave_bit0: 0x7 */
		 #define APB_SFR_INTERLEAVE_CONF_VAL    0x20001507
		 #define APB_SFR_ARBRITATION_CONF_VAL   0x00000001
		@@ -556,7 +556,7 @@ struct mem_timings {
		 
		 #define CONTROL2_VAL           0x00000000
		 
		-#ifdef CONFIG_ORIGEN
		+#ifdef CONFIG_TINY4412
		 #define TIMINGREF_VAL          0x000000BB
		 #define TIMINGROW_VAL          0x4046654f
		 #define        TIMINGDATA_VAL          0x46400506
		```
		12. 修改 ./arch/arm/include/asm/mach-types.h
		```C
		已经添加，不用修改
		```
		13. 修改 ./arch/arm/dts/exynos4412-tiny4412.dts
		```C
		root@ubuntu:/opt/u-boot-2017.03# cp ./arch/arm/dts/exynos4412-odroid.dts
		arch/arm/dts/exynos4412-tiny4412.dts
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/arch
		/arm/dts/exynos4412-odroid.dts arch/arm/dts/exynos4412-tiny4412.dts 
		diff --git a/../temp/u-boot-2017.03/arch/arm/dts/exynos4412-odroid.dts b/arch/arm/dts/exynos4412-tiny4412.dts
		index 188cb93..9307c0b 100644
		--- a/../temp/u-boot-2017.03/arch/arm/dts/exynos4412-odroid.dts
		+++ b/arch/arm/dts/exynos4412-tiny4412.dts
		@@ -11,260 +11,20 @@
		 #include "exynos4412.dtsi"
		 
		 / {
		-       model = "Odroid based on Exynos4412";
		-       compatible = "samsung,odroid", "samsung,exynos4412";
		+       model = "Tiny4412 based on Exynos4412";
		+       compatible = "samsung,tiny4412", "samsung,exynos4412";
		 
		-       aliases {
		-               i2c0 = "/i2c@13860000";
		-               i2c1 = "/i2c@13870000";
		-               i2c2 = "/i2c@13880000";
		-               i2c3 = "/i2c@13890000";
		-               i2c4 = "/i2c@138a0000";
		-               i2c5 = "/i2c@138b0000";
		-               i2c6 = "/i2c@138c0000";
		-               i2c7 = "/i2c@138d0000";
		-               serial0 = "/serial@13800000";
		-               console = "/serial@13810000";
		-               mmc2 = "/sdhci@12530000";
		-               mmc4 = "/dwmmc@12550000";
		+       chosen {
		+               stdout-path = "serial0";
		        };
		 
		-       i2c@13860000 {
		-               samsung,i2c-sda-delay = <100>;
		-               samsung,i2c-slave-addr = <0x10>;
		-               samsung,i2c-max-bus-freq = <100000>;
		-               status = "okay";
		-
		-               max77686_pmic@09 {
		-                       compatible = "maxim,max77686";
		-                       interrupts = <7 0>;
		-                       reg = <0x09 0 0>;
		-                       #clock-cells = <1>;
		-
		-                       voltage-regulators {
		-                               ldo1_reg: LDO1 {
		-                                       regulator-name = "VDD_ALIVE_1.0V";
		-                                       regulator-min-microvolt = <1000000>;
		-                                       regulator-max-microvolt = <1000000>;
		-                               };
		-
		-                               ldo2_reg: LDO2 {
		-                                       regulator-name = "VDDQ_VM1M2_1.2V";
		-                                       regulator-min-microvolt = <1200000>;
		-                                       regulator-max-microvolt = <1200000>;
		-                               };
		-
		-                               ldo3_reg: LDO3 {
		-                                       regulator-name = "VCC_1.8V_AP";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo4_reg: LDO4 {
		-                                       regulator-name = "VDDQ_MMC2_2.8V";
		-                                       regulator-min-microvolt = <2800000>;
		-                                       regulator-max-microvolt = <2800000>;
		-                               };
		-
		-                               ldo5_reg: LDO5 {
		-                                       regulator-name = "VDDQ_MMC0/1/3_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo6_reg: LDO6 {
		-                                       regulator-name = "VMPLL_1.0V";
		-                                       regulator-min-microvolt = <1100000>;
		-                                       regulator-max-microvolt = <1100000>;
		-                               };
		-
		-                               ldo7_reg: LDO7 {
		-                                       regulator-name = "VPLL_1.1V";
		-                                       regulator-min-microvolt = <1100000>;
		-                                       regulator-max-microvolt = <1100000>;
		-                               };
		-
		-                               ldo8_reg: LDO8 {
		-                                       regulator-name = "VDD_MIPI/HDMI_1.0V";
		-                                       regulator-min-microvolt = <1000000>;
		-                                       regulator-max-microvolt = <1000000>;
		-                               };
		-
		-                               ldo10_reg: LDO10 {
		-                                       regulator-name = "VDD_MIPI/HDMI_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo11_reg: LDO11 {
		-                                       regulator-name = "VDD_ABB1_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo12_reg: LDO12 {
		-                                       regulator-name = "VDD_UOTG_3.0V";
		-                                       regulator-min-microvolt = <3000000>;
		-                                       regulator-max-microvolt = <3000000>;
		-                               };
		-
		-                               ldo13_reg: LDO13 {
		-                                       regulator-name = "VDD_C2C_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo14_reg: LDO14 {
		-                                       regulator-name = "VDD_ABB02_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo15_reg: LDO15 {
		-                                       regulator-name = "VDD_HSIC/OTG_1.0V";
		-                                       regulator-min-microvolt = <1000000>;
		-                                       regulator-max-microvolt = <1000000>;
		-                               };
		-
		-                               ldo16_reg: LDO16 {
		-                                       regulator-name = "VDD_HSIC_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                               };
		-
		-                               ldo17_reg: LDO17 {
		-                                       regulator-name = "VDDQ_CAM_1.2V";
		-                                       regulator-min-microvolt = <1200000>;
		-                                       regulator-max-microvolt = <1200000>;
		-                               };
		-
		-                               ldo20_reg: LDO20 {
		-                                       regulator-name = "VDDQ_EMMC_1.8V";
		-                                       regulator-min-microvolt = <1800000>;
		-                                       regulator-max-microvolt = <1800000>;
		-                                       regulator-always-on;
		-                                       regulator-boot-on;
		-                               };
		-
		-                               ldo21_reg: LDO21 {
		-                                       regulator-name = "TFLASH_2.8V";
		-                                       regulator-min-microvolt = <2800000>;
		-                                       regulator-max-microvolt = <2800000>;
		-                                       regulator-always-on;
		-                                       regulator-boot-on;
		-                               };
		-
		-                               ldo22_reg: LDO22 {
		-                                       regulator-name = "VDDQ_EMMC_2.8V";
		-                                       regulator-min-microvolt = <2800000>;
		-                                       regulator-max-microvolt = <2800000>;
		-                                       regulator-always-on;
		-                                       regulator-boot-on;
		-                               };
		-
		-                               ldo25_reg: LDO25 {
		-                                       regulator-compatible = "LDO25";
		-                                       regulator-name = "VDDQ_LCD_3.0V";
		-                                       regulator-min-microvolt = <3000000>;
		-                                       regulator-max-microvolt = <3000000>;
		-                               };
		-
		-                               buck1_reg: BUCK1 {
		-                                       regulator-name = "VDD_MIF_1.0V";
		-                                       regulator-min-microvolt = <8500000>;
		-                                       regulator-max-microvolt = <1100000>;
		-                               };
		-
		-                               buck2_reg: BUCK2 {
		-                                       regulator-name = "VDD_ARM_1.0V";
		-                                       regulator-min-microvolt = <850000>;
		-                                       regulator-max-microvolt = <1500000>;
		-                               };
		-
		-                               buck3_reg: BUCK3 {
		-                                       regulator-name = "VDD_INT_1.1V";
		-                                       regulator-min-microvolt = <850000>;
		-                                       regulator-max-microvolt = <1150000>;
		-                               };
		-
		-                               buck4_reg: BUCK4 {
		-                                       regulator-name = "VDD_G3D_1.0V";
		-                                       regulator-min-microvolt = <850000>;
		-                                       regulator-max-microvolt = <1150000>;
		-                               };
		-
		-                               buck5_reg: BUCK5 {
		-                                       regulator-name = "VDDQ_AP_1.2V";
		-                                       regulator-min-microvolt = <1200000>;
		-                                       regulator-max-microvolt = <1200000>;
		-                               };
		-
		-                               buck6_reg: BUCK6 {
		-                                       regulator-name = "VCC_INL1/7_1.35V";
		-                                       regulator-min-microvolt = <1350000>;
		-                                       regulator-max-microvolt = <1350000>;
		-                               };
		-
		-                               buck7_reg: BUCK7 {
		-                                       regulator-name = "VCC_INL2/3/5_2.0V";
		-                                       regulator-min-microvolt = <2000000>;
		-                                       regulator-max-microvolt = <2000000>;
		-                               };
		-
		-                               buck8_reg: BUCK8 {
		-                                       regulator-name = "VCC_P3V3_2.85V";
		-                                       regulator-min-microvolt = <2850000>;
		-                                       regulator-max-microvolt = <3300000>;
		-                               };
		-                       };
		-               };
		+       aliases {
		+               serial0 = "/serial@13800000";
		+               console = "/serial@13800000";
		        };
		 
		-       serial@13810000 {
		+       serial0:serial@13810000 {
		                status = "okay";
		        };
		 
		-       sdhci@12510000 {
		-               status = "disabled";
		-       };
		-
		-       sdhci@12520000 {
		-               status = "disabled";
		-       };
		-
		-       sdhci@12530000 {
		-               samsung,bus-width = <4>;
		-               samsung,timing = <1 2 3>;
		-               cd-gpios = <&gpk2 2 0>;
		-       };
		-
		-       sdhci@12540000 {
		-               status = "disabled";
		-       };
		-
		-       dwmmc@12550000 {
		-               samsung,bus-width = <8>;
		-               samsung,timing = <2 1 0>;
		-               samsung,removable = <0>;
		-               fifoth_val = <0x203f0040>;
		-               bus_hz = <400000000>;
		-               div = <0x3>;
		-               index = <4>;
		-       };
		-
		-       ehci@12580000 {
		-               compatible = "samsung,exynos-ehci";
		-               reg = <0x12580000 0x100>;
		-               #address-cells = <1>;
		-               #size-cells = <1>;
		-               phy {
		-                       compatible = "samsung,exynos-usb-phy";
		-                       reg = <0x125B0000 0x100>;
		-               };
		-       };
		-
		-       emmc-reset {
		-               compatible = "samsung,emmc-reset";
		-               reset-gpio = <&gpk1 2 0>;
		-       };
		 };
		(END)
		```
		14. 修改 ./arch/arm/dts/Makefile
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/arch
		/arm/dts/Makefile arch/arm/dts/Makefile               
		diff --git a/../temp/u-boot-2017.03/arch/arm/dts/Makefile 
		b/arch/arm/dts/Makefile
		index eb68c20..ebd0ca4 100644
		--- a/../temp/u-boot-2017.03/arch/arm/dts/Makefile
		+++ b/arch/arm/dts/Makefile
		@@ -14,7 +14,8 @@ dtb-$(CONFIG_EXYNOS4) += exynos4210-origen.dtb \
		        exynos4210-universal_c210.dtb \
		        exynos4210-trats.dtb \
		        exynos4412-trats2.dtb \
		-       exynos4412-odroid.dtb
		+       exynos4412-odroid.dtb \
		+       exynos4412-tiny4412.dtb
		 
		 dtb-$(CONFIG_TARGET_HIKEY) += hi6220-hikey.dtb
		```
		15. 增加 ./arch/arm/mach-exynos/clock_init_exynos4412.h 
		```C
		root@ubuntu:/opt/u-boot-2017.03# vim arch/arm/mach-exynos/exynos4412_setup.h 
		/*
		 * Copyright (C) 2014 Samsung Electronics
		 * Przemyslaw Marczak <p.marczak@samsung.com>
		 *
		 * SPDX-License-Identifier:    GPL-2.0
		 */
		
		#ifndef __CLOCK_INIT_EXYNOS4412_H
		#define __CLOCK_INIT_EXYNOS4412_H
		
		/* A/M/E/V PLL_CON0 */
		#define SDIV(x)                 ((x) & 0x7)
		#define PDIV(x)                 (((x) & 0x3f) << 8)
		#define MDIV(x)                 (((x) & 0x3ff) << 16)
		#define FSEL(x)                 (((x) & 0x1) << 27)
		#define PLL_LOCKED_BIT          (0x1 << 29)
		#define PLL_ENABLE(x)           (((x) & 0x1) << 31)
		
		/* A/M PLL_CON1 */
		#define AFC(x)                 ((x) & 0xf)
		#define LOCK_CON_DLY(x)        (((x) & 0xf) << 8)
		#define LOCK_CON_IN(x)        (((x) & 0x3) << 12)
		#define LOCK_CON_OUT(x)        (((x) & 0x3) << 14)
		#define FEED_EN(x)        (((x) & 0x1) << 16)
		#define AFC_ENB(x)        (((x) & 0x1) << 20)
		#define DCC_ENB(x)        (((x) & 0x1) << 21)
		#define BYPASS(x)        (((x) & 0x1) << 22)
		#define RESV0(x)        (((x) & 0x1) << 23)
		#define RESV1(x)        (((x) & 0x1) << 24)
		
		/* E/V PLL_CON1 */
		#define K(x)                 ((x) & 0xffff)
		#define MFR(x)        (((x) & 0xff) << 16)
		#define MRR(x)        (((x) & 0x1f) << 24)
		#define SEL_PF(x)        (((x) & 0x3) << 9)
		
		/* E/V PLL_CON2 */
		#define ICP_BOOST(x)    ((x) & 0x3)
		#define FSEL_E_V(x)        (((x) & 0x1) << 2)
		#define FVCO_EN(x)        (((x) & 0x1) << 3)
		#define BYPASS_E_V(x)        (((x) & 0x1) << 4)
		#define SSCG_EN(x)        (((x) & 0x1) << 5)
		#define AFC_ENB_E_V(x)        (((x) & 0x1) << 6)
		#define DCC_ENB_E_V(x)        (((x) & 0x1) << 7)
		#define EXTAFC(x)        (((x) & 0x1f) << 8)
		
		#define PLL_LOCKTIME(x)    ((x) & 0xffff)
		
		
		/* CLK_SRC_CPU */
		#define MUX_APLL_SEL(x)         ((x) & 0x1)
		#define MUX_CORE_SEL(x)         (((x) & 0x1) << 16)
		#define MUX_HPM_SEL(x)          (((x) & 0x1) << 20)
		#define MUX_MPLL_USER_SEL_C(x)  (((x) & 0x1) << 24)
		
		#define MUX_STAT_CHANGING       0x100
		
		/* CLK_MUX_STAT_CPU */
		#define APLL_SEL(x)             ((x) & 0x7)
		#define CORE_SEL(x)             (((x) & 0x7) << 16)
		#define HPM_SEL(x)              (((x) & 0x7) << 20)
		#define MPLL_USER_SEL_C(x)      (((x) & 0x7) << 24)
		#define MUX_STAT_CPU_CHANGING   (APLL_SEL(MUX_STAT_CHANGING) | \
		               CORE_SEL(MUX_STAT_CHANGING) | \
		               HPM_SEL(MUX_STAT_CHANGING) | \
		               MPLL_USER_SEL_C(MUX_STAT_CHANGING))
		
		/* CLK_DIV_CPU0 */
		#define CORE_RATIO(x)           ((x) & 0x7)
		#define COREM0_RATIO(x)         (((x) & 0x7) << 4)
		#define COREM1_RATIO(x)         (((x) & 0x7) << 8)
		#define PERIPH_RATIO(x)         (((x) & 0x7) << 12)
		#define ATB_RATIO(x)            (((x) & 0x7) << 16)
		#define PCLK_DBG_RATIO(x)       (((x) & 0x7) << 20)
		#define APLL_RATIO(x)           (((x) & 0x7) << 24)
		#define CORE2_RATIO(x)          (((x) & 0x7) << 28)
		
		/* CLK_DIV_STAT_CPU0 */
		#define DIV_CORE(x)             ((x) & 0x1)
		#define DIV_COREM0(x)           (((x) & 0x1) << 4)
		#define DIV_COREM1(x)           (((x) & 0x1) << 8)
		#define DIV_PERIPH(x)           (((x) & 0x1) << 12)
		#define DIV_ATB(x)              (((x) & 0x1) << 16)
		#define DIV_PCLK_DBG(x)         (((x) & 0x1) << 20)
		#define DIV_APLL(x)             (((x) & 0x1) << 24)
		#define DIV_CORE2(x)            (((x) & 0x1) << 28)
		
		#define DIV_STAT_CHANGING       0x1
		#define DIV_STAT_CPU0_CHANGING  (DIV_CORE(DIV_STAT_CHANGING) | \
		               DIV_COREM0(DIV_STAT_CHANGING) | \
		               DIV_COREM1(DIV_STAT_CHANGING) | \
		               DIV_PERIPH(DIV_STAT_CHANGING) | \
		               DIV_ATB(DIV_STAT_CHANGING) | \
		               DIV_PCLK_DBG(DIV_STAT_CHANGING) | \
		               DIV_APLL(DIV_STAT_CHANGING) | \
		               DIV_CORE2(DIV_STAT_CHANGING))
		
		/* CLK_DIV_CPU1 */
		#define COPY_RATIO(x)           ((x) & 0x7)
		#define HPM_RATIO(x)            (((x) & 0x7) << 4)
		#define CORES_RATIO(x)          (((x) & 0x7) << 8)
		
		/* CLK_DIV_STAT_CPU1 */
		#define DIV_COPY(x)             ((x) & 0x7)
		#define DIV_HPM(x)              (((x) & 0x1) << 4)
		#define DIV_CORES(x)            (((x) & 0x1) << 8)
		
		#define DIV_STAT_CPU1_CHANGING (DIV_COPY(DIV_STAT_CHANGING) | \
		               DIV_HPM(DIV_STAT_CHANGING) | \
		               DIV_CORES(DIV_STAT_CHANGING))
		
		/* CLK_SRC_DMC */
		#define MUX_C2C_SEL(x)     ((x) & 0x1)
		#define MUX_DMC_BUS_SEL(x) (((x) & 0x1) << 4)
		#define MUX_DPHY_SEL(x)        (((x) & 0x1) << 8)
		#define MUX_MPLL_SEL(x)        (((x) & 0x1) << 12)
		#define MUX_PWI_SEL(x)     (((x) & 0xf) << 16)
		#define MUX_G2D_ACP0_SEL(x)    (((x) & 0x1) << 20)
		#define MUX_G2D_ACP1_SEL(x)    (((x) & 0x1) << 24)
		#define MUX_G2D_ACP_SEL(x) (((x) & 0x1) << 28)
		
		/* CLK_MUX_STAT_DMC */
		#define C2C_SEL(x)     (((x)) & 0x7)
		#define DMC_BUS_SEL(x)     (((x) & 0x7) << 4)
		#define DPHY_SEL(x)        (((x) & 0x7) << 8)
		#define MPLL_SEL(x)        (((x) & 0x7) << 12)
		/* #define PWI_SEL(x)      (((x) & 0xf) << 16)  - Reserved */
		#define G2D_ACP0_SEL(x)        (((x) & 0x7) << 20)
		#define G2D_ACP1_SEL(x)        (((x) & 0x7) << 24)
		#define G2D_ACP_SEL(x)     (((x) & 0x7) << 28)
		
		#define MUX_STAT_DMC_CHANGING  (C2C_SEL(MUX_STAT_CHANGING) | \
		               DMC_BUS_SEL(MUX_STAT_CHANGING) | \
		               DPHY_SEL(MUX_STAT_CHANGING) | \
		               MPLL_SEL(MUX_STAT_CHANGING) |\
		               G2D_ACP0_SEL(MUX_STAT_CHANGING) | \
		               G2D_ACP1_SEL(MUX_STAT_CHANGING) | \
		               G2D_ACP_SEL(MUX_STAT_CHANGING))
		
		/* CLK_DIV_DMC0 */
		#define ACP_RATIO(x)       ((x) & 0x7)
		#define ACP_PCLK_RATIO(x)  (((x) & 0x7) << 4)
		#define DPHY_RATIO(x)      (((x) & 0x7) << 8)
		#define DMC_RATIO(x)       (((x) & 0x7) << 12)
		#define DMCD_RATIO(x)      (((x) & 0x7) << 16)
		#define DMCP_RATIO(x)      (((x) & 0x7) << 20)
		
		/* CLK_DIV_STAT_DMC0 */
		#define DIV_ACP(x)     ((x) & 0x1)
		#define DIV_ACP_PCLK(x)        (((x) & 0x1) << 4)
		#define DIV_DPHY(x)        (((x) & 0x1) << 8)
		#define DIV_DMC(x)     (((x) & 0x1) << 12)
		#define DIV_DMCD(x)        (((x) & 0x1) << 16)
		#define DIV_DMCP(x)        (((x) & 0x1) << 20)
		
		#define DIV_STAT_DMC0_CHANGING (DIV_ACP(DIV_STAT_CHANGING) | \
		               DIV_ACP_PCLK(DIV_STAT_CHANGING) | \
		               DIV_DPHY(DIV_STAT_CHANGING) | \
		               DIV_DMC(DIV_STAT_CHANGING) | \
		               DIV_DMCD(DIV_STAT_CHANGING) | \
		               DIV_DMCP(DIV_STAT_CHANGING))
		
		/* CLK_DIV_DMC1 */
		#define G2D_ACP_RATIO(x)   ((x) & 0xf)
		#define C2C_RATIO(x)       (((x) & 0x7) << 4)
		#define PWI_RATIO(x)       (((x) & 0xf) << 8)
		#define C2C_ACLK_RATIO(x)  (((x) & 0x7) << 12)
		#define DVSEM_RATIO(x)     (((x) & 0x7f) << 16)
		#define DPM_RATIO(x)       (((x) & 0x7f) << 24)
		
		/* CLK_DIV_STAT_DMC1 */
		#define DIV_G2D_ACP(x)     ((x) & 0x1)
		#define DIV_C2C(x)     (((x) & 0x1) << 4)
		#define DIV_PWI(x)     (((x) & 0x1) << 8)
		#define DIV_C2C_ACLK(x)        (((x) & 0x1) << 12)
		#define DIV_DVSEM(x)       (((x) & 0x1) << 16)
		#define DIV_DPM(x)     (((x) & 0x1) << 24)
		
		#define DIV_STAT_DMC1_CHANGING (DIV_G2D_ACP(DIV_STAT_CHANGING) | \
		               DIV_C2C(DIV_STAT_CHANGING) | \
		               DIV_PWI(DIV_STAT_CHANGING) | \
		               DIV_C2C_ACLK(DIV_STAT_CHANGING) | \
		               DIV_DVSEM(DIV_STAT_CHANGING) | \
		               DIV_DPM(DIV_STAT_CHANGING))
		
		/* CLK_DIV_TOP */
		#define    ACLK_400_MCUISP_RATIO(x)    (((x) & 0x7) << 24)
		#define    ACLK_266_GPS_RATIO(x)   (((x) & 0x7) << 20)
		#define    ONENAND_RATIO(x)    (((x) & 0x7) << 16)
		#define    ACLK_133_RATIO(x)   (((x) & 0x7) << 12)
		#define ACLK_160_RATIO(x)  (((x) & 0x7) << 8)
		#define ACLK_100_RATIO(x)  (((x) & 0xf) << 4)
		#define ACLK_200_RATIO(x)  ((x) & 0x7)
		
		#define DIV_STAT_TOP_CHANGING  (ACLK_400_MCUISP_RATIO(DIV_STAT_CHANGING) | \
		               ACLK_266_GPS_RATIO(DIV_STAT_CHANGING) | \
		               ONENAND_RATIO(DIV_STAT_CHANGING) | \
		               ACLK_133_RATIO(DIV_STAT_CHANGING) | \
		               ACLK_160_RATIO(DIV_STAT_CHANGING) | \
		               ACLK_100_RATIO(DIV_STAT_CHANGING) | \
		               ACLK_200_RATIO(DIV_STAT_CHANGING))
		
		/* CLK_SRC_TOP0 */
		#define MUX_ONENAND_SEL(x)     (((x) & 0x1) << 28)
		#define MUX_ACLK_133_SEL(x)        (((x) & 0x1) << 24)
		#define MUX_ACLK_160_SEL(x)        (((x) & 0x1) << 20)
		#define MUX_ACLK_100_SEL(x)        (((x) & 0x1) << 16)
		#define MUX_ACLK_200_SEL(x)        (((x) & 0x1) << 12)
		#define MUX_VPLL_SEL(x)        (((x) & 0x1) << 8)
		#define MUX_EPLL_SEL(x)        (((x) & 0x1) << 4)
		#define MUX_ONENAND_1_SEL(x)   ((x) & 0x1)
		
		/* CLK_MUX_STAT_TOP */
		#define ONENAND_SEL(x)     (((x) & 0x3) << 28)
		#define ACLK_133_SEL(x)        (((x) & 0x3) << 24)
		#define ACLK_160_SEL(x)        (((x) & 0x3) << 20)
		#define ACLK_100_SEL(x)        (((x) & 0x3) << 16)
		#define ACLK_200_SEL(x)        (((x) & 0x3) << 12)
		#define VPLL_SEL(x)        (((x) & 0x3) << 8)
		#define EPLL_SEL(x)        (((x) & 0x3) << 4)
		#define ONENAND_1_SEL(x)   ((x) & 0x3)
		
		/* CLK_SRC_TOP1 */
		#define MUX_ACLK_400_MCUISP_SUB_SEL(x)     (((x) & 0x1) << 24)
		#define MUX_ACLK_200_SUB_SEL(x)        (((x) & 0x1) << 20)
		#define MUX_ACLK_266_GPS_SUB_SEL(x)        (((x) & 0x1) << 16)
		#define MUX_MPLL_USER_SEL_T(x)     (((x) & 0x1) << 12)
		#define MUX_ACLK_400_MCUISP_SEL(x)     (((x) & 0x1) << 8)
		#define MUX_ACLK_266_GPS_SEL(x)        (((x) & 0x1) << 4)
		
		/* CLK_MUX_STAT_TOP1 */
		#define ACLK_400_MCUISP_SUB_SEL(x)     (((x) & 0x3) << 24)
		#define ACLK_200_SUB_SEL(x)        (((x) & 0x3) << 20)
		#define ACLK_266_GPS_SUB_SEL(x)        (((x) & 0x3) << 16)
		#define MPLL_USER_SEL_T(x)     (((x) & 0x3) << 12)
		#define ACLK_400_MCUISP_SEL(x)     (((x) & 0x3) << 8)
		#define ACLK_266_GPS_SEL(x)        (((x) & 0x3) << 4)
		
		
		
		
		
		
		/*CLK_DIV_LEFTBUS*/
		#define GDL_RATIO(x)   ((x) & 0x7)
		#define GPL_RATIO(x)   (((x) & 0x7) << 4)
		
		#define DIV_STAT_LEFTBUS_CHANGING  (GDL_RATIO(DIV_STAT_CHANGING) | \
		                                       GPL_RATIO(DIV_STAT_CHANGING) )
		/* CLK_SRC_LEFTBUS */
		#define MUX_MPLL_USER_SEL_L(x)     (((x) & 0x1) << 4)
		#define MUX_GDL_SEL(x)     ((x) & 0x1)
		
		/* CLK_MUX_STAT_LEFTBUS */
		#define MPLL_USER_SEL_L(x)     (((x) & 0x3) << 4)
		#define GDL_SEL(x)     ((x) & 0x3)
		
		
		/*CLK_DIV_RIGHTBUS*/
		#define GDR_RATIO(x)   ((x) & 0x7)
		#define GPR_RATIO(x)   (((x) & 0x7) << 4)
		
		#define DIV_STAT_RIGHTBUS_CHANGING (GDR_RATIO(DIV_STAT_CHANGING) | \
		                               GPR_RATIO(DIV_STAT_CHANGING) )
		
		/* CLK_SRC_RIGHTBUS */
		#define MUX_MPLL_USER_SEL_R(x)     (((x) & 0x1) << 4)
		#define MUX_GDR_SEL(x)     ((x) & 0x1)
		
		/* CLK_MUX_STAT_RIGHTBUS */
		#define MPLL_USER_SEL_R(x)     (((x) & 0x3) << 4)
		#define GDR_SEL(x)     ((x) & 0x3)
		
		
		
		
		/* Set CLK_SRC_PERIL0 */
		#define UART4_SEL(x)       (((x) & 0xf) << 16)
		#define UART3_SEL(x)       (((x) & 0xf) << 12)
		#define UART2_SEL(x)       (((x) & 0xf) << 8)
		#define UART1_SEL(x)       (((x) & 0xf) << 4)
		#define UART0_SEL(x)       ((x) & 0xf)
		
		/* Set CLK_DIV_PERIL0 */
		#define UART4_RATIO(x)     (((x) & 0xf) << 16)
		#define UART3_RATIO(x)     (((x) & 0xf) << 12)
		#define UART2_RATIO(x)     (((x) & 0xf) << 8)
		#define UART1_RATIO(x)     (((x) & 0xf) << 4)
		#define UART0_RATIO(x)     ((x) & 0xf)
		
		/* Set CLK_DIV_STAT_PERIL0 */
		#define DIV_UART4(x)       (((x) & 0x1) << 16)
		#define DIV_UART3(x)       (((x) & 0x1) << 12)
		#define DIV_UART2(x)       (((x) & 0x1) << 8)
		#define DIV_UART1(x)       (((x) & 0x1) << 4)
		#define DIV_UART0(x)       ((x) & 0x1)
		
		#define DIV_STAT_PERIL0_CHANGING   (DIV_UART4(DIV_STAT_CHANGING) | \
		                   DIV_UART3(DIV_STAT_CHANGING) | \
		                   DIV_UART2(DIV_STAT_CHANGING) | \
		                   DIV_UART1(DIV_STAT_CHANGING) | \
		                   DIV_UART0(DIV_STAT_CHANGING))
		
		/* CLK_DIV_FSYS1 */
		#define MMC0_RATIO(x)      ((x) & 0xf)
		#define MMC0_PRE_RATIO(x)  (((x) & 0xff) << 8)
		#define MMC1_RATIO(x)      (((x) & 0xf) << 16)
		#define MMC1_PRE_RATIO(x)  (((x) & 0xff) << 24)
		
		/* CLK_DIV_STAT_FSYS1 */
		#define DIV_MMC0(x)        ((x) & 1)
		#define DIV_MMC0_PRE(x)        (((x) & 1) << 8)
		#define DIV_MMC1(x)        (((x) & 1) << 16)
		#define DIV_MMC1_PRE(x)        (((x) & 1) << 24)
		
		#define DIV_STAT_FSYS1_CHANGING        (DIV_MMC0(DIV_STAT_CHANGING) | \
		                   DIV_MMC0_PRE(DIV_STAT_CHANGING) | \
		                   DIV_MMC1(DIV_STAT_CHANGING) | \
		                   DIV_MMC1_PRE(DIV_STAT_CHANGING))
		
		/* CLK_DIV_FSYS2 */
		#define MMC2_RATIO(x)      ((x) & 0xf)
		#define MMC2_PRE_RATIO(x)  (((x) & 0xff) << 8)
		#define MMC3_RATIO(x)      (((x) & 0xf) << 16)
		#define MMC3_PRE_RATIO(x)  (((x) & 0xff) << 24)
		
		/* CLK_DIV_STAT_FSYS2 */
		#define DIV_MMC2(x)        ((x) & 0x1)
		#define DIV_MMC2_PRE(x)        (((x) & 0x1) << 8)
		#define DIV_MMC3(x)        (((x) & 0x1) << 16)
		#define DIV_MMC3_PRE(x)        (((x) & 0x1) << 24)
		
		#define DIV_STAT_FSYS2_CHANGING        (DIV_MMC2(DIV_STAT_CHANGING) | \
		                   DIV_MMC2_PRE(DIV_STAT_CHANGING) | \
		                   DIV_MMC3(DIV_STAT_CHANGING) | \
		                   DIV_MMC3_PRE(DIV_STAT_CHANGING))
		
		/* CLK_DIV_FSYS3 */
		#define MMC4_RATIO(x)      ((x) & 0x7)
		#define MMC4_PRE_RATIO(x)  (((x) & 0xff) << 8)
		
		/* CLK_DIV_STAT_FSYS3 */
		#define DIV_MMC4(x)        ((x) & 0x1)
		#define DIV_MMC4_PRE(x)        (((x) & 0x1) << 8)
		
		#define DIV_STAT_FSYS3_CHANGING        (DIV_MMC4(DIV_STAT_CHANGING) | \
		                   DIV_MMC4_PRE(DIV_STAT_CHANGING))
		
		
		#endif 
		```
		
		16. 文件修改完毕，开始编译。
		```C
		写一个脚本文件，自动编译:
		root@ubuntu:/opt/u-boot-2017.03# vim auto_run.sh 
		1 #!/bin/bash
		2 
		3 echo "Clean Configuration File..."
		4 make distclean
		5 
		6 echo "Clean Obj..."
		7 make clean
		8 
		9 echo "Load Configuration File..."
		10 make tiny4412_defconfig
		11 
		12 echo "make..."
		13 make CROSS_COMPILE=arm-linux-
		
		```
		17. 提示错误
		```C
		*** Your dtc is too old, please upgrade to dtc 1.4 or newer
		Makefile:1385: recipe for target 'checkdtc' failed
		解决：
		root@ubuntu:/opt/u-boot-2017.03/doc# apt-cache search dtc
		device-tree-compiler - Device Tree Compiler for Flat Device Trees
		root@ubuntu:/opt/u-boot-2017.03/doc# apt-get install 
		device-tree-compiler
		```

		```C
		Error: You must add new CONFIG options using Kconfig
		The following new ad-hoc CONFIG options were detected:
		CONFIG_EXYNOS4412
		CONFIG_TINY4412
		
		Please add these via Kconfig instead. Find a suitable Kconfig
		file and add a 'config' or 'menuconfig' option.
		Makefile:853: recipe for target 'all' failed
		make: *** [all] Error 1
		解决：
		root@ubuntu:/opt/u-boot-2017.03# vim Makefile
		839 cfg: u-boot.cfg
		840 
		841 quiet_cmd_cfgcheck = CFGCHK  $2
		842 cmd_cfgcheck =
		843 #cmd_cfgcheck = $(srctree)/scripts/check-config.sh $2 \
		844 #       $(srctree)/scripts/config_whitelist.txt $(srctree)
		845 
		846 all:        $(ALL-y)
		这句话只用于检查配置，可以屏蔽掉
		```
		18. 使用三星提供的烧录脚本
		1. 修改文件 ./sd_fuse/tiny4412/sd_fusing.sh 
		```C
		 73 #<BL2 fusing>
		 74 echo "---------------------------------------"
		 75 echo "BL2 fusing"
		 76 #dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position
		 77 dd iflag=dsync oflag=dsync if=../../spl/tiny4412-spl.bin of=$1 seek=$bl2_position
		```
		19. 写一个烧录脚本
		```C
		root@ubuntu:/opt/u-boot-2017.03/sd_fuse/tiny4412# vim auto_fuse.sh 
		1 #!/bin/bash
		2 
		3 EXEC="sd_fusing.sh"
		4 SD_PATH="/dev/sdb"
		5 FUSE_PATH="./${EXEC}"
		6 
		7 if [ -e ${FUSE_PATH} ]
		8 then
		9     if [ -e ${SD_PATH} ]
		10     then
		11         ${FUSE_PATH} ${SD_PATH}
		12     else
		13         echo "Please Insert SD!"
		14     fi
		15 else
		16     echo "File Not Exist!"
		17 fi
		```
	+ 执行流程
		1. 使用点灯大发
		```C
		root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/
		arch/arm/cpu/armv7/start.S arch/arm/cpu/armv7/start.S
		diff --git a/../temp/u-boot-2017.03/arch/arm/cpu/armv7/start.S 
		b/arch/arm/cpu/armv7/start.S
		index 7eee54b..1165148 100644
		--- a/../temp/u-boot-2017.03/arch/arm/cpu/armv7/start.S
		+++ b/arch/arm/cpu/armv7/start.S
		@@ -49,6 +49,8 @@ save_boot_params_ret:
		        beq     switch_to_hypervisor
		 switch_to_hypervisor_ret:
		 #endif
		+
		+       
		        /*
		         * disable interrupts (FIQ and IRQ), also set the cpu to SVC32 mode,
		         * except if in HYP mode already
		@@ -61,6 +63,10 @@ switch_to_hypervisor_ret:
		        orr     r0, r0, #0xc0           @ disable FIQ and IRQ
		        msr     cpsr,r0
		 
		+       bl led_config
		+       bl led_off_all
		+       bl led_on_1
		+
		 /*
		  * Setup vector:
		  * (OMAP4 spl TEXT_BASE is not 32 byte aligned.
		@@ -87,6 +93,7 @@ switch_to_hypervisor_ret:
		 
		        bl      _main
		 
		+
		 /*------------------------------------------------------------------------------*/
		 
		 ENTRY(c_runtime_cpu_setup)
		@@ -293,3 +300,77 @@ ENTRY(cpu_init_crit)
		        b       lowlevel_init           @ go setup pll,mux,memory
		 ENDPROC(cpu_init_crit)
		 #endif
		+
		+       .globl led_config
		+led_config:
		+       ldr r0, =0x110002E0     @ GPM4CON地址
		+       ldr r1, [r0]                    
		+       bic r1, r1, #0xFF00             @ 清除高8位
		+       bic r1, r1, #0x00FF             @ 清除低8位
		+       orr r1, r1, #0x1100             @ 配置高8位位输出模式
		+       orr r1, r1, #0x0011             @ 配置低8位为输出模式 
		+       str r1, [r0]    
		+       
		+       bx lr
		+
		+       .globl led_off_all
		+led_off_all:
		+       ldr r0, =0x110002E4             @ GMP4DAT地址
		+       ldr r1, [r0]
		+       orr r1, r1, #0x0F
		+       str r1, [r0]
		+
		+       bx lr
		+               
		+       .globl led_on_1
		+led_on_1:
		+       ldr r0, =0x110002E4             @ GMP4DAT地址
		+       ldr r1, [r0]
		+       bic r1, r1, #0x01
		+       str r1, [r0]
		+
		+       bx lr                                   @ 函数返回
		+
		+       .globl led_on_2
		+led_on_2:
		+       ldr r0, =0x110002E4             @ GMP4DAT地址
		+       ldr r1, [r0]
		+       bic r1, r1, #0x02
		+       str r1, [r0]
		+
		+       bx lr                                   @ 函数返回
		+
		+       .globl led_on_3
		+led_on_3:
		+       ldr r0, =0x110002E4             @ GMP4DAT地址
		+       ldr r1, [r0]
		+       bic r1, r1, #0x04
		+       str r1, [r0]
		+
		+       bx lr                                   @ 函数返回
		+
		+       .globl led_on_4
		+led_on_4:
		+       ldr r0, =0x110002E4             @ GMP4DAT地址
		+       ldr r1, [r0]
		+       bic r1, r1, #0x08
		+       str r1, [r0]
		+
		+       bx lr                                   @ 函数返回
		+
		+       .globl bsp_delay
		+bsp_delay:
		+       ldr r0, =0x8FFFFF
		+
		+loop:
		+       sub r0, r0, #0x01
		+       cmp r0, #0x00
		+       bne loop 
		+       
		+       bx lr
		+
		+
		+               
		+
		+
		+
		(END)
		```
		2. U-BOOT_SPL 执行流程
		```C
		root@ubuntu:/opt/u-boot-2017.03# more board/samsung/common/exynos-uboot-spl.lds
		ENTRY(_start)
	
		SECTIONS
		{
		        .text :
		        {
		                __start = .;
		                *(.vectors)
		                arch/arm/cpu/armv7/start.o (.text*)
		                *(.text*)
		        } >.sram
		        . = ALIGN(4);
		}
		1. 根据ENTRY(_start)，可知先执行 __start
		2. 找到 arch/arm/lib/vectors.S 
		/*
		*************************************************************************
		*
		* Symbol _start is referenced elsewhere, so make it global
		*
		*************************************************************************
		*/
		
		.globl _start
	
		可知这个符号是一个全局符号。
		_start:
		
			#ifdef CONFIG_SYS_DV_NOR_BOOT_CFG
				.word   CONFIG_SYS_DV_NOR_BOOT_CFG
			#endif
			
			b       reset
		然后执行 reset
		3. 找到 root@ubuntu:/opt/u-boot-2017.03# more arch/arm/cpu/armv7/start.S
		4. 因为配置了CONFIG_SKIP_LOWLEVEL_INIT，
		跳过 bl      cpu_init_cp15，
		跳过 bl      cpu_init_crit，
		执行 bl _main
		5. root@ubuntu:/opt/u-boot-2017.03# more arch/arm/lib/crt0.S
		6. 执行 bl      board_init_f
		7. 找到 root@ubuntu:/opt/u-boot-2017.03# more arch/arm/mach-exynos/spl_boot.c 
		执行 void board_init_f(unsigned long bootflag); 
		执行 void do_lowlevel_init();
		8. 进入 root@ubuntu:/opt/u-boot-2017.03# more arch/arm/mach-exynos/lowlevel_init.c
		9. 执行 system_clock_init(); 初始化系统时钟
		10. 执行 exynos_pinmux_config(PERIPH_ID_UART0, PINMUX_FLAG_NONE);
		debug_uart_init(); 初始化串口0 
		11. 执行 mem_ctrl_init(); 初始化SDRAM，为了下一步加载U-BOOT.bin做准备
		12. 执行 tzpc_init(); 配置 TrustZone Protection Controller
		13. 执行 copy_uboot_to_ram()， 将u-boo.bin从启动媒介拷贝到SDRAM的
		CONFIG_SYS_TEXT_BASE 位置。
		14. 跳转到u-boot执行： 
		/* Jump to U-Boot image */
		uboot = (void *)CONFIG_SYS_TEXT_BASE;
		(*uboot)();
		```
		3. U-BOOT 执行流程
		```C

		```
	
	+ 问题
		+ 使用sd_fuse/tiny4412/sd_fusing.sh生成的bl2.bin文件，烧录到开发板，
		经过放置小灯测试，在执行 bl  board_init_f_alloc_reserve 时，会出现死机情况？
		原因：bl2.bin使用u-boot根目录的u-boot.bin制作而成，而在BL2阶段应该执行的
		文件是./spl/tiny4412-spl.bin，该文件使用./spl/u-boot-spl.bin制作而成
		见：./script/Makefile.spl中的 
		259 $(obj)/$(BOARD)-spl.bin: $(obj)/u-boot-spl.bin 
		解决：修改 ./sd_fuse/tiny4412/sd_fusing.sh，
		```C
		#<BL2 fusing>
		echo "---------------------------------------"
		echo "BL2 fusing"
		#dd iflag=dsync oflag=dsync if=./bl2.bin of=$1 seek=$bl2_position
		dd iflag=dsync oflag=dsync if=../../spl/tiny4412-spl.bin of=$1 
		seek=$bl2_position
		```
	
	+ 时钟配置
		+ 开发板启动方式
			1. 根据 Android_Exynos4412_iROM_Secure_Booting_Guide_Ver.1.00.00.pdf
			提供的方式：
	
			| 	OM[5:1] | 	启动设备 	|
			|:---------:|:-------------:|
			| 5b'00010 	| 	SDMMC_CH2	|
			| 5b'00100	| 	eMMC44_CH4	|
	
	 		通过核心板原理图，可以看出，OM0 = 1; OM1 = 0，OM4 = 0， OM5 = 0;
			通过SD卡启动时，OM2 = 1； 通过eMMC启动时，OM3 = 1;
			开发板在XusbXTI引脚，连接一个24MHz的晶振，
			参考 Exynos 4412 SCP_Users Manual_Ver.0.10.00_Preliminary0.pdf 的P455页，
			在最左边找到XusbXTI位置向上看,通过一个多路选择器输出到FINpll，而开关就是XOM[0]，
			我们知道XOM[0] = 1,因此芯片将使用XusbXTI作为系统时钟源。
		+ 路径分析
		```C
		详见P584(APLL_CON0)和P451(表格7-2)
		要想达到：Fout = 1400MHz
		MDIV = 175
		PDIV = 3
		SDIV = 0
		Fin = 24MHz
		根据公式：FOUT = MDIV * FIN / (PDIV * (2 ^ sdiv));
		-> Fout = 175 * 24 / (3 * 1) = 1400MHz
		
		/* 系统推荐频率 */
		 freq (ARMCLK) = 1400 MHz at 1.3 V
		 freq (ACLK_COREM0) = 350 MHz at 1.3V
		 freq (ACLK_COREM1) = 188 MHz at 1.3 V
		 freq (PERIPHCLK) = 1400 MHz at 1.3 V
		 freq (ATCLK) = 214 MHz at 1.3 V
		 freq (PCLK_DBG) = 107 MHz at 1.3 V
		 freq (SCLK_DMC) = 400 MHz at 1.0 V
		 freq (ACLK_DMCD) = 200 MHz at 1.0 V
		 freq (ACLK_DMCP) = 100 MHz at 1.0 V
		 freq (ACLK_ACP) = 200 MHz at 1.0 V
		 freq (PCLK_ACP) = 100 MHz at 1.0 V
		 freq (SCLK_C2C) = 400 MHz at 1.0 V
		 freq (ACLK_C2C) = 200 MHz at 1.0 V
		 freq (ACLK_GDL) = 200 MHz at 1.0 V
		 freq (ACLK_GPL) = 100 MHz at 1.0 V
		 freq (ACLK_GDR) = 200 MHz at 1.0 V
		 freq (ACLK_GPR) = 100 MHz at 1.0 V
		 freq (ACLK_400_MCUISP) = 400 MHz at 1.0 V
		 freq (ACLK_200) = 160 MHz at 1.0 V
		 freq (ACLK_100) = 100 MHz at 1.0 V
		 freq (ACLK_160) = 160 MHz at 1.0 V
		 freq (ACLK_133) = 133 MHz at 1.0 V
		 freq (SCLK_ONENAND) = 160 MHz at 1.0 V
		
		<< ------------------ CMU_CPU ------------------ >>
		24MHz->经过APLL倍频后，升至1400MHz。与系统频率一致
		-> DIVcore = 1 -> DIVcore2 = 1 -> ARMCLK = 1400MHz
		
		CLK_DIV_CPU0寄存器：
			1. ARMCLK = DOUTCORE/(CORE2_RATIO + 1);
				1400 = 1400 / (CORE2_RATIO + 1);
				-> CORE2_RATIO = 0;
			2. SCLKAPLL = MOUTAPLL/(APLL_RATIO + 1);
				-> SCLKAPLL = 1400 / (1 + 1) = 700MHz;
				（疑问：为什么APLL_RATIO = 1 ？）
			3. PCLK_DBG = ATCLK/(PCLK_DBG_RATIO + 1);
				107 = 214 / (PCLK_DBG_RATIO + 1);
				-> PCLK_DBG_RATIO = 1;
			4. ATCLK = MOUTCORE/(ATB_RATIO + 1);
				214 = 1400 / (ATB_RATIO + 1);
				-> ATB_RATIO = 6;
			5. PERIPHCLK = DOUTCORE/(PERIPH_RATIO + 1);
				1400 = 1400/(PERIPH_RATIO + 1);
				-> PERIPH_RATIO = 0;
			6. ACLK_COREM1 = ARMCLK/(COREM1_RATIO +1);
				188 = 1400 / (COREM1_RATIO + 1)；
				-> COREM1_RATIO = 7;
			7. ACLK_COREM0 = ARMCLK/(COREM0_RATIO +1);
				350 = 1400 / (COREM0_RATIO + 1);
				-> COREM0_RATIO = 3;
			8. DIVCORE_OUT = MOUTCORE/(CORE_RATIO +1);
				-> DIVCORE_OUT = 1400 / 1 = 1400MHz

		CLK_DIV_CPU1寄存器:
			1. ACLK_CORES = ARMCLK/(CORES_RATIO + 1);
				233 = 1400 / (CORES_RATIO + 1);
				-> CORES_RATIO = 5;
			2. SCLK_HPM = DOUTCOPY/(HPM_RATIO + 1);
				200 = 200 / (HPM_RATIO + 1);
				-> HPM_RATIO = 0;
			3. DOUTCOPY = MOUTHPM/(COPY_RATIO + 1);
				200 = 1400 / (COPY_RATIO + 1);
				-> COPY_RATIO = 6;
		
		<< ------------------ CMU_CPU ------------------ >>
		CLK_DIV_DMC0寄存器：
			1. ACLK_DMCP = ACLK_DMCD/(DMCP_RATIO + 1);
				100 = 200 / (DMCP_RATIO + 1);
				-> DMCP_RATIO = 1;
			2. ACLK_DMCD = DOUTDMC/(DMCD_RATIO + 1);
				200 = 400 / (DMCD_RATIO + 1);
				-> DMCD_RATIO = 1;
			3. DOUTDMC = MOUTDMC_BUS/(DMC_RATIO + 1);
				400 = 800 / (DMC_RATIO + 1);
				-> DMC_RATIO = 1;
			4. SCLK_DPHY = MOUTDPHY/(DPHY_RATIO + 1);
				400 = 800 / (DPHY_RATIO + 1);
				-> DPHY_RATIO = 1;
			5. PCLK_ACP = ACLK_ACP/(ACP_PCLK_RATIO + 1);
				100 = 200 / (ACP_PCLK_RATIO + 1);
				-> ACP_PCLK_RATIO = 1;
			6. ACLK_ACP = MOUTDMC_BUS/(ACP_RATIO + 1);
				200 = 800 / (ACP_RATIO + 1);
				-> ACP_RATIO = 3;
		
		 CLK_DIV_DMC1寄存器：
			1. ACLK_C2C = MOUTC2C_ACLK/(C2C_ACLK_RATIO + 1);
				200 = 400 / (C2C_ACLK_RATIO + 1);
				-> C2C_ACLK_RATIO = 1;
			2. SCLK_PWI = MOUTPWI/(PWI_RATIO + 1);
				100 = 800 / (PWI_RATIO + 1);
				-> PWI_RATIO = 7;
			3. SCLK_C2C = MOUTC2C / (C2C_RATIO + 1);
				400 = 800 / (C2C_RATIO + 1);
				-> C2C_RATIO = 1;
			4. SCLK_G2D_ACP = MOUTG2D_ACP / (G2D_ACP_RATIO + 1);
				200 = 800 / (G2D_ACP_RATIO + 1);
				-> G2D_ACP_RATIO = 3;
			5. IECDVSEMCLKEN = ACLK_DMCP/( DVSEM_RATIO+ 1);
				50 = 100 / ( DVSEM_RATIO+ 1);
				-> DVSEM_RATIO = 1;
			6. IECDPMCLKEN = ACLK_DMCP/( DPM_RATIO+ 1);
				50 = 100 / ( DPM_RATIO + 1);
				-> DPM_RATIO = 1;
		```

	+ 串口配置
	```C
	root@ubuntu:/opt/u-boot-2017.03# git diff ../temp/u-boot-2017.03/arch/arm/
	mach-exynos/lowlevel_init.c arch/arm/mach-exynos/lowlevel_init.c 
	diff --git a/../temp/u-boot-2017.03/arch/arm/mach-exynos/lowlevel_init.c 
	b/arch/arm/mach-exynos/lowlevel_init.c
	index 1e090fd..0a69927 100644
	--- a/../temp/u-boot-2017.03/arch/arm/mach-exynos/lowlevel_init.c
	+++ b/arch/arm/mach-exynos/lowlevel_init.c
	@@ -218,8 +218,9 @@ int do_lowlevel_init(void)
	 #ifdef CONFIG_DEBUG_UART
	 #if (defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_SERIAL_SUPPORT)) || \
	     !defined(CONFIG_SPL_BUILD)
	-               exynos_pinmux_config(PERIPH_ID_UART3, PINMUX_FLAG_NONE);
	+               exynos_pinmux_config(PERIPH_ID_UART0, PINMUX_FLAG_NONE);
	                debug_uart_init();
	+               printascii("USART0 Init .......... OK!\n");
	 #endif
	 #endif
	                mem_ctrl_init(actions & DO_MEM_RESET);
	```
		+ 打印输出
			1. 使用 printascii();可以打印字符串;
			2. 使用 printhex2() ... printhex8();可以打印数字;
	
	+ SDRAM配置
		+ 背景介绍
			1. DDR SDRAM全名叫做：双倍数据率同步动态随机存取存储器
			2. SDRAM在一个时钟周期内只传输一次数据，它是在时钟的上升期进行数据传输
			3. DDR SDRAM则是一个时钟周期内传输两次数据，它能够在时钟的上升期和下降期各传输一次数据
			4. DDR SDRAM芯片的时钟频率一般为DMC控制芯片频率的2倍
		+ 内存芯片：2片512MB的三星1600Mb/sec/pin内存颗粒，总内存大小为1GB
		+ 型号：K4B4G1646D-BCK0
		+ 手册：K4B4G1646D-BCK0.pdf
		+ 自动刷新周期：Average Refresh Period 7.8us at lower than TCASE 85C, 3.9us at 85C < TCASE < 95 C
		+ 外部时钟[主芯片提供给内存颗粒的时钟]：800MHz，主芯片需要提供给内存颗粒2个差分的
		时钟信号，CK、CK/,详见内存芯片手册P27
		+ 内部时钟[DMC时钟]：400MHz
		+ 自动刷新周期TIMINGAREF：24MHz * 7.8us（查看内存手册） = 187.2 = 0xBB
		+ TIMINGROW：查看内存手册可知，	
			
		| 参数 		| 数值 	|
		|:---: 		|:---:	|
		| t_ras		| 35	|
		| t_rc		| 48.75	|
		| t_rcd		| 13.75	|
		| t_rp		| 13.75	|
		| t_rrd		| 6		|
		| t_rfc		| 208	|


		+ 代码分析：
		```C
		
		```
		
	
	+ TZSZ
		+ tzsz现在放置在SD的705块位置，可能在拷贝tzsz时，将uboot覆盖掉。导致UBOOT出现错误
	