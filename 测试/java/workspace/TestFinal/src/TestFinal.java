/* final类不能被继承 */
final class A {
	final int a = 3;
	
	/* final 方法不能被重写 */
	/*
	public final void fun() {
		;
	}
	*/
}

class B extends A {
	/*
	public void fun() {
		;
	}
	*/
}

public class TestFinal {
	public static void main(String[] args) {
		A a = new A();
		/* final变量不能被重写 */
		//a.a = 2;
	}
}
