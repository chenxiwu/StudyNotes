import java.io.*;

public class TestFile {
	public static void main(String[] args) {
		//�ڵ�ǰ·���´����ļ�(��)
		/*
		String separator = File.separator;
		String pathName = "��ˮè" + separator + "Сˮ��";
		String fileName = "���ܿ�����.txt";
		
		File file = new File(pathName, fileName);
		if (file.exists() == true) {
			System.out.println("·����" + file.getAbsolutePath());
			System.out.println("��С��" + file.length());
		} else {
			file.getParentFile().mkdirs();
			try {
				file.createNewFile();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		*/
		//����״�ṹ�г�ָ��·���µ��ļ����У�
		TestFile a = new TestFile();
		
		String listPath = "C:/Users/SY/Desktop/java/workspace/TestFile/��ˮè1";
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
