import java.awt.*;

public class TestLayout {
	public static void main(String[] args) {
		Frame f = new Frame("TestLayout");
		f.setBackground(Color.BLUE);
		
		//总布局
		f.setLayout(new GridLayout(2,1));	
		
		//上半部分
		Panel p1 = new Panel(new BorderLayout());
		
		Panel p11 = new Panel(new GridLayout(2,1));
		p11.add(new Button("BUTTON1"));
		p11.add(new Button("BUTTON2"));
		p1.add(p11, BorderLayout.CENTER);
		
		p1.add(new Button("BUTTON3"), BorderLayout.WEST);
		p1.add(new Button("BUTTON4"), BorderLayout.EAST);
		
		f.add(p1);
		
		//下半部分
		Panel p2 = new Panel(new BorderLayout());
		
		Panel p21 = new Panel(new GridLayout(2,2));	
		int serial = 5;
		for (int i=0; i<4; ++i) {
			p21.add(new Button("BUTTON"+serial));
			serial++;
		}
		p2.add(p21, BorderLayout.CENTER);
		
		p2.add(new Button("BUTTON9"), BorderLayout.WEST);
		p2.add(new Button("BUTTON10"), BorderLayout.EAST);
		
		f.add(p2);
		
		f.pack();
		f.setVisible(true);
	}
}
