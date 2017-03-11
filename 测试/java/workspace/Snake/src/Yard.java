import java.awt.Color;
import java.awt.Font;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Yard extends Frame {
	public static final int ROWS = 20;
	public static final int COLUMNS = 20;
	public static final int BLOCK_SIZE = 20;
	
	Snake snake = new Snake(this, "大水猫");
	Egg egg = new Egg();
	PaintThread paintThread = new PaintThread();
	
	public static void main(String[] args) {
		new Yard().launch("Greedy Snack");
	}

	/* 启动类 */
	public void launch(String title) {
		this.setTitle(title);
		this.setBounds(100, 100, COLUMNS*BLOCK_SIZE, ROWS*BLOCK_SIZE);
		this.setVisible(true);

		/* 内部类 */
		this.addWindowListener(new WindowAdapter() {

			@Override
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
			
		});
		
		this.addKeyListener(new KeyMonitor());
		new Thread(paintThread).start();	
	}
	
	private int score = 0;
	public int getScore() {
		return score;
	}

	public void setScore(int score) {
		this.score = score;
	}

	private Boolean gameOver = false;
	public void stop() {
		gameOver = true;
	}

	@Override
	public void paint(Graphics g) {
		Color c = g.getColor();
		
		g.setColor(Color.GRAY);
		g.fillRect(0, 0, COLUMNS*BLOCK_SIZE, ROWS*BLOCK_SIZE);
		g.setColor(Color.WHITE);		
		//画横线
		for (int i=1; i<ROWS; ++i) {
			g.drawLine(0, BLOCK_SIZE*i, COLUMNS*BLOCK_SIZE, BLOCK_SIZE*i);
		}
		//画竖线
		for (int i=1; i<COLUMNS; ++i) {
			g.drawLine(BLOCK_SIZE*i, 0, BLOCK_SIZE*i, ROWS*BLOCK_SIZE);
		}
		
		g.setFont(new Font("宋体", Font.BOLD, 24));
		g.setColor(Color.YELLOW);
		g.drawString("Store: " + score, 50, 80);
		if (gameOver == true) {
			g.setFont(new Font("宋体", Font.BOLD, 50));
			g.setColor(Color.BLUE);
			g.drawString("Game Over!", 80, 150);
			paintThread.setPause(true);
		}
		
		g.setColor(c);
		
		snake.eat(egg);
		snake.draw(g);
		egg.draw(g);
	}

	class KeyMonitor extends KeyAdapter {
		public void keyPressed(KeyEvent e) {
			snake.keyPress(e);
		}
	}
	
	class PaintThread implements Runnable {
		private Boolean pause = false;
		public Boolean getPause() {
			return pause;
		}
		public void setPause(Boolean pause) {
			this.pause = pause;
		}
		@Override
		public void run() {	
			while(true) {
				if (pause == true) {
					continue;
				} else {
					repaint();
				}
				
				try {
					Thread.sleep(200);
				} catch(InterruptedException e) {
					e.printStackTrace();
				}
			}
		}	
	}
}



