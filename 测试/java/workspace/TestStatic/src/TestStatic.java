class Static {
	static int id;
	String name;
	
	Static(String name) {
		this.name = name;
		id += 1;
	}
}

public class TestStatic {
	public static void main(String[] args) {
		Static.id = 100;
		System.out.println(Static.id);
		
		Static a = new Static("a");
		Static b = new Static("b");
		
		System.out.println(Static.id);
	}
}
