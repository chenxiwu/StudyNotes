import java.awt.*;
import java.awt.event.*;

public class TestWindowsClose {
	public static void main(String[] args) {
		new CloseWindows("Close...");
	}
}

class CloseWindows extends Frame {
	public CloseWindows(String title) {
		super(title);
		this.setBounds(100, 100, 500, 500);
		this.setVisible(true);
		this.addWindowListener(new Monitor());
	}

	class Monitor extends WindowAdapter {
		public void	windowClosing(WindowEvent e) {
			CloseWindows c = (CloseWindows)e.getSource();
			System.out.println("我被关闭了！");
			c.setVisible(false);
			System.exit(-1);
		}
	}
}

