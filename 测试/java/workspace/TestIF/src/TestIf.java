public class TestIf {
	public static void main(String[] args) {
		double a = Math.random();	
		System.out.println(a);
		
		int b = (int)(a * 10);
		System.out.println(b);
		
		if (b >= 5) {
			System.out.println("����");
		} else {
			System.out.println("С��");
		}
	}
}
