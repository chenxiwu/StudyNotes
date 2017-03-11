import java.awt.*;
import java.awt.event.*;

public class TestTFMath {
	public static void main(String[] args) {
		new MyTFMath().launchFrame();
	}
}

class MyTFMath extends Frame {
	private TextField num1,num2,num3;
	public void launchFrame() {
		num1 = new TextField(20);
		num2 = new TextField(20);
		num3 = new TextField(20);
		Label label = new Label("+");
		Button equal = new Button("=");
		equal.addActionListener(new Monitor());
		
		this.setLayout(new FlowLayout());
		this.add(num1);
		this.add(label);
		this.add(num2);
		this.add(equal);
		this.add(num3);
		this.pack();
		this.setVisible(true);
	}
	
	//使用内部类
	class Monitor implements ActionListener {	
		public void actionPerformed(ActionEvent e) {
			int n1 = Integer.parseInt(num1.getText());
			int n2 = Integer.parseInt(num2.getText());
			num3.setText(Integer.toString(n1+n2));
		}
	}
}

/*
class Monitor implements ActionListener {
	MyTFMath tf = null;
	public Monitor(MyTFMath tf) {
		this.tf = tf;
	}
	
	public void actionPerformed(ActionEvent e) {
		int num1 = Integer.parseInt(tf.num1.getText());
		int num2 = Integer.parseInt(tf.num2.getText());
		tf.num3.setText(Integer.toString(num1+num2));
	}
}  
*/

