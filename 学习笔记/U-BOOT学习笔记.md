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
	
+ 移植U-BOOT
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