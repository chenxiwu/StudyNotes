
public class TestArray {
	public static void main(String[] args) {
		A[] array = new A[3];	
		
		array[0] = new A(18, "��è");
		array[1] = new A(19, "����");
		array[2] = new A(20, "����");
		
		/*
		for (int i=0; i<array.length; ++i) {
			array[i].print();
		}
		*/
		
		//��ӡ�����в���
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
		System.out.println("����:" + name + ",����:" + age);
	}
}
