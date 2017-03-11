import java.io.*; 

public class TestBufferWrite {
	public static void main(String[] args) {
		BufferedWriter bw = null;
		BufferedReader br = null;
		
		try {
			bw = new BufferedWriter( new FileWriter("C:/Users/SY/Desktop/java/workspace/"
					+ "TestBufferWrite/src/FileWriter.txt") );
			
			for (int i=0; i<100; ++i) {
				bw.write( String.valueOf( Math.random() ) );
				bw.newLine();
			}
			bw.flush();
			
			br = new BufferedReader( new FileReader("C:/Users/SY/Desktop/java/workspace/"
					+ "TestBufferWrite/src/FileWriter.txt") );
			
			String s = null;
			while ( (s = br.readLine()) != null ) {
				System.out.println(s);
			}
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				bw.close();
				br.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}
