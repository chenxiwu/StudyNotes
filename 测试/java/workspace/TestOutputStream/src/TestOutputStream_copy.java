import java.io.*;

public class TestOutputStream {
	public static void main(String[] args) {
		FileInputStream in = null;
		FileOutputStream out = null;
		
		try {
			in = new FileInputStream("C:/Users/SY/Desktop/java/workspace/"
									  + "TestOutputStream/src/TestOutputStream.java");
			out = new FileOutputStream("C:/Users/SY/Desktop/java/workspace/"
									  + "TestOutputStream/src/TestOutputStream_copy.java");
			
			int value;
			while ((value=in.read())!=-1) {
				out.write(value);
			}
		} catch(FileNotFoundException e) {
			e.printStackTrace();
		} catch(IOException e) {
			e.printStackTrace();
		} finally {
			try {
				//�رղ�������Ҳ�׳��쳣�����봦��
				in.close();
				out.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		System.out.println("�ļ������ɹ���");
	}
}
