
public class TestEnum {
	public enum Color {red, blue, green};
	
	public static void main(String[] args) {
		Color c = Color.red;
		
		switch (c) {
		case red:
			System.out.println("��ɫ");
			break;
		case green:
			System.out.println("��ɫ");
			break;
		case blue:
			System.out.println("��ɫ");
			break;
		}
		
		System.out.println(c);
	}
}
