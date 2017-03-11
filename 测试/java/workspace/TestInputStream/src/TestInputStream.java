import java.io.*;

public class TestInputStream {
	public static void main(String[] args) {
		FileInputStream in = null;
		int fileSize = 0;
		
		try {
			in = new FileInputStream("C:/Users/SY/Desktop/java/workspace/"
									  + "TestInputStream/src/TestInputStream.java");
			int value;
			while ((value = in.read()) != -1) {
				fileSize++;
				System.out.print((char)value);
			}
			
			in.close();
			
			/* 中文不能正常显示。因为中文一个字符包含2个字节 */
			System.out.println("文件长度：" + fileSize);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
