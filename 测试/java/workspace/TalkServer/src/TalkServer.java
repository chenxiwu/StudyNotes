import java.io.*;
import java.net.*;

public class TalkServer {
	public static void main(String[] args) {
		try {
			ServerSocket socket = new ServerSocket(8888);
			
			while (true) {
				System.out.println("========== [服务器] ==========");
				System.out.println("准备接收...");
				
				Socket server = socket.accept();
				BufferedReader netInput = new BufferedReader( new InputStreamReader( server.getInputStream() ) );
				BufferedReader cmdInput = new BufferedReader( new InputStreamReader(System.in) );
				PrintWriter cmdOutput = new PrintWriter( new OutputStreamWriter( server.getOutputStream() ) );
				
				String str = null;
				while (true) {
					str = netInput.readLine();
					if (str == null) {
						break;
					}
					System.out.println("[Server] " + str);

					str = cmdInput.readLine();
					cmdOutput.println(str);
					cmdOutput.flush();
				}
				
				netInput.close();
				cmdOutput.close();
				
				System.out.println("[Server] Bye!");
			}
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
