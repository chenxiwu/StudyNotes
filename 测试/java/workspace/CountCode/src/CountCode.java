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
		
		/* 统计数据 */
		System.out.println("总行数：" + lines);
		System.out.println("空白行：" + blankRows);
		System.out.println("代码：" + code);
		System.out.println("注释：" + note);
	}
	
	private static void iterator(File[] list) {
		for (File f:list) {
			if (f.isDirectory() == true) {
				iterator(f.listFiles());
			} else if (f.getName().matches(".*\\.java$")) {
				//使用正则表达式匹配
				parsePattern(f);
			//统计.c .h文件代码	
			} else if (f.getName().matches(".*\\.[ch]$")) {
				parsePattern(f);
			}
		}
	}
	
	/**
	 * 分析文件
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
	 * 分析文件
	 * @param s
	 */
	private static void parsePattern(File f) {		
		BufferedReader br = null;
		
		try {
			br = new BufferedReader(new FileReader(f));
			
			String s = null;
			boolean noteStart = false;
			while ((s = br.readLine()) != null) {
				/* 移除空白字符*/
				s = s.trim();
				//总行数增加
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
