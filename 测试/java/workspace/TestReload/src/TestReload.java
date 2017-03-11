class Persion {
	int id;
	int age;
	
	Persion(int id) {
		this.id = id;
	}
	
	Persion(int id, int age) {
		this.id = id;
		this.age = age;
	}
	
	void show() {
		System.out.println("id = " + id);
		System.out.println("age = "+ age);
	}
}

public class TestReload {
	public static void main (String[] args) {
		Persion sunyu = new Persion(9527);
		sunyu.show();
		
		Persion dasuimao = new Persion(10,20);
		dasuimao.show();
	}
	
}
