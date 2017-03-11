import java.io.FileInputStream;
import java.io.IOException;
import java.io.FileNotFoundException;

public class TestException {
	public static void main( String[] args ) {
		int[] array = {1,2,3};
		
		//System.out.println(array[1]);
		//System.out.println(array[3]);
		//System.out.println(array[1]/0);
		
		//捕获异常
		/*
		try {
			System.out.println(array[0]/0);
		} catch(ArithmeticException e) {
			//System.out.println("系统出错！");
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
			System.out.println("文件打开错误！");
		} catch(IOException e) {
			System.out.println("文件读取错误！");
		} finally {
			try {
				input.close();
			} catch(IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/* 自己抛出一个异常 */
	public void Function(int a) throws ArithmeticException {
		if (a == 0) {
			throw new ArithmeticException("参数不能为0！");
		}
	}
}
