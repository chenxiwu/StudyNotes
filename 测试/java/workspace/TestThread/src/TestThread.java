
/**
 * ����1
 */
/*
public class TestThread {
	public static void main(String[] args) {
		T t = new T();
		Thread thread = new Thread(t);
		thread.start();
		
		for (int i=0; i<100; ++i) {
			System.out.println("���̣߳�" + i);
		}
	}
}

class T implements Runnable{
	public void run() {
		for (int i=0; i<100; ++i) {
			System.out.println("��֧��" + i);
		}
	}
}
*/

/**
 * ������
 * @author SY
 *
 */
public class TestThread {
	public static void main(String[] args) {
		T t = new T();
		t.start();
		
		for (int i=0; i<100; ++i) {
			System.out.println("���̣߳�" + i);
		}
	}
}

class T extends Thread {
	public void run() {
		for (int i=0; i<100; ++i) {
			System.out.println("��֧��" + i);
		}
	}
}

