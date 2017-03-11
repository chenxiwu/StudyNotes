class People {
	private int age;
	private String name;
	
	public void setAge(int age) {
		this.age = age;
	}
	
	public int getAge() {
		return age;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
}

class Student extends People {
	private String school;
	
	public void setSchool(String school) {
		this.school = school;
	}
	
	public String getSchool() {
		return school;
	}
}

public class TestStudent {
	public static void main(String[] args) {
		Student student = new Student();
		student.setAge(25);
		student.setName("孙宇");
		student.setSchool("杭州电子科技大学信息工程学院");
		
		System.out.println("姓名：" + student.getName());
		System.out.println("年龄：" + student.getAge());
		System.out.println("学校：" + student.getSchool());
	}
}
