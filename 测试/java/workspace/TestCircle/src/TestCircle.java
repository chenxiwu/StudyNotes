class Point {
	double x, y;
	
	Point (double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	void setPoint(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	double getDistance(Point point) {
		return (Math.sqrt( Math.pow(this.x-point.x,2) + Math.pow(this.y-point.y,2) ));
	}
}

class Circle {
	Point o;
	double r;
	
	Circle(Point o, double r) {
		this.o = o;
		this.r = r;
	}
	
	double getRadius() {
		return r;
	}
	
	Point getO() {
		return o;
	}
}

public class TestCircle {
	public static void main (String[] args) {
		Point o = new Point(0,0);
		Circle circle = new Circle(o, 2);
		
		Point point = new Point(2,2);
		
		double distance = circle.getO().getDistance(point);
		System.out.println("距离：" + distance);
		if (distance > circle.getRadius()) {
			System.out.println("点不在圆内");
		} else {
			System.out.println("点在圆内");
		}
	}
}
