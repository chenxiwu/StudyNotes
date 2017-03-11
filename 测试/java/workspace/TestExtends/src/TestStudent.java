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
		student.setName("����");
		student.setSchool("���ݵ��ӿƼ���ѧ��Ϣ����ѧԺ");
		
		System.out.println("������" + student.getName());
		System.out.println("���䣺" + student.getAge());
		System.out.println("ѧУ��" + student.getSchool());
	}
}
