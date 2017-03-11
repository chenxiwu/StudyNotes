//============================================================================
// Name        : New.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
	int *temp = new int[10];

	temp[1] = 5;

	for (int i=0; i<10; i++) {
		cout << temp[i] << endl;
	}

	delete[] temp;

	return 0;
}
