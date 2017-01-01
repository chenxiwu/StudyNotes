# Eclipse学习笔记

#
*作者：SY*
*2016-12-10 15:09:45*
##

+ `dpi`：Dots Per Inch(每英寸点的个数)
	公式：dpi = sqrt(x^2 + y^2) / 屏幕英寸;
	例程：屏幕英寸 = 4，分辨率 = 240X320
			dpi = sqrt(240^2 + 320^2) / 4 = sqrt(57600+102400) / 4 = 100;

+ `dp`：等同于dip(Device Independent Pixels)
	公式：px = dp * (dpi / 160)，其中160为最低dpi
	日常开发中应该使用dp作为单位
		
+ `sp`：Scaled Pixels(比例像素)
	用途：用于指定字体的大小
		
+ 外边距：layout_margin

+ 内边距：padding	

+ 两种主要的布局方式：LinearLayout、RelativeLayout
	LinearLayout：线性布局，按照行列进行布局
	RelativeLayout：相对布局
	1. android:layout_above="@id/xxx"，表示将当前控件放在xxx的上面
	2. android:layout_below="@id/xxx"，表示将当前控件放在xxx的下面
	3. android:layout_toLeftOf="@id/xxx"，表示将当前控件放在xxx的左边
	4. android:layout_toRightOf="@id/xxx"，表示将当前控件放在xxx的右边
	5. android:layout_alignLeft="@id/xxx"，表示将当前控件与xxx控件左对齐
	6. android:layout_alignRight="@id/xxx"，表示将当前控件与xxx控件右对齐
	7. android:layout_alignTop="@id/xxx"，表示将当前控件与xxx控件上对齐
	8. android:layout_alignBottom="@id/xxx"，表示将当前控件与xxx控件下对齐
	9. android:layout_alignParentLeft="true"，表示对齐到父控件的左边
	10. android:layout_alignParentRight="true"，表示对齐到父控件的右边
	11. android:layout_alignParentTop="true"，表示对齐到父控件的上边
	12. android:layout_alignParentBittom="true"，表示对齐到父控件的下边
	13. android:layout_centerInParent="true",表示对齐到父控件中心
	14. android:layout_centerHorizontal="true"，表示对齐到父控件水平中心
	15. android:layout_centerVertical="true"，表示对齐到父控件的垂直中心
	16. android:layout_alignParentStart="true",表示对齐到父控件的开始
	17. android:layout_alignParentEnd="true",表示对齐到父控件的结尾
	
+ layout_weight：用于指示“空闲空间”的分配比例，相当于权重

+ Activity
	1. 定义新的Activity
		+ 定义一个类，继承Activity类
		+ 在类中复写Activity中的onCreate方法
		+ 在AndroidManifest.xml文件中注册Activity
	
	2. 启动一个Activity
		+ 生成一个意图对象（Intent）
		+ 调用setClass方法设置要启动的Activity
		+ 调用startActivity()方法启动Axtivity
	
	3. Activity生命周期
		+ OnCreate：在Activity对象第一次创建时调用
		+ OnStart：当Activity变得可见时调用该方法
		+ OnResume：当Activity开始准备与用户交互时调用该方法
		+ OnPause：当系统即将启动另一个Activity之前调用该方法
		+ OnStop：当前Activity变得不可见时调用该方法
		+OnDestory：当前Activity被销毁之前将会调用该方法
		+ InRestart：当一个Activity再次启动之前将会调用该方法
		是成对出现的。 Create -- Destory Start -- Stop Resume -- Pause

+ Intent
	+ Intent是安卓应用程序组件之一
	+ 表示一种意图
	+ 可以传递数据，
	e.g.  
		放置数据：intent.putExtra("com.example.sy.testIntent.Name", "大水猫"); 存储键值对<Name,大水猫>
		取出数据：String name = intent.getStringExtra("com.example.sy.testIntent.Name");
			
+ 线程
	+ 只有创建视图View的线程（一般是Main Thread）才能修改视图控件，否则其他线程去修改，将产生运行时异常！！
	+ 为什么要使用多线程？
	如果所有逻辑操作，都在主线程中。如果线程阻塞，将导致页面假死。
	因此，对于一些可能产生阻塞的操作，必须放在Work Thread线程中执行。
	这样，就需要一种多线程之间可以实现通信的机制。
	+ Handler实现线程间通信
			
+ Widget	
	+ ListView
	1. 使用官方提供的布局文件		android.R.layout.android.R.layout.simple_list_item_multiple_choice、android.R.layout.simple_list_item_1 等。
	2. 使用自定义布局文件
		编写自定义布局文件xml，继承ArrayAdapter，编写相应的适配器