
public class TestString {
	public static void main(String[] args) {
		/*
		String a = new String("泰迪");
		String b = new String("泰迪");
		
		//System.out.println(a == b);
		System.out.println(a.equals(b));
		*/
		
		/*
		//统计一个字符串中，大写英文、小写英文、非英文字符个数
		String str = "ABC1 &%2ahdc";
		TestString string = new TestString();
		
		int capNums = string.getStringCapitalLetterNums(str);
		System.out.println("大写字符：" + capNums);
		
		int smallNums = string.getStringSmallLetterNums(str);
		System.out.println("小写字符：" + smallNums);
		
		int notLetterNums = string.getStringNotLetterNums(str);
		System.out.println("非字符：" + notLetterNums);
		*/
		
		//在字符串中查找指定字符串出现的次数
		String str = "Hello World Hello World";
		TestString string = new TestString();
		
		String target = "H";
		int nums = string.getStringStrNums(str, target);
		System.out.println("字符串中含有" + target + "的个数：" + nums);
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
