import java.awt.*; 

/*
public class TestFrame {
	public static void main(String[] args) {
		Frame frame = new Frame("Hello World");
		frame.setBackground(Color.blue);
		frame.setSize(500,300);
		frame.setLocation(100,100);
		frame.setVisible(true);
	}
}
*/

public class TestFrame {
	public static void main(String[] args) {
		MyFrame frame1 = new MyFrame(100,100,400,200,Color.RED);
		MyFrame frame2 = new MyFrame(500,100,400,200,Color.DARK_GRAY);
		MyFrame frame3 = new MyFrame(100,300,400,200,Color.CYAN);
		MyFrame frame4 = new MyFrame(500,300,400,200,Color.BLUE);
	}
}

class MyFrame extends Frame {
	private static int id = 0;
	
	MyFrame(int x, int y, int lenth, int width, Color color) {
		super("MyFrame " + (++id));
		
		setBackground(color);
		setBounds(x, y, lenth, width);
		setLayout(null);
		setVisible(true);
	}
}

