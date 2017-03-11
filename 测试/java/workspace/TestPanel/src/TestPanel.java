import java.awt.*;

/*
public class TestPanel {
	public static void main(String[] args) {
		Frame f = new Frame("Frame");
		f.setBounds(100, 100, 500, 300);
		f.setLayout(null);
		f.setBackground(Color.BLUE);
		
		Panel p = new Panel();
		p.setBounds(50, 50, 200, 100);
		p.setBackground(Color.BLACK);
		
		f.add(p);
		f.setVisible(true);
	}
}
*/

public class TestPanel {
	public static void main(String[] args) {
		MyFrame f = new MyFrame("Multi Panel", 200,200,800,400);
	}
}

class MyFrame extends Frame {
	private Panel p1, p2, p3, p4;
	
	MyFrame(String title, int x, int y, int lenth, int width) {
		super(title);
		
		setBackground(Color.BLUE);
		setBounds(x,y,lenth,width);
		setLayout(null);
		
		p1 = new Panel(null);
		p1.setBackground(Color.CYAN);
		p1.setBounds(0,0,lenth/2,width/2);
		add(p1);
		
		p2 = new Panel(null);
		p2.setBackground(Color.RED);
		p2.setBounds(lenth/2,0,lenth/2,width/2);
		add(p2);
		
		p3 = new Panel(null);
		p3.setBackground(Color.GREEN);
		p3.setBounds(0,width/2,lenth/2,width/2);
		add(p3);
		
		p4 = new Panel(null);
		p4.setBackground(Color.DARK_GRAY);
		p4.setBounds(lenth/2,width/2,lenth/2,width/2);
		add(p4);
		
		setVisible(true);
	}
	
}
