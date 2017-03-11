import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.util.Random;

public class Egg {
	public int getRows() {
		return rows;
	}

	public void setRows(int rows) {
		this.rows = rows;
	}

	public int getColumns() {
		return columns;
	}

	public void setColumns(int columns) {
		this.columns = columns;
	}

	private int rows;
	private int columns;
	private static Random r = new Random();
	
	public Egg(int rows, int columns) {
		this.rows = rows;
		this.columns = columns;
	}
	
	public Egg() {	
		this(r.nextInt(Yard.ROWS), r.nextInt(Yard.COLUMNS));
	}
	
	public void generateNextEgg() {
		this.rows = r.nextInt(Yard.ROWS-3) + 2;
		this.columns = r.nextInt(Yard.COLUMNS-1);
	}
	
	public void draw(Graphics g) {
		Color c = g.getColor();
		g.setColor(Color.YELLOW);
		g.fillRect(this.columns*Yard.BLOCK_SIZE, this.rows*Yard.BLOCK_SIZE, Yard.BLOCK_SIZE, Yard.BLOCK_SIZE);
		
		g.setColor(c);
	}
	
	public Rectangle getRect() {
		return new Rectangle(this.rows*Yard.BLOCK_SIZE, this.columns*Yard.BLOCK_SIZE,
					Yard.BLOCK_SIZE, Yard.BLOCK_SIZE);
	}
}
