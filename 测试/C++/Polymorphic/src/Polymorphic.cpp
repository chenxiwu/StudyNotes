//============================================================================
// Name        : Polymorphic.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//多态
class Shape {
protected:
	int width;
	int height;

public:
	Shape(int width, int height) {
		this->width = width;
		this->height = height;
	};
	virtual int getArea() = 0;
};

class Rectangle : public Shape {
public:
	Rectangle(int width, int height) : Shape(width, height) {
		this->width = width;
		this->height = height;
	};
	int getArea() {
		return width * height;
	};
};

class Triangle : public Shape {
public:
	Triangle(int width, int height) : Shape(width, height) {
		this->width = width;
		this->height = height;
	};
	int getArea() {
		return (width * height / 2);
	};
};

int main() {
	Rectangle rect(20, 10);
	Triangle tri(50, 20);

	Shape *shape;

	shape = &rect;
	cout << "矩形面积：" << shape->getArea() << endl;

	shape = &tri;
	cout << "三角形面积：" << shape->getArea() << endl;

	return 0;
}
