
public class TestEnum {
	public enum Color {red, blue, green};
	
	public static void main(String[] args) {
		Color c = Color.red;
		
		switch (c) {
		case red:
			System.out.println("ºìÉ«");
			break;
		case green:
			System.out.println("ÂÌÉ«");
			break;
		case blue:
			System.out.println("À¶É«");
			break;
		}
		
		System.out.println(c);
	}
}
