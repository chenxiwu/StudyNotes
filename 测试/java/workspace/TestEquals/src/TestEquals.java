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
		 * instanceof 用来判断左边对象是否等于右边对象
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
		Cat cat1 = new Cat("大水猫");
		Cat cat2 = new Cat("大水猫");
		
		/* 堆地址不一致，肯定不相等 */
		//System.out.println(cat1 == cat2);
		System.out.println(cat1.equals(cat2));
		
	}
}
