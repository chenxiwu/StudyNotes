import java.io.*;
import java.net.*;

public class TalkClient {
	public static void main(String[] args) {
		try {
			while (true) {
				Socket client = new Socket("127.0.0.1", 8888);
				System.out.println("========== [øÕªß∂À] ==========");
				System.out.println("«Î ‰»Î...");
				
				BufferedReader netInput = new BufferedReader( new InputStreamReader( client.getInputStream() ) );
				BufferedReader cmdInput = new BufferedReader( new InputStreamReader(System.in) );
				PrintWriter cmdOutput = new PrintWriter( new OutputStreamWriter( client.getOutputStream() ) );
				
				String str = null;
				while (true) {
					str = cmdInput.readLine();
					if (str.equalsIgnoreCase("bye")) {
						break;
					}
					cmdOutput.println(str);
					cmdOutput.flush();
					
					str = netInput.readLine();
					System.out.println("[Client] " + str);
				}
				
				netInput.close();
				cmdOutput.close();
				client.close();
				
				System.out.println("[Client] Bye!");
			}
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
