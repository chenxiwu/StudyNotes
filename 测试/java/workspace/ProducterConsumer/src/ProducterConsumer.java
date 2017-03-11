
public class ProducterConsumer {
	public static void main(String[] args) {
		Basket bs = new Basket();
		Producter p1 = new Producter(bs);
		Producter p2 = new Producter(bs);
		Producter p3 = new Producter(bs);
		
		Consumer c1 = new Consumer(bs);
		Consumer c2 = new Consumer(bs);
		Consumer c3 = new Consumer(bs);
		
		new Thread(p1).start();
		new Thread(p2).start();
		new Thread(p3).start();
		
		new Thread(c1).start();
		new Thread(c2).start();
		new Thread(c3).start();
	}
}

class Bread {
	private int id;
	
	Bread(int id) {
		this.id = id;
	}
	
	public String toString() {
	return "面包" + id;
	}
}

class Basket {
	private int index;
	private Bread[] bread = new Bread[5];          
	
	public synchronized void push(Bread bread) {
		while (this.index == this.bread.length) {
			try {
				this.wait();
			} catch(InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.notifyAll();
			
		this.bread[index] = bread;
		index++;
//		System.out.println("++生产了：" + bread);
	}
	
	public synchronized Bread pop() {
		while (this.index == 0) {
			try {
				this.wait();
			} catch(InterruptedException e) {
				e.printStackTrace();
			}
		}
		this.notifyAll();
		
		index--;
//		System.out.println("--消费了：" + this.bread[index]);
		return this.bread[index];
	}
}

class Producter implements Runnable {
	Basket bs = null;
	
	Producter(Basket bs) {
		this.bs = bs;
	}
	
	public void run() {
		Bread bread = null;
		for (int i=0; i<20; ++i) {
			bread = new Bread(i);
			
			/* 必须加同步块，否则打印输出与实际不一致 */
			synchronized(bs) {
				bs.push(bread);
				System.out.println("生产了：" + bread);
			}
			
			try {
				Thread.sleep(10);
			} catch(InterruptedException e) {
				;
			}
		}
	}
}

class Consumer implements Runnable {
	Basket bs = null;
	
	Consumer(Basket bs) {
		this.bs = bs;
	}
	
	public void run() {
		Bread bread = null;
		for (int i=0; i<20; ++i) {
			
			/* 必须加同步块，否则打印输出与实际不一致 */
			synchronized(bs) {
				bread = bs.pop();
				System.out.println("    消费了：" + bread);
			}
			
			try {
				Thread.sleep(10);
			} catch(InterruptedException e) {
				;
			}
		}
	}
}
