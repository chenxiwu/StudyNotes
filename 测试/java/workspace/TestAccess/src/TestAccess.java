import Student.Student;

class People {
	private int i;
	int j;
	protected int k;
	public int l;
}

class Student1 extends People {
	void access() {
		//默认权限：在包内部，但是有继承关系可以访问
		j = 0;
		k = 0;
	}
}

class Student2 {
	void access() {
		Student sunyu = new Student();
		
		//默认权限：在包外部，不可访问
		System.out.println(sunyu.i);
		
		//保护权限：在包外部，不可访问
		System.out.println(sunyu.j);
	}
}

public class TestAccess extends Student {
	public static void main (String[] args) {
		People people = new People();
		
		//私有权限：私有成员不能跨类访问
		System.out.println(people.i);
		
		//默认权限：包内部可以访问
		System.out.println(people.j);
		
		Student sunyu = new Student();
		
		//保护权限：在包外部，有继承关系，不可访问？
		System.out.println(j);
		
		
	}
}
