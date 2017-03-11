
public class TestSwitch {
	public static void main(String[] args) {
		/*
		double a = Math.random();
		int b = (int)(3 * a);
		
		System.out.println(a);
		
		switch (b) {
		case 0:
			System.out.println("值为0");
			break;
		case 1:
			System.out.println("值为1");
			break;
		default:
			System.out.println("其他");
			break;
		}
		*/
		
		String str = "张三";
		
		
		switch (str) {
		case "张三":
			System.out.println("我是"+str);
			break;
		default:
			System.out.println("我是谁？");
			break;
		}
	}
}
