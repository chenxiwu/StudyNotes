//============================================================================
// Name        : DeepCopy.cpp
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
		ptr = new int;
		*ptr = age;
		cout << "Constructor" << endl;
	};
	Student(const Student &s) {
		ptr = new int;
		*ptr = *s.ptr;
		cout << "Shallow" << endl;
	};
	~Student() {
		cout << "Destructor" << endl;
		delete ptr;
	};
	void printAge() {
		cout << "ÄêÁä£º" << *ptr << endl;
	}

private:
	int* ptr;
};

int main() {
	Student a(20);
	cout << "Start..." << endl;
	Student b = a;
	b.printAge();

	return 0;
}

