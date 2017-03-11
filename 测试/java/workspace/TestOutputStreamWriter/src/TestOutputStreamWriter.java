import java.io.*;

public class TestOutputStreamWriter {
	public static void main(String[] args) {
		OutputStreamWriter osw = null;
		InputStreamReader isr = null;
		
		try {
			osw = new OutputStreamWriter( new FileOutputStream("C:/Users/SY/Desktop/java/workspace/"
											+ "TestOutputStreamWriter/src/OutputStreamWriter.txt") );
			osw.write("abcdefg1234567");
			osw.close();
			
			osw = new OutputStreamWriter( new FileOutputStream("C:/Users/SY/Desktop/java/workspace/"
					+ "TestOutputStreamWriter/src/OutputStreamWriter.txt", true) );
			osw.write("8888888");
			osw.close();
		} catch(IOException e) {
			e.printStackTrace();
		} finally {
			try {
				osw.close();
			} catch(Exception e) {
				e.printStackTrace();
			}
		}
		
		System.out.println("–¥»ÎÕÍ≥…£°");
	}
}
