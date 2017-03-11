
class Point {
	double x, y, z;
	
	Point(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	void setPoint(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	double getDistance(Point p) {
		return (x * p.x + y * p.y + z * p.z);
	}
	
	void showPoint() {
		System.out.println("x = "+ x + "," + "y = " + y + "," + "z = " + z);
	}
}

public class TestPoint {
	public static void main (String[] args) {
		Point point1 = new Point(1, 2, 3);
		Point point2 = new Point(4, 5, 6);
		
		//System.out.println(point1.getDistance(point2));
		
		point1.setPoint(14, 2.2, 3.3);
		System.out.println(point1.getDistance(point2));
	}
}

