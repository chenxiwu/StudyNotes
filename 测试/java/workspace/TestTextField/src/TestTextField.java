import java.awt.*;
import java.awt.event.*;

public class TestTextField {
	public static void main(String[] args) {
		new TFFrame();
	}
}

class TFFrame extends Frame {
	TFFrame() {
		TextField tf = new TextField();
		tf.addActionListener(new Monitor());
		super.add(tf);
		super.pack();
		super.setVisible(true);
	}
}

class Monitor implements ActionListener {
	public void actionPerformed(ActionEvent e) {
		TextField tf = (TextField)e.getSource();
		System.out.println(tf.getText());
		tf.setText("");
	}
}
