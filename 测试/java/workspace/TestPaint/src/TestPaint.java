import java.awt.*;

public class TestPaint extends Frame {
	public static void main(String[] args) {
		new TestPaint().launchFrame();
	}
	
	public void launchFrame() {
		this.setBounds(100, 100, 500, 400);
		this.setVisible(true);
	}
	
	//自动调用该方法
	public void	paint(Graphics g) {
		Color c = g.getColor();
		
		g.setColor(Color.RED);
		g.fillRect(50, 50, 100, 80);
		g.setColor(Color.BLUE);
		g.fillOval(200, 200, 80, 40);
		
		g.setColor(c);
	}
}

