import java.util.*;

public class TestGeneric {
	public static void main(String[] args) {
		List<String> l = new ArrayList<String>();
		l.add("大水猫");
		l.add("大水狗");
		
		for (int i=0; i<l.size(); ++i) {
			System.out.println(l.get(i));
		}
		
		Map<String,Integer> m = new HashMap<String,Integer>();
		m.put("m1", 88);
		m.put("m3", 99);
		
		if (m.containsKey("m3")) {
			System.out.println(m.get("m3"));
		}
		
		Collection<String> c = new HashSet<String>();
		c.add("大水猫一号");
		c.add("大水猫二号");
		c.add("大水猫二号");
		
		System.out.println(c.size());
		for (Iterator<String> i=c.iterator(); i.hasNext(); ) {
			String s = i.next();
			System.out.println(s);
		}
		
		List<String> cat = new ArrayList<String>();
		cat.add("科比");
		cat.add("詹姆斯");
		cat.add("帕克");
		System.out.println(cat);
		
		Collections.sort(cat);
		System.out.println(cat);
	}
}

class Cat implements Comparable<Cat> {
	String name;
	
	public Cat(String name) {
		this.name = name;
	}
	
	public int compareTo(Cat o) {
		return name.compareTo(o.name);
	}
}

