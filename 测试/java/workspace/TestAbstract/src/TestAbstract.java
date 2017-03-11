abstract class Animal {
	private String name;
	
	Animal(String name) {
		this.name = name;
	}
	
	public abstract void happy();
	public abstract void showColor();
}

class Cat extends Animal {
	private String color;
	
	Cat(String name, String color) {
		super(name);
		this.color = color;
	}
	
	public void happy() {
		System.out.println(color + "的猫叫...");
	}
	
	public void showColor() {
		System.out.println("我的颜色是" + color);
	}
}

class Dog extends Animal {
	private String color;
	
	Dog(String name, String color) {
		super(name);
		this.color = color;
	}
	
	public void happy() {
		System.out.println(color + "的狗叫...");
	}
	
	public void showColor() {
		System.out.println("我的颜色是" + color);
	}
}

class Lady {
	private String name;
	private Animal animal;
	
	Lady(String name, Animal animal) {
		this.name = name;
		this.animal = animal;
	}
	
	public void Happy() {
		animal.happy();
	}
	
	public void showColor() {
		animal.showColor();
	}
}

public class TestAbstract {
	public static void main(String[] args) {
		Cat cat = new Cat("大水猫", "白色");
		Dog dog = new Dog("吴老狗", "黑色");
		
		/* 动态绑定，父类引用指向子类对象，调用子类方法 */
		Lady lady1 = new Lady("小美", cat);
		lady1.Happy();
		lady1.showColor();
		
		Lady lady2 = new Lady("小花", dog);
		lady2.Happy();
		lady2.showColor();
	}
}
