import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class CountCode {
	private static int lines = 0;
	private static int code = 0;
	private static int blankRows = 0;
	private static int note = 0;
	
	public static void main(String[] args) {
		//File file = new File("C:\\Users\\SY\\Desktop\\java\\workspace\\CountCode\\src");
		File file = new File("C:\\Users\\SY\\Desktop\\SWE_HMI0031_BRIDGE-master");
		File[] list = file.listFiles();
		
		iterator(list);
		
		/* ͳ������ */
		System.out.println("��������" + lines);
		System.out.println("�հ��У�" + blankRows);
		System.out.println("���룺" + code);
		System.out.println("ע�ͣ�" + note);
	}
	
	private static void iterator(File[] list) {
		for (File f:list) {
			if (f.isDirectory() == true) {
				iterator(f.listFiles());
			} else if (f.getName().matches(".*\\.java$")) {
				//ʹ��������ʽƥ��
				parsePattern(f);
			//ͳ��.c .h�ļ�����	
			} else if (f.getName().matches(".*\\.[ch]$")) {
				parsePattern(f);
			}
		}
	}
	
	/**
	 * �����ļ�
	 * @param s
	 */
	private static void parse(File f) {		
		BufferedReader br = null;
		
		try {
			br = new BufferedReader(new FileReader(f));
			
			String s = null;
			boolean noteStart = false;
			while ((s = br.readLine()) != null) {
				s = s.trim();
				lines++;
				if (s.matches("^[\\s&&[^\\n]]*") == true) {
					blankRows++;
				} else if (s.startsWith("//") == true) {
					note++;
				} else if ((s.startsWith("/*") == true) && (s.endsWith("*/") == true)) {
					note++;
				} else if ((s.startsWith("/*") == true) && (s.endsWith("*/") == false)) {
					noteStart = true;
					note++;
				} else if (noteStart == true) {
					note++;
					if (s.endsWith("*/") == true) {
						noteStart = false;
					}
				} else {
					code++;
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null) {
					br.close();
					br = null;
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	/**
	 * �����ļ�
	 * @param s
	 */
	private static void parsePattern(File f) {		
		BufferedReader br = null;
		
		try {
			br = new BufferedReader(new FileReader(f));
			
			String s = null;
			boolean noteStart = false;
			while ((s = br.readLine()) != null) {
				/* �Ƴ��հ��ַ�*/
				s = s.trim();
				//����������
				lines++;
				if (s.matches("^[\\s&&[^\\n]]*") == true) {
					blankRows++;
				} else if (s.matches("^//.*") == true) {
					note++;
				} else if (s.matches("^/\\*.*\\*/$") == true) {
					note++;
				} else if (s.matches("^/\\*(?!.*\\*/).*") == true) {
					noteStart = true;
					note++;
				} else if (noteStart == true) {
					note++;
					if ((s.matches(".*\\*/$")) == true) {
						noteStart = false;
					}
				} else {
					code++;
				}
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null) {
					br.close();
					br = null;
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
