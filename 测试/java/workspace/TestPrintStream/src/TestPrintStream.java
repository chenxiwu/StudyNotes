import java.io.*;

public class TestPrintStream {
	public static void main(String[] args) {
		FileOutputStream fos = null;
		PrintStream ps = null;
		
		try {
			fos = new FileOutputStream("C:/Users/SY/Desktop/java/workspace/TestPrintStream/src/test.txt");
			ps = new PrintStream(fos);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		//完成输出重定向
		if (ps != null) {
			System.setOut(ps);
		}
		
		for (int i=0; i<10; ++i) {
			System.out.println(i);
		}
		
		System.out.println("Bye!");
	}
}
