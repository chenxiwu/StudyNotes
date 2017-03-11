
public class TestStructFunction {
	int id;
	
	public static void main (String[] args) {
		Persion sunyu = new Persion(9527);
		sunyu.printID();
		
	TestStructFunction dasuimao = new TestStructFunction(1111);
	dasuimao.printID();	
	}
	
	TestStructFunction(int id) {
		this.id = id;
	}	
	
	public void printID() {
		System.out.println("我的ID是 "+ id + "号。");
	}
}

class Persion {
	int id;
	
	Persion(int id) {
		this.id = id;
	}
	
	public void printID() {
		System.out.println("我的ID是 "+ id + "号。");
	}
}