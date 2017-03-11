class Cat {
	String name;
	
	Cat(String name) {
		this.name = name;
	}
	
	public boolean	equals(Object obj) {
		if (obj == null) {
			return false;
		}
		
		/**
		 * instanceof �����ж���߶����Ƿ�����ұ߶���
		 */
		if (obj instanceof Cat) {
			Cat cat = (Cat)obj;
			if (this.name == cat.name) {
				return true;
			}
		}
		
		return false;
	}
}

public class TestEquals {
	public static void main(String[] args) {
		Cat cat1 = new Cat("��ˮè");
		Cat cat2 = new Cat("��ˮè");
		
		/* �ѵ�ַ��һ�£��϶������ */
		//System.out.println(cat1 == cat2);
		System.out.println(cat1.equals(cat2));
		
	}
}
