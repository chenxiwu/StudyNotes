import java.awt.*;
import java.awt.event.*;

/*
public class TestActionEvent {
	public static void main(String[] args) {
		Frame f = new Frame("Test Action Event");
		f.setLayout(new BorderLayout());
		
		Button b = new Button("Press ME");
		Monitor m = new Monitor();
		b.addActionListener(m);
		
		f.add(b, BorderLayout.CENTER);
		f.pack();
		f.setVisible(true);
	}
}

class Monitor implements ActionListener {
	public void actionPerformed(ActionEvent e) {
		System.out.println("啊，我被按下了！");
	}
}
*/

public class TestActionEvent {
	public static void main(String[] args) {
		Frame f = new Frame("Test Button");
		
		Monitor m = new Monitor();
		Button b1 = new Button("Run");
		b1.addActionListener(m);
		//b1.setActionCommand("我是按钮RUN");
		f.add(b1, BorderLayout.NORTH);
		
		Button b2 = new Button("Stop");
		b2.addActionListener(m);
		f.add(b2, BorderLayout.SOUTH);
		
		f.pack();
		f.setVisible(true);
	}
}

class Monitor implements ActionListener {
	public void actionPerformed(ActionEvent e) {
		System.out.println(e.getActionCommand() + "按钮被按下了");
	}
} 
