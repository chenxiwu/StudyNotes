import java.util.*;

public class TestThreadInterrupt {
	public static void main(String[] agrs) {
		T t = new T();
		Thread thread = new Thread(t);
		thread.start();
		
		try {
			Thread.sleep(10000);
		} catch(InterruptedException e) {
			;
		}
		
		thread.interrupt();
	}
}

class T implements Runnable {
	public void run() {
		while (true) {
			System.out.println(new Date());
			try {
				Thread.sleep(1000);
			} catch(InterruptedException e) {
				System.out.println("Bye!");
				
				return;
			}
		}
	}
}
