import java.util.*;

public class TestComparable {
	public static void main (String[] agrs) {
		List a = new LinkedList();
		a.add(new Cat("Cat"));
		a.add(new Cat("Tom"));
		a.add(new Cat("Bob"));
		
		System.out.println(a);
		Collections.sort(a);
		System.out.println(a);
	}
}

class Cat implements Comparable {
	String name;
	
	Cat(String name) {
		this.name = name;
	}
	
	public int compareTo(Object o) {
		Cat cat = (Cat)o;
		
		return name.compareTo(cat.name);
	}
	
	public String toString() {
		return name.toString();
	}
}
