import java.awt.*;
import java.awt.event.*;

public class TestKeyEvent {
	public static void main(String[] args) {
		new MyKey("Key");
	}
}

class MyKey extends Frame {
	Button button = null;
	
	public MyKey(String title) {
		super(title);
		
		this.setLayout(null);
		this.setBackground(Color.BLUE);
		this.setSize(500, 400);
		
		this.addKeyListener(new KeyMonitor());
		this.addWindowListener(new CloseMonitor());
		this.setVisible(true);
	}
	
	class KeyMonitor extends KeyAdapter {
		public void	keyPressed(KeyEvent e) {
			System.out.println("¼üÖµ = " + e.getKeyCode());
			if (e.getKeyCode() == KeyEvent.VK_UP) {
				System.out.println("UP");
			}
		}
	}
	
	class CloseMonitor extends WindowAdapter {
		public void	windowClosing(WindowEvent e) {
			System.exit(0);
		}
	}	
}


