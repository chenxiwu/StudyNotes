import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class EmailSpider {
	public static void main(String[] args) {
	
		BufferedReader br = null;
		try {
			br = new BufferedReader(
					new FileReader("C:\\Users\\SY\\Desktop\\java\\workspace\\EmailSpider\\src\\要的留邮箱!_dj吧_百度贴吧.html"));
			
			String s = null;
			while ((s = br.readLine()) != null) {
				findEmail(s);
				
			}			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				br.close();
			} catch(IOException e) {
				e.printStackTrace();
			}
		}	
	}
	
	private static boolean findEmail(String s) {
		boolean isFind = false;
		Pattern p = Pattern.compile("[\\w[-.]]+@[\\w[-]]+\\.[\\w]+");
		Matcher m = p.matcher(s);
		while (m.find()) {
			System.out.println(m.group());
			isFind = true;
		}
		
		return isFind;
	}
}
