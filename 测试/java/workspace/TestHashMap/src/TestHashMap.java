import java.util.*;

public class TestHashMap {
	public static void main(String[] args) {
		Map m1 = new HashMap();
		//m1.put("m1", new Integer(1));
		//可以将基础类型转换为对象
		m1.put("m1", 1);
		m1.put("m2", new Integer(8));
		
		Map m2 = new HashMap();
		m2.put("z1", new Float(1.23));
		m2.put("z2", new Float(2.34));
		m2.put("z3", new Float(3.45));
		
		System.out.println(m1.size());
		System.out.println(m2.size());
		
		System.out.println(m1.containsKey("m2"));
		System.out.println(m2.containsValue(new Float(2.34)));
		
		//必须强制类型转换，从容器中取出来后已经失去本来的类型
		if (m1.containsKey("m2")) {
			//System.out.println( ((Integer)m1.get("m2")).intValue() );
			//JDK自动将对象转换为基础类型
			System.out.println(m1.get("m2"));
		}
		
		Map m3 = new HashMap(m1);
		System.out.println(m3);
		
		m3.putAll(m2);
		System.out.println(m3);
	}
}
