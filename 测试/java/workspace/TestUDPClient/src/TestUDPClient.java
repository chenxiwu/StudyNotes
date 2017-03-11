import java.io.*;
import java.net.*;

/*
public class TestUDPClient {
	public static void main(String[] args) {
		byte[] buff = new byte[1024];
		String str = "Hello World!";
		buff = str.getBytes();
		DatagramPacket dp = new DatagramPacket(buff, str.length(),
								new InetSocketAddress("127.0.0.1", 9999));
		try {
			DatagramSocket socket = new DatagramSocket(8888);
			socket.send(dp);
			socket.close();
		} catch(SocketException e) {
			e.printStackTrace();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
*/

public class TestUDPClient {
	public static void main(String[] args) {	
		try {
			DatagramSocket socket = new DatagramSocket(8888);
			
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			DataOutputStream dos = new DataOutputStream(baos);
			dos.writeLong(8989L);
			byte[] buff = baos.toByteArray();
			
			DatagramPacket dp = new DatagramPacket(buff, buff.length,
					new InetSocketAddress("127.0.0.1", 9999));
			socket.send(dp);
			
			dos.close();
			socket.close();
			System.out.println("[¿Í»§¶Ë] ¹Ø±Õ...");
		} catch(Exception e) {
			e.printStackTrace();
		}
		
	}
}