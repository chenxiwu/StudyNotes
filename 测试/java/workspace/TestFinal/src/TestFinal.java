/* final�಻�ܱ��̳� */
final class A {
	final int a = 3;
	
	/* final �������ܱ���д */
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
		/* final�������ܱ���д */
		//a.a = 2;
	}
}
