import java.awt.*;

public class TestCenterPanel {
	public static void main(String[] args) {
		CenterPanel cp = new CenterPanel(100, 100, 500, 400, Color.BLUE,
							Color.YELLOW, "FrameWithPanel");
		
	}
}

class CenterPanel extends Frame {
	CenterPanel(int x, int y, int width, int height, 
				Color backColor, Color panelColor, String title) {
		//首先实现父类的构造方法
		super(title);
		
		this.setBackground(backColor);
		this.setBounds(x, y, width, height);
		this.setLayout(null);
		
		Panel p = new Panel(null);
		p.setBackground(panelColor);
		p.setBounds((int)(0.25*width), (int)(0.25*height), (int)(0.5*width), (int)(0.5*height));
		
		this.add(p);
		this.setVisible(true);
	}
}
