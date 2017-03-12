# QT学习笔记

#
*作者：SY*
*2017-2-26 12:37:46*
##

+ 软件安装
	+ 有两种安装方式：一种是使用MinGW作为编译器，一种是使用微软的VS作为编译器。
		1. 使用VS2015
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

	2. 使用MinGW（推荐）
		+ 直接下载安装MinGW版本的软件即可，注意在安装时勾选 MinGW。
		+ 设置MinGW环境变量： 
		1. 新建 MINGW_HOME 值为C:\Qt\Qt5.8.0\Tools\mingw530_32 （你的安装路径）
		2. path变量添加“;%MINGW_HOME%\bin;"
	
+ 常用操作
	+ 使用快捷键
		1. 输入`&F`表示设置快捷键`Alt+F`
	
	+ 忽略大小写
		1. Qt::CaseInsensitive
	
	+ 忽略空白字符
		1. QString::trimmed()方法

	+ 资源图片在菜单栏不显示
		1. 删除工程下面整个DEBUG文件夹，重新运行

	+ 代码补全
		1. 默认 QT Creator 使用快捷键：`Ctrl + Space`，和输入法产生冲突。
		进入 “工具” -- “选项” -- “环境” -- “键盘” -- “Conplete This”，
		使用宏录制方式，按下 `Alt + /`

	+ 给应用程序添加图标
		1. 创建一个项目后，如果已经编译运行，则需要先删除 Debug、Release 文件夹，否则将看不到图标。
		2. 选择一个图片，进入网站 http://ico.storyren.com/ 生成一个.ico文件，并放入源程序目录。命名为：myappico.ico
		3. 进入项目文件 xxx.pro文件，在最后添加 `RC_ICONS = myappico.ico`
		4. 重新编译，即可看到应用程序的图标出现。

	+ 生成dll动态链接库
		1. 在QT Creator中新建项目，选择 `Library`->`C++库`，一路Next直至完成。
		2. 编写程序。
		3. 选择 `release` 版本，点击 `构建项目`。生成dll文件。

	+ 使用dll动态链接库 
		1. 在项目文件.pro中添加：`LIBS     += "xxx.dll"`
		2. 将动态链接库对应的头文件拷贝到工程目录
		3. 将动态链接库对应的.dll文件拷贝到 `DEBUG` 目录。
		4. 然后就可以像正常调用某个类，直接调用动态链接库内的方法。

	+ 编译 Libcurl 实现TFTP协议
		参考 http://blog.csdn.net/xueyushenzhou/article/details/51702672
		使用命令编译：`mingw32-make -f Makefile.m32`
		在Lib目录生成：libcurl.dll

	+ 将项目文件 源文件放入/SRC文件夹 头文件放入/INC文件夹，编译出错
		1. 在.pro 文件中添加：INCLUDEPATH += $$PWD/INC/ 即可编译通过

+ 常见问题

	+ 问题：点击可执行文件，提示：找不到dll文件
	> 解决：
	1. 可以在系统环境变量中添加路径：`C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`
	但是将程序打包交给其他人仍然无法运行。
	2. 在路径`C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`中，找到缺失的文件，放入.exe所在的文件夹中，一起打包发给用户
	3. 使用静态编译。
	
	+ 问题：QT5中文乱码
	> 原因：字符编码问题
	> 解决：
	1. 点击 “工具” -- “选项” -- “文本编辑器” -- “行为” -- “文件编码”，
	将UTF-8 BOM项修改为 “如果编码是UTF-8则添加”
	2. 如果使用中文常量：使用 `QStringLiteral("大水猫")`
	3. 如果是引用字符串变量，使用 `QString::fromLocal8Bit("大水猫");`

	+ 问题：QT Creator左侧的 “帮助、运行、调试 等快捷菜单”消失了？
	+ 解决：
	1. 进入目录：C:\Users\SY\AppData\Roaming，找到QTProject文件夹，整个删掉，重新打开QT Creator。

	+ 问题： 连接MySql数据库，使用Qt命令行，提示：`QSqlDatabase: QMYSQL driver not loaded`?
	+ 解决：
	1. 进入 MySQL的安装目录：`C:\Program Files\MySQL\MySQL Server 5.7\lib`，拷贝文件`libmysql.dll`
	到QT的安装目录：`C:\Qt\Qt5.8.0\5.8\msvc2015_64\bin`
	2. 添加环境变量：`C:\Program Files\MySQL\MySQL Server 5.7\bin`

	+ 问题：连接MySQL，`db.setDatabaseName("test1");` 使用`db.open()`返回false？
	+ 原因：MySQL并没有名叫 `test1` 的数据库。手动创建一个test1数据库，重新连接。

	+ 问题：Qt发布错误：无法定位程序输入点于动态链接库QtCore5.dll？
	+ 原因：在系统环境变量Path路径中，还有一个独立的MinGW，而且这个 
	环境变量 `C:\MinGW\bin\`放在了`C:\Qt\Qt5.8.0\5.8\mingw53_32\bin\`的前面。导致QT编译时使用的是前面的动态链接库。
	解决：将他们的顺序对调。