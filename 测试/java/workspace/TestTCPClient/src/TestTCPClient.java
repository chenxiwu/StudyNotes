import java.io.*;
import java.net.*;

/*
public class TestTCPClient {
	public static void main(String[] args) {
		System.out.println("[客户端] 开始建立Socket...");
		try {
			Socket socket = new Socket("127.0.0.1", 8888);
			
			DataOutputStream dos = new DataOutputStream( socket.getOutputStream() );
			dos.writeUTF("Hello Server!");
			dos.flush();
			dos.close();
			socket.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
*/

public class TestTCPClient {
	public static void main(String[] args) {
		try {
			Socket client = new Socket("127.0.0.1", 8888);
			
			DataInputStream dis = new DataInputStream( client.getInputStream() );
			System.out.println( dis.readUTF() );
			
			dis.close();
			client.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}