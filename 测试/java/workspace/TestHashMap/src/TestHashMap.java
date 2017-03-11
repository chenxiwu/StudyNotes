import java.util.*;

public class TestHashMap {
	public static void main(String[] args) {
		Map m1 = new HashMap();
		//m1.put("m1", new Integer(1));
		//���Խ���������ת��Ϊ����
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
		
		//����ǿ������ת������������ȡ�������Ѿ�ʧȥ����������
		if (m1.containsKey("m2")) {
			//System.out.println( ((Integer)m1.get("m2")).intValue() );
			//JDK�Զ�������ת��Ϊ��������
			System.out.println(m1.get("m2"));
		}
		
		Map m3 = new HashMap(m1);
		System.out.println(m3);
		
		m3.putAll(m2);
		System.out.println(m3);
	}
}
