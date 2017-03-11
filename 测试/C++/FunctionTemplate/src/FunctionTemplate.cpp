//============================================================================
// Name        : FunctionTemplate.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

template <typename T>
inline T const& Max(T const &a, T const &b) {
	return (a < b) ? b : a;
}

int main() {
	int a = 1;
	int b = 4;
	cout << Max(a, b) << endl;

	float c = 2.3;
	float d = 3.5;
	cout << Max(c, d) << endl;

	string e = "张三";
	string f = "李四";
	cout << Max(e, f) << endl;

	return 0;
}
