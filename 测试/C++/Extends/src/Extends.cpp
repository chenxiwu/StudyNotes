//============================================================================
// Name        : Extends.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Shape {
public:
	Shape(int width, int height) {
		this->width = width;
		this->height = height;
		cout << "基类构造函数" << endl;
		cout << "base::width:" << width << endl;
		cout << "base::height:" << height << endl;
	}

protected:
	int width;
	int height;
};

class Rectangle : public Shape {
public:
	Rectangle(int width, int height) : Shape(width, height) {
		this->width = width;
		this->height = height;

		cout << "width:" << width << endl;
		cout << "height:" << height << endl;
	};

	int getArea() {
		return width * height;
	};
};

int main() {
	Rectangle rect(20, 10);
	cout << "面积：" << rect.getArea();

	return 0;
}
