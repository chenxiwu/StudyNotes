import java.net.*;
import java.io.*;

/*
public class TestUDPServer {
	public static void main(String[] args) {
		byte[] buff = new byte[1024];
		DatagramPacket dp = new DatagramPacket(buff, buff.length);
		try {
			DatagramSocket socket = new DatagramSocket(9999);
			
			System.out.println("[服务器] 准备就绪...");
			while (true) {
				socket.receive(dp);
				System.out.println( new String(buff, 0, dp.getLength()) );
			}
		} catch(SocketException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
*/

public class TestUDPServer {
	public static void main(String[] args) {
		System.out.println("[服务器] 已就绪...");
		
		byte[] buff = new byte[1024];
		DatagramPacket dp = new DatagramPacket(buff, buff.length);
		try {
			DatagramSocket socket = new DatagramSocket(9999);
			while (true) {
				socket.receive(dp);
				ByteArrayInputStream bais = new ByteArrayInputStream(buff);
				DataInputStream dis = new DataInputStream(bais);
				System.out.println(dis.readLong());
			}	
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
}