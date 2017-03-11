import java.io.*;

public class TestPrintStream1 {
	public static void main(String[] args) {
		String s = args[0];
		if (s != null) {
			print(s, System.out);
		}
	}
	
	public static void print(String path, PrintStream p) {
		try {
			BufferedReader br = new BufferedReader( new FileReader(path) );
			String s;
			
			while ((s = br.readLine()) != null) {
				p.println(s);
			}
			
			br.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
