# Altium Designer 学习笔记

#
*作者：SY*
*2017-2-7 08:56:57*
##

+ 常用命令
	+ 命令集
		1. 画线：P + W
		2. 测量间距： Ctrl + M
		3. 延长元器件之间的连接线：选中元器件，按住Ctrl键，拖动。
		4. 快速复制：点击要复制的元器件，按住Shift，拖动。
		5. 快速连接相对应的引脚：先将两个元器件引脚接触，按住Ctrl键，拖动
	
+ 规	范
	+ 原理图：
		1. 引脚间距：100mil == 2.54mm
	
	+ 原理图库
		+ Units
			1. 选择“Use Imperial Unit System”
			2. 选择“Dxp Defaults”
			
		+ Grids
			1. Snap：10
			2. Visible：10
			
+ 常见问题
	+ 原理图
		+ 问题：画原理图时，怎么固定画线颜色？
		解决：画线时，按下TAB键，选择一种颜色。
		
		+ 问题：怎么水平、垂直镜像翻转元件？
		解决：
			1. 输入法切换至英文状态
			2. 选中该器件时，鼠标左键按住不放，鼠标呈十字状，器件为可移动状态。
			3. 同时按键盘上的X或Y：X为水平左右翻转；Y为垂直上下翻转。
	
		+ 问题：画线时，怎么走斜线？
		解决：按下“Shift + BackSpace”

		+ 问题：元器件下面出现波浪线，编译出警告：
		`Details Duplicate Component Designators C? at 95,520 and 95,450`
		解决：因为注释出现重名，重新注释一遍，不能使用同一编号。	
		
		+ 问题：怎么修改单位？
		单位：右键选择 Options -- Document Options -- Imperial unit used，选择 Mils
	
	+ 原理图库
		+ 问题：画原理图库时，怎么改变引脚方向？
		解决：鼠标选中引脚后，按下空格键。
						
		+ 问题：怎么下载原理图库？
		解决：http://techdocs.altium.com/display/ADOH/Download+Libraries

		+ 问题：怎么安装常用元器件库？
		解决：进入Altium官网，http://www.altium.com.cn/，依次进入：Resources / Design Content / Unified Components,
		找到相关库下载。

	+ 语言
		+ 问题：怎么切换中文显示？
		解决：选择 Preference -- System -- General -- Localization -- Use Localized resources 
		-- Display localized hints only，重启软件。

	