import java.io.*;

public class TestDataStream {
	public static void main(String[] args) {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		DataOutputStream dos = new DataOutputStream(baos);
		
		try {
			dos.writeDouble(Math.random());
			dos.writeBoolean(false);
			
			ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
			DataInputStream dis = new DataInputStream(bais);
			
			System.out.println(bais.available());
			System.out.println(dis.readDouble());
			System.out.println(dis.readBoolean());
			
			dos.close();
			dis.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
