
public class TestArray {
	public static void main(String[] args) {
		A[] array = new A[3];	
		
		array[0] = new A(18, "阿猫");
		array[1] = new A(19, "阿狗");
		array[2] = new A(20, "阿花");
		
		/*
		for (int i=0; i<array.length; ++i) {
			array[i].print();
		}
		*/
		
		//打印命令行参数
		for (int i=0; i<args.length; ++i) {
			System.out.println(args[i]);
		}
	}
}

class A {
	int age;
	String name;
	
	A(int age, String name) {
		this.age = age;
		this.name = name;
	}
	
	public void print() {
		System.out.println("姓名:" + name + ",年龄:" + age);
	}
}
