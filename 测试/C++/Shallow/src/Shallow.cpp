//============================================================================
// Name        : Shallow.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Student {
public:
	Student(int age) {
		this->age = age;
		cout << "Constructor" << endl;
	};
	Student(const Student &s) {
		age = s.age;
		cout << "Shallow" << endl;
	};
	~Student() {
		cout << "Destructor" << endl;
	};
	void printAge() {
		cout << "ÄêÁä£º" << age << endl;
	}

private:
	int age;
};

int main() {
	Student a(18);
	cout << "Start..." << endl;
	Student b = a;
	b.printAge();

	return 0;
}
