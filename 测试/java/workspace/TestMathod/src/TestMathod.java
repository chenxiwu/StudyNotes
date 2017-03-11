
public class TestMathod {
	public static void main (String[] args) {
		startTask();
		
		int a = 1;
		int b = 2;
		int c = add(a,b);
		output(c);
		
		endTask();
	}
	
	public static void startTask() {
		System.out.println("Start...");
	}
	
	public static int add(int a, int b) {
		return a + b;
	}
	
	public static void output(int a) {
		System.out.println(a);
	}
	
	public static void endTask() {
		System.out.println("Bye...");
	}
}
