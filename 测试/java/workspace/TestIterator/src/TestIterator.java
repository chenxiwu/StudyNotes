import java.util.*;

public class TestIterator {
	public static void main(String[] args) {
		Collection c = new HashSet();
		c.add(new Student(12));
		c.add(new Student(13));
		
		for (Iterator i=c.iterator(); i.hasNext(); ) {
			Student s = (Student)i.next();
			s.print();
			
			if (s.getAge() < 13) {
				i.remove();
			}
		}
		
		System.out.println("----------");
		
		for (Iterator i=c.iterator(); i.hasNext(); ) {
			Student s = (Student)i.next();
			s.print();
		}
	}
}

class Student {
	private int age;
	
	public Student(int age) {
		this.age = age;
	}
	
	public int getAge() {
		return age;
	}
	
	public void print() {
		System.out.println("ÄêÁä£º" + age);
	}
}


