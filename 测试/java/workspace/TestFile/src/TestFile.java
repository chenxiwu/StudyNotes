import java.io.*;

public class TestFile {
	public static void main(String[] args) {
		//在当前路径下创建文件(夹)
		/*
		String separator = File.separator;
		String pathName = "大水猫" + separator + "小水狗";
		String fileName = "跑跑卡丁车.txt";
		
		File file = new File(pathName, fileName);
		if (file.exists() == true) {
			System.out.println("路径：" + file.getAbsolutePath());
			System.out.println("大小：" + file.length());
		} else {
			file.getParentFile().mkdirs();
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		*/
		//以树状结构列出指定路径下的文件（夹）
		TestFile a = new TestFile();
		
		String listPath = "C:/Users/SY/Desktop/java/workspace/TestFile/大水猫1";
		File file = new File(listPath); 
		System.out.println(file.getName());
		a.ListFile(file, 1);
	}
	
	public void ListFile(File file, int level) {
		File[] child = file.listFiles();
		for (int i=0; i<child.length; ++i) {
			for (int j=0; j<level; ++j) {
				System.out.print("--");
			}
			System.out.println(child[i].getName());
			
			if (child[i].isDirectory() == true) {
				ListFile(child[i], level+1);
			}
		}
	}
}
