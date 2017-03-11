
public class TestString {
	public static void main(String[] args) {
		/*
		String a = new String("̩��");
		String b = new String("̩��");
		
		//System.out.println(a == b);
		System.out.println(a.equals(b));
		*/
		
		/*
		//ͳ��һ���ַ����У���дӢ�ġ�СдӢ�ġ���Ӣ���ַ�����
		String str = "ABC1 &%2ahdc";
		TestString string = new TestString();
		
		int capNums = string.getStringCapitalLetterNums(str);
		System.out.println("��д�ַ���" + capNums);
		
		int smallNums = string.getStringSmallLetterNums(str);
		System.out.println("Сд�ַ���" + smallNums);
		
		int notLetterNums = string.getStringNotLetterNums(str);
		System.out.println("���ַ���" + notLetterNums);
		*/
		
		//���ַ����в���ָ���ַ������ֵĴ���
		String str = "Hello World Hello World";
		TestString string = new TestString();
		
		String target = "H";
		int nums = string.getStringStrNums(str, target);
		System.out.println("�ַ����к���" + target + "�ĸ�����" + nums);
	}
	
	public int getStringStrNums(String source, String target) {
		int nums = 0;
		int index = 0;
		
		for (int i=0; i<source.length(); ++i)
		{
			index = source.indexOf(target, i);
			if (index >= i) {
				i = index;
				nums++;
			}
		}
		
		return nums;
	}
	
	public int getStringCapitalLetterNums(String str) {
		int nums = 0;
		
		for (int i=0; i<str.length(); ++i) {
			int ch = str.charAt(i);
			if ( (ch>='A') && (ch<='Z') ) {
				nums++;
			}
		}
		
		return nums;
	}
	
	public int getStringSmallLetterNums(String str) {
		int nums = 0;
		
		for (int i=0; i<str.length(); ++i) {
			int ch = str.charAt(i);
			if ( (ch>='a') && (ch<='z') ) {
				nums++;
			}
		}
		
		return nums;
	}
	
	public int getStringNotLetterNums(String str) {
		int nums = 0;
		
		for (int i=0; i<str.length(); ++i) {
			int ch = str.charAt(i);
			if ( (ch<'A') || (ch>'Z') && (ch<'a') || (ch>'z') ) {
				nums++;
			}
		}
		
		return nums;
	}
}
