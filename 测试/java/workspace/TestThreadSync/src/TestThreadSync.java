
public class TestThreadSync implements Runnable {
	Time t = new Time();
	
	public static void main(String[] args) {
		TestThreadSync tts = new TestThreadSync();
		Thread thread1 = new Thread(tts);
		Thread thread2 = new Thread(tts);
		thread1.setName("线程1");
		thread2.setName("线程2");
		
		thread1.start();
		thread2.start();
	} 
	
	public void run() {
		t.incTime(Thread.currentThread().getName());
	}
}

class Time {
	private static int time = 0;
	
	public synchronized void incTime(String name) {
		time++;
		try {
			Thread.sleep(1);
		} catch(InterruptedException e) {
			;
		}
		
		System.out.println(name + " 是第 " + time + "个访问的对象");
	}
}
