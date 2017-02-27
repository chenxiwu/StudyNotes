# QT学习笔记

#
*作者：SY*
*2017-2-26 12:37:46*
##

+ 软件安装
	+ 安装 Visual Studio 2015
		1. 下载地址：
		http://download.microsoft.com/download/B/8/F/B8F1470D-2396-4E7A-83F5-AC09154EB925/vs2015.ent_chs.iso
		2. 安装时使用自定义安装方式，注意选择C++组件	
	+ 安装调试器
		1. 参考链接：
		https://www.librehat.com/qt-creator-on-windows-debugger-installation-and-configuration/
		2. 进入网站：
		https://developer.microsoft.com/en-us/windows/hardware/windows-driver-kit
		选择：Get Debugging Tools for Windows (WinDbg) (from the SDK)
		下载后得到文件名：	SDKSETUP.EXE
		点击Install，下一步。只选择：Debugging Tools For Windows 等待下载安装完成。

	+ 安装 Qt Creator
		1. 该软件是Qt的集成开发环境。
		2. 下载地址：
		https://www.qt.io/download-open-source/
		选择：Qt 5.8.0 for Windows 64-bit (VS 2015, 1.0 GB)    (info)
		3. 安装完成后，进入 “工具” -- “选项” -- “构建和运行” -- “构建套件”，
		只要安装Visual Studio，编译器会自动识别。安装调试器后，手动选择cdb调试器。
		4. 安装完毕后，即可在 Qt Creator中创建项目。
	
+ 小技巧
	+ 给应用程序添加图标
		1. 创建一个项目后，如果已经编译运行，则需要先删除 Debug、Release 文件夹，否则将看不到图标。
		2. 选择一个图片，进入网站 http://ico.storyren.com/ 生成一个.ico文件，并放入源程序目录。命名为：myappico.ico
		3. 进入项目文件 xxx.pro文件，在最后添加 `RC_ICONS = myappico.ico`
		4. 重新编译，即可看到应用程序的图标出现。

+ 常见问题
	+ 问题：点击可执行文件，提示：找不到dll文件
	> 解决：
	1. 可以在系统环境变量中添加路径：`C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`
	但是将程序打包交给其他人仍然无法运行。
	2. 在路径`C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`中，找到缺失的文件，放入.exe所在的文件夹中，一起打包发给用户
	3. 使用静态编译。