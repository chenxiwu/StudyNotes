import java.io.*;

public class TestInputStreamRead {
	public static void main(String[] args) {
		InputStreamReader isr = null;
		BufferedReader br = null;
		
		try {
			isr = new InputStreamReader(System.in);
			br = new BufferedReader(isr);
			String s = br.readLine();
			
			while (s != null) {
				System.out.println(s);
				if (s.equalsIgnoreCase("exit")) {
					break;
				}
				s = br.readLine();
			}
		} catch(IOException e) {
			e.printStackTrace();
		} finally {
			try {
				isr.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		
		System.out.println("bye!");
	}
}
