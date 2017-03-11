import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class TestMouseAdapter {
	public static void main(String[] args) {
		new MyMouse("Mouse Paint");
	}
}

class MyMouse extends Frame {
	ArrayList<Point> mouseInfo = new ArrayList<Point>();
	
	public MyMouse(String title) {
		super(title);
		
		this.setBounds(100, 100, 800, 500);
		this.setVisible(true);
		this.setLayout(null);
		this.addMouseListener(new Monitor());
	}
	
	public void paint(Graphics g) {
		Color c = g.getColor();
		g.setColor(Color.RED);
		Iterator<Point> i = mouseInfo.iterator();
		while(i.hasNext()) {
			Point p = i.next();
			g.fillOval(p.x, p.y, 20, 20);
		}	
		g.setColor(c);
	}
	
	public void addPoint(Point p) {
		mouseInfo.add(p);
	}
}

class Monitor extends MouseAdapter {
	public void mousePressed(MouseEvent e) {
		MyMouse mm = (MyMouse)e.getSource();
		mm.addPoint(new Point(e.getX(), e.getY()));
		mm.repaint();
	}
}
