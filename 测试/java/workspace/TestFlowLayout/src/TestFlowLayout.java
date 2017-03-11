import java.awt.*;

public class TestFlowLayout {
	public static void main(String[] args) {
		Frame f = new Frame("FlowLayout");
		f.setBackground(Color.BLUE);
		f.setBounds(100, 100, 500, 400);
		f.setLayout(new FlowLayout(FlowLayout.LEFT));
		Button b1 = new Button("��ť1");
		Button b2 = new Button("��ť2");
		Button b3 = new Button("��ť3");
		f.add(b1);
		f.add(b2);
		f.add(b3);
		f.setVisible(true);
	}
}
