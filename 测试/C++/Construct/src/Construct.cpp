//============================================================================
// Name        : Construct.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Student {
public:
	Student(string name) {
		this->name = name;
		age = 50;
	}
	~Student() {
		cout << "姓名：" << name << endl;
		cout << "年龄：" << age << endl;
	}
private:
	int age;
	string name;
};

int main() {

	cout << "Start..." << endl;
	{
		Student a("大水猫");
	}
	cout << "End..." << endl;
	return 0;
}
