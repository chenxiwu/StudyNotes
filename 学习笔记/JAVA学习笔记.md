# JAVA学习笔记

#
*作者：SY*
*2016-11-12 12:45:43*
##

+ 数据类型
	+ 知识点
		1. char、byte、short 进行运算时，全部转换为int类型。
		2. 局部变量使用之前必须赋值。
		3. 成员变量不需要初始化，默认值为0
	
+ 常见错误
	+ 问题：
	```JAVA
		char a = ‘a’; 
	 	byte b = 2;
	 	byte c = a + b;
	```
	 错误原因：
	 	a、b进行运算时，转换为int类型，将计算出的结果赋值给byte类型出错。
	 	
+ 格式
	1. 大括号对齐
	2. 语句块之间加空行
	3. 类名采用大驼峰命名
	4. 方法名采用小驼峰命名
	  
+ 引用类型
	1. 除了基本类型以外的所有类型都是引用类型
	2. 引用分配了2块内存，1块是堆内存、1块是栈内存。
		形如：String str = new String"Hello World");
	
+ 构造函数
	1. 对于普通成员方法而言，没有形参可以不写void，但是必须写返回值类型！！！
	2. 构造函数是一种特殊的成员方法，没有返回值！！！且方法名必须与类名一致。
	3. 形如：
	```JAVA
	public class Persion {
		int id;
		int age;
		
		Persionint id, int age) {
			id = id;
			age = age;
		}
	}
	```
+ 函数重载OverLoad. 
	1. 定义：方法名相同，形参类型不同或者形参个数不同，便可以构成重载。
	2. 只有返回值不同的2个函数不能构成重载。
	3. 构造方法也可以构成重载。

+ static
	1. 对于普通的成员变量，每 new 一次，便重新分配一个成员变量。而对于static 修饰的成员变量，所有 new 出来的对象共用同一个。
	2. static 修饰的变量被存放在 data 段，非stack段，非heap段
	3. 静态变量属于类本身，不属于任何一个对象。所有对象共享同一个 static 变量。
	4. 就算没有对象也可以访问 static 变量，使用 “类名.成员变量名” 访问
	5. 静态变量不能使用this指针访问，因为静态变量是属于类本身的，不属于任一个对象。只能通过 类名.对象名 访问。

+ package
	1. 为了解决2个类名冲突的问题
	2. package放在java源文件的第一条语句
	3. 只有java.lang不需要import，其他包都需要import

+ 继承
	1. 通过继承子类可以拥有父类所有成员。包括私有成员
	2. 只允许单继承。

+ 访问控制
	1. private：只有在类的内部可以访问
	2. default：具有包权限，只要在一个包里都可以访问
	3. protected：允许子类对象访问
	4. public：在任何地方都可以访问

+ 重写OverWrite. 
	1. 重写方法和被重写方法具有相同方法名、参数列表、返回类型	
	2. 子类继承父类后，可以重写父类方法
	3. 重写方法不能比父类方法具有更严格的权限

+ super
	1. 在具有继承关系的上下文中，this代表当前对象，super代表父类对象

+ 继承中的构造方法
	1. 子类对象的构造过程中需要先调用父类的构造方法！！！
	2. 使用superargs)可以访问父类构造方法
	3. 使用thisargs)可以访问子类的构造方法
	4. 如果子类的构造方法没有显示显示调用父类的构造方法，则编译器自动调用父类默认的无参构造方法

+ Object类
	1. 是所有的类的父类

+	equals
	1. 用于比较两个对象的内容是否一致

+ 动态绑定/多态
	+ 指在运行期间，判断所引用对象的实际类型，根据实际类型调用相应的方法。
	+ 动态绑定3个条件：
		1. 要有继承
		2. 方法要重写
		3. 父类引用指向子类对象
	
+ 抽象类abstract)
	1. 目的：作为父类时，并没有实现自己的必要，但是有定义的必要。因为子类需要继承，从而实现多态。
	2. 形式：public abstract void fun);
	3. 含有抽象方法的类，必须使用abstract修饰。
	4. 子类继承抽象类，必须实现父类的抽象方法。
	5. 抽象类不能被实例化。
	6. 抽象方法只需要声明，不需要实现。

+ final
	1. final的变量的值不能被改变
	2. final的方法不能被重写
	3. final的类不能被继承

+ 接口interface)
	1. 接口是一种特殊的抽象类，只包含常量和方法的定义，而没有变量和方法的实现。
	2. 示例：
	```JAVA
	public interface Runner {
		/* 不属于某一个对象，且不可改变 */
		public static final int id = 1;
		
		/* 不需要写abstract */
		public void run);
		public void stop);
		public void start);
	}
	```
	3. 类可以实现多个接口，相当于多继承
	4. 声明的属性，只能是public static final 类型
	5. 内部方法不需要加abstract关键字修饰
	6. 类和类之间可以继承，接口和接口之间可以继承，类和接口之间只能实现

