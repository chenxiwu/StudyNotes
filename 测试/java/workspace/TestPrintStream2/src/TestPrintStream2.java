import java.io.*;
import java.util.*;

public class TestPrintStream2 {
	public static void main(String[] args) {
		BufferedReader br = null;
		br = new BufferedReader( new InputStreamReader(System.in) );
		String s = null;
		
		PrintWriter fos = null;
		System.out.println("«Î ‰»Î...");
		try {
			fos = new PrintWriter( new FileOutputStream("C:\\Users\\SY\\Desktop\\java\\workspace\\" + 
					"TestPrintStream2\\src\\test.txt", true) );
			
			while ( (s = br.readLine()) != null ) {
				if (s.equalsIgnoreCase("exit")) {
					break;
				}
				
				fos.println(s);
				fos.flush();
			}
			fos.println("==========" + new Date() + "==========");
			fos.flush();
			fos.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
