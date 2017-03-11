import java.io.*;

public class TestObjectIO {
	public static void main(String[] args) {
		T t = new T();
		
		try {
			FileOutputStream fos = new FileOutputStream("C:\\Users\\SY\\Desktop\\java\\workspace\\TestObjectIO\\src\\Test.txt");
			ObjectOutputStream oos = new ObjectOutputStream(fos);
			oos.writeObject(t);
			oos.close();
			
			FileInputStream fis = new FileInputStream("C:\\Users\\SY\\Desktop\\java\\workspace\\TestObjectIO\\src\\Test.txt");
			ObjectInputStream ois = new ObjectInputStream(fis);
			T tr = (T)ois.readObject();
			
			System.out.println(tr.a + " " + tr.b + " " + tr.c + " " + tr.d);
			ois.close();
		} catch(IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException c) {
			c.printStackTrace();
		}
		
	}
}

class T implements Serializable {
	int a = 9;
	double b = 3.455666;
	float c = 5.9f;
	
	//不参与序列化
	transient int d = 3;
}
