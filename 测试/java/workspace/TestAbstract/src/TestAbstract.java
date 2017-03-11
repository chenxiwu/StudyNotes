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
		System.out.println(color + "��è��...");
	}
	
	public void showColor() {
		System.out.println("�ҵ���ɫ��" + color);
	}
}

class Dog extends Animal {
	private String color;
	
	Dog(String name, String color) {
		super(name);
		this.color = color;
	}
	
	public void happy() {
		System.out.println(color + "�Ĺ���...");
	}
	
	public void showColor() {
		System.out.println("�ҵ���ɫ��" + color);
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
		Cat cat = new Cat("��ˮè", "��ɫ");
		Dog dog = new Dog("���Ϲ�", "��ɫ");
		
		/* ��̬�󶨣���������ָ��������󣬵������෽�� */
		Lady lady1 = new Lady("С��", cat);
		lady1.Happy();
		lady1.showColor();
		
		Lady lady2 = new Lady("С��", dog);
		lady2.Happy();
		lady2.showColor();
	}
}
