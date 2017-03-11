import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.event.KeyEvent;

public class Snake {
	private String name = null;
	private Node head = null;
	private Node tail = null;
	private Yard yard;
	
	public Snake(Yard yard, String name) {
		this.name = name;
		this.yard = yard;
		
		//创建头结点
		Node point = new Node(2, 0, Dir.RIGHT);
		head = point;
		tail = point;
	
		head.prev = tail;
		head.next = tail;
		tail.prev = head;
		tail.next = head;
	}
	
	public void addToTail() {
		Node node = null;
		switch (tail.dir) {
		case LEFT:
			node = new Node(tail.rows, tail.columns+1, tail.dir);
			break;
		case UP:
			node = new Node(tail.rows+1, tail.columns, tail.dir);
			break;
		case RIGHT:
			node = new Node(tail.rows, tail.columns-1, tail.dir);
			break;
		case DOWN:
			node = new Node(tail.rows-1, tail.columns, tail.dir);
			break;
		}
		
		tail.next = node;
		node.prev = tail;
		node.next = head;
		head.prev = node;
		
		tail = node;
	}
	
	public void addToHead() {
		Node node = null;
		switch (head.dir) {
		case LEFT:
			node = new Node(head.rows, head.columns-1, head.dir);
			break;
		case UP:
			node = new Node(head.rows-1, head.columns, head.dir);
			break;
		case RIGHT:
			node = new Node(head.rows, head.columns+1, head.dir);
			break;
		case DOWN:
			node = new Node(head.rows+1, head.columns, head.dir);
			break;
		}
		
		node.next = head;
		head.prev = node;
		node.prev = tail;
		tail.next = node;
				
		head = node;
	}
	
	public Boolean isCrashWall() {
		if ((this.getHeadRows() <= 1) || (this.getHeadRows() > Yard.ROWS-1) ||
			(this.getHeadColumns()<0) || (this.getHeadColumns() > Yard.COLUMNS-1)) {
			return true;
		} else {
			return false;
		}
	}
	
	public Boolean isCrashMyself() {
		for (Node n = head.next; n != head; n = n.next) {
			if ((n.rows == head.rows) && (n.columns == head.columns)) {
				return true;
			}
		}
		
		return false;
	}
	
	public int getHeadRows() {
		return head.rows;
	}
	
	public int getHeadColumns() {
		return head.columns;
	}
	
	public void deleteFromTail() {
		tail.prev.next = tail.next;
		tail.next.prev = tail.prev;
		tail = tail.prev;
	}
	
	public Boolean checkDead() {
		if (this.isCrashWall() == true) {
			return true;
		}
		if (this.isCrashMyself() == true) {
			return true;
		}
		
		return false;
	}
	
	public void move() {
		this.addToHead();
		this.deleteFromTail();
		if (this.checkDead() == true) {
			yard.stop();
		}
	}
	
	public void increase() {
		this.addToHead();
	}
	
	private Rectangle getRect() {
		return new Rectangle(this.head.rows*Yard.BLOCK_SIZE, this.head.columns*Yard.BLOCK_SIZE,
				Yard.BLOCK_SIZE, Yard.BLOCK_SIZE);
	}
	
	public void eat(Egg egg) {
		if (this.getRect().intersects(egg.getRect()) == true) {
			egg.generateNextEgg();
			this.increase();	
			yard.setScore(yard.getScore() + 5);
		} else {
			this.move();
		}
	}
	
	public void draw(Graphics g) {
		//头结点必须绘制
		head.draw(g);
		for (Node node=head.next; node!=head; node=node.next) {
			node.draw(g);
		}
	}
	
	public void keyPress(KeyEvent e) {
		if (e.getKeyCode() == KeyEvent.VK_UP) {
			if (this.head.dir != Dir.DOWN) {
				this.head.dir = Dir.UP;
			}
		} else if (e.getKeyCode() == KeyEvent.VK_DOWN) {
			if (this.head.dir != Dir.UP) {
				this.head.dir = Dir.DOWN;
			}
		} else if (e.getKeyCode() == KeyEvent.VK_LEFT) {
			if (this.head.dir != Dir.RIGHT) {
				this.head.dir = Dir.LEFT;
			}
		} else if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
			if (this.head.dir != Dir.LEFT) {
				this.head.dir = Dir.RIGHT;
			}
		}
	}

	private class Node {
		public int rows;
		public int columns;
		private Dir dir = Dir.LEFT;
		private Node prev = null;
		private Node next = null;
		
		public Node(int rows, int columns, Dir dir) {
			this.rows = rows;
			this.columns = columns;
			this.dir = dir;
		}
		
		public void draw(Graphics g) {
			Color c = g.getColor();
			g.setColor(Color.GREEN);
			g.fillRect(columns*Yard.BLOCK_SIZE, rows*Yard.BLOCK_SIZE, Yard.BLOCK_SIZE, Yard.BLOCK_SIZE);
			g.setColor(c);
		}
	} 
}