+ 异常
	1. 是Java提供的用于处理程序中错误的一种机制。
	2. 组成架构：ThrowableError,Exception), ExceptionRuntimeException, ...)
	3. RuntimeException的子类属于可选择性的捕获
	4. 捕获异常框架
	```
	try {
		;程序语句
	} catchException e) {
		;Exception1 Handler
	} catchException e) {
		;Exception2 Handler
	} finally {
		;打扫战场，无论是否有异常都会执行。
	}
	```
	5. e.printStackTrace) 打印异常调试信息
	6. getMessage) 得到异常事件的信息
	7. 自定义异常
		public void functionint a) throws ArithmeticException {
			if a == 0) {
				throw new ArithmeticException"除零异常！");
			}
		}
	8. finally 用于为异常处理提供一个统一的出口。
	9. 自己处理不了的方法可以继续向外抛出异常，交给调用自己的方法的对象处理。

+ 数组
	1. 定义：多个相同类型的数据类型集合。
	2. 格式：Type[] array;
	3. 数组定义与赋值的操作分两步进行。
	4. 数组在堆内存中创建，在栈中引用。	
	5. A[] array = new A[3];
		array.length：取出数组长度

+ String类
	1. 代表“不可变”的字符序列。

+ StringBuffer类
	1. 代表“可变”的字符序列。	

+ file类
	1. 文件的相关操作。
	2. 对于新建文件时，需要调用函数 file.getParentFile).mkdirs); 才能创建相关文件。
		如果使用 file.mkdirs); 则创建的是文件夹，没有文件。
	
+ enum类
	1. 在 java.lang.Enum类中
	2. 语法：public enum Color = {red, green, blue};	

+ 容器
	1. 定义：一组任意类型的数据集合。
	2. Collection接口：定义了存取一组对象的方法，其子接口Set和List分别定义了存储方式。
	3. Set接口：Set中的数据对象没有顺序而且不可重复。主要包括：HashSet
	4. List接口：List中的数据对象有顺序且可以重复。主要包括：ArrayList、LinkedList
	5. Collection c = new ArrayList"Hello World!"); 
		Collection是接口类型，ArrayList实现了该接口，可以说 父类引用指向子类对象，提供了极大的灵活性。
		但是形参不能为“基础类型”的变量，因为基础类型的变量在堆栈中定义，随时可能消失。
		形参都是以对象引用的形式存储在容器内部，而不是具体的对象。
	6. Iterator接口：用来遍历容器内的元素
	7. Set接口
	8. List接口：是Collection的子接口，容器空间不够了，可以自动扩充。很像数组，但是数组不可扩充。
	9. Collections类：包含了很多List接口的操作方法。
	10. Map接口：Map类中存储的键-值对通过键来标识，因此不可重复。
			主要包括：HashMap、TreeMap	
		
+ 泛型
	1. 原来所有的数据类型装载到容器中，再取出来都变成Object类型，需要强制类型转换，容易出错！
	2. 什么时候使用泛型？只要API文档中包含<E>,则可以使用泛型。

+ Stream流. 
	1. 在 Java 程序中，对于数据的输入/输出操作以“流”方式进行。
	2. 存在于Java.io包中。
	3. 字节流1个字节)：InputStream、OutputStream
	4. 字符流2个字节)：Reader、Writer
	5. 处理流：BufferedReader、BufferedWriter
	6. Object流：可以将整个类写入到硬盘或者从硬盘读取

+ 线程
	1. 线程是一个程序内部的顺序控制流。
	2. Java中通过Java.lang.Thread类实现的。
	3. 两种方法启动多线程：
		法1：
			需要多线程执行的类，需要实现Runnable接口，需要重写接口的Run方法。
			需要创建Thread对象，调用Start方法开始多线程。
		法2：
			需要多线程执行的类，需要继承Thread类，重写run方法
			调用start方法开始多线程。
	4. 推荐方法1，能够使用接口，尽量不要使用继承。
	5. sleep：使当前进程进入睡眠状态
	6. join：等待join的进程执行完毕，继续执行。
	7. yield：暂时释放一次CPU占用
	8. 线程同步：使用synchronized作为标识，相当于互斥锁
	9. 死锁问题：通过加大锁的粒度解决死锁问题
	10. synchronized：同步代码块保证同一时刻只有一个线程访问当前对象的属性或者方法。

+ 网络编程
	1. TCP
	2. UDP

+ AWT
	1. FlowLayout：是 panel 类默认的布局管理器。
	2. BorderLayout：是 Frame 类默认的布局管理器。分为东、西、南、北、中 5个区域。
	3. GridLayout:将屏幕分为很多小格子，包含XX行，XX列
	4. 事件监听：实现ActionListener接口

+ 内部类
	1. 可以方便访问包内类的成员
	2. 防止其他类访问。


+ 总结
	1. 静态方法不能访问非静态成员
		解释；静态方法对于类来说只有一份，只要类存在，则静态方法已经存在。不需要new出一个对象才能访问。
			而非静态成员只有在new出一个对象后才存在。你不能要求一个已存在的东西访问一个不一定存在的东西。
	2. 通过 <类名.静态成员> 访问
	3. 打包jar：在命令行进入需要打包的class目录，输入：jar -cxf xxx.jar *.* 
	4. 增强型for： 
	```JAVA
	Type arr[] = {1,2,3};
	for Type i : arr) {
		//Do SomeThing...
	}
	```

	