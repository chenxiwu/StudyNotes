
public class TestDeadLock implements Runnable {
	private int flag = 0;
	private static Object o1 = new Object();
	private static Object o2 = new Object();
	
	public static void main(String[] args) {
		TestDeadLock deadLock1 = new TestDeadLock();
		TestDeadLock deadLock2 = new TestDeadLock();
		
		Thread t1 = new Thread(deadLock1);
		Thread t2 = new Thread(deadLock2);
		deadLock1.flag = 0;
		deadLock1.flag = 1;
		t1.start();
		t2.start();
	}
	
	public void run() {
		if (flag == 0) {
			System.out.println("flag = 0 开始运行...");
			synchronized(o1) {
				try {
					Thread.sleep(1000);
				} catch(InterruptedException e) {
					;
				}
				
				synchronized(o2) {
					System.out.println("flag = 0 结束运行...");
				}
			}
		} else if (flag == 1) {
			System.out.println("flag = 1 开始运行...");
			synchronized(o2) {
				try {
					Thread.sleep(1000);
				} catch(InterruptedException e) {
					;
				}
				
				synchronized(o1) {
					System.out.println("flag = 1 结束运行...");
				}
			}
		}
	}
}
