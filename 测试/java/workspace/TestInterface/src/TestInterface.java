interface Singer {
	public void eat();
	public void sing();
}

interface Drawer {
	public void draw();
	public void sleep();
}

public class TestInterface implements Singer,Drawer {
	public static void main(String[] args) {
		TestInterface object = new TestInterface();
		object.eat();
		object.sing();
		object.sleep();
		object.draw();
	}
	
	public void eat() {
		System.out.println("eat...");
	}
	
	public void sing() {
		System.out.println("sing...");
	}
	
	public void draw() {
		System.out.println("draw...");
	}
	
	public void sleep() {
		System.out.println("sleep...");
	}
}
