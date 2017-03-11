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
			
			/* ���Ĳ���������ʾ����Ϊ����һ���ַ�����2���ֽ� */
			System.out.println("�ļ����ȣ�" + fileSize);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
