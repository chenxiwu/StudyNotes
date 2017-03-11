import java.io.*;
import java.net.*;

/*
public class TestTCPServer {
	public static void main(String[] args) {
		System.out.println("[服务器] 开始监听端口...！");
		try {
			ServerSocket server = new ServerSocket(8888);
			
			while (true) {
				Socket socket = server.accept();
				
				DataInputStream dis = new DataInputStream( socket.getInputStream() );
				System.out.println( dis.readUTF() );
				dis.close();
				socket.close();
			}
			
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
*/

public class TestTCPServer {
	public static void main(String[] args) {
		
		try {
			ServerSocket server = new ServerSocket(8888);
			
			while (true) {
				Socket s = server.accept();
				
				DataOutputStream dos = new DataOutputStream( s.getOutputStream() );
				dos.writeUTF("Start " + s.getInetAddress() + " " + s.getPort() + " Bye!");
				
				dos.close();
				s.close();
			}
		} catch(IOException e) {
			e.printStackTrace();
		}
		
	}
}
