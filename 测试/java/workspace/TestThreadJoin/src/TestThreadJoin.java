import java.util.*;

public class TestThreadJoin {
	public static void main(String[] args) {
		T t = new T();
		Thread thread = new Thread(t);
		thread.setName("T");
		thread.start();
		
		try {
			thread.join();
		} catch (InterruptedException e) {
			;
		}
		
		System.out.println("My Name is " + thread.getName());
	}
}

class T implements Runnable {
	public void run() {
		for (int i=0; i<5; ++i) {
			System.out.println(new Date());
			
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				System.out.println("Bye!");
				
				return;
			}
		}
	}
}
