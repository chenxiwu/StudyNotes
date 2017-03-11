import java.util.*;

public class TestCollection {
	public static void main(String[] args) {
		/*
		Collection c = new ArrayList();
		
		c.add("Hello World!");
		c.add(new Integer("123"));
		
		System.out.println(c);
		System.out.println("对象个数：" + c.size());
		*/
		
		/*
		Collection c = new ArrayList();
		
		c.add("Hello World!");
		c.add(new Float(1.234));
		c.add(new Student(12,"小美"));
		System.out.println(c);
		
		c.remove("Hello World!");
		System.out.println(c);
		
		c.remove(new Float(1.234));
		System.out.println(c);
			
		c.remove(new Student(12,"小美"));
		System.out.println(c);
		*/
		
		Collection c = new HashSet();
		
		c.add("Hello World!");
		c.add(new Float(1.234));
		c.add(new Student(12,"小美"));
		System.out.println(c);
		
		c.remove("Hello World!");
		System.out.println(c);
		
		c.remove(new Float(1.234));
		System.out.println(c);
			
		c.remove(new Student(12,"小美"));
		System.out.println(c);
		
	}
}


class Student {
	int age; 
	String name;
	
	Student(int age, String name) {
		this.age = age;
		this.name = name;
	}
	
	public String toString() {
		return name;
	}
	
	public boolean equals(Object obj) {
		if (obj instanceof Student) {
			Student student = (Student)obj;
			if (name.equals(student.name) && (this.age == student.age)) {
				return true;
			}
		}
		
		return false;
	}
	
	public int hashCode() {
		return name.hashCode();
	}
}


