//============================================================================
// Name        : Exception.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int devision(int a, int b) {
	if (b == 0) {
		throw "The Exception By Devision Zero!";
	} else {
		return (a/b);
	}
}

int main() {
	int a = 50;
	int b = 0;
	int ret;

	try {
		ret = devision(a, b);
		cout << ret << endl;
	} catch (const char *e) {
		cerr << e << endl;
	}

	return 0;
}
