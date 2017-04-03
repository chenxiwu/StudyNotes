# PCB设计学习笔记

#
*作者：SY*
*2017-1-19 09:26:07*
##

+ 元器件
	+ 继电器
		1. 线包需要添加续流二极管
		2. PCB上需要丝印 NO/NC标识

+ 原理图
	1. VDD： 3.3V
	2. VDDA： 用于模拟电压电源，3.3V
	3. VBAT： 用于备份域电源，3.3V
	4. VSS:  作为参考端接地，0V
	5. VSSA： 作为模拟电源地，0V
	6. 单片机电源引脚需要添加滤波电容，一般为0.1uF
	
+ 知识点
	+ 问题：晶振旁边的电容作用？
	解答：一般并联在晶振两端，连接GND。作为负载电容，容值是确定的。查看芯片手册得出：5pF~25pF之间，一般取20pF

	+ 问题:STM32单片机启动配置？
	解答：通过stm32f1xx参考手册，找到启动配置：

	| BOOT1  | BOOT0 |	启动模式 	|  
	| :---:  | :---: | :---:		|
	|  	X	 |  0	 | 主闪存存储区	|
	| 	0	 |	1	 | 系统存储器		| 
	|	1	 |	1	 | 内置SRAM		|

	+ JTAG接口
	JLINK是SEGGER公司的仿真器，找到“J-Link BASE”页，下载文档：UM08001_JLink.pdf
	找到“16.1.1 Pinout for JTAG”页，
	引脚：nTRST（JTAG Reset. Output from J-Link to the Reset signal of the target JTAG port. 
	Typically connected to nTRST of the target CPU. 
	This pin is normally pulled HIGH on the target to avoid unintentional resets when there is no connection.）

	+ nRST复位引脚
	通过数据手册可以查到电容容值（0.1uF == 104）

	+ 电源VDD与地VSS之间的电容
	通过数据手册可以查到电容容值（5X100nF + 1X4.7uF）
