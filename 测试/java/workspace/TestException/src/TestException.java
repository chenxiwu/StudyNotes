import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

public class TestException {
	public static void main( String[] args ) {
		int[] array = {1,2,3};
		
		//System.out.println(array[1]);
		//System.out.println(array[3]);
		//System.out.println(array[1]/0);
		
		//�����쳣
		/*
		try {
			System.out.println(array[0]/0);
		} catch(ArithmeticException e) {
			//System.out.println("ϵͳ����");
			e.printStackTrace();
		}
		*/
		
		//TestException e = new TestException();
		//e.Function(0);
		
		FileInputStream input = null;
		try {
			input = new FileInputStream("123.txt");
			int a = input.read();
		} catch(FileNotFoundException e) {
			System.out.println("�ļ��򿪴���");
		} catch(IOException e) {
			System.out.println("�ļ���ȡ����");
		} finally {
			try {
				input.close();
			} catch(IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/* �Լ��׳�һ���쳣 */
	public void Function(int a) throws ArithmeticException {
		if (a == 0) {
			throw new ArithmeticException("��������Ϊ0��");
		}
	}
}
