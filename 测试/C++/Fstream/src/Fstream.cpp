//============================================================================
// Name        : Fstream.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream ofs;
	ofs.open("table.txt", ios::out | ios::trunc);
	char temp[50];
	cout << "Write To File..." << endl;

	cout << "Please Input Your Name:" << endl;
	cin.getline(temp, sizeof(temp));
	ofs << "ÐÕÃû£º";
	ofs << temp << endl;

	cout << "Please Input Your Age:" << endl;
	cin.getline(temp, 100);
	ofs << temp << endl;

	ofs.close();
	cout << "Write Complete!" << endl;

	ifstream ifs;
	ifs.open("table.txt", ios::in);
	while(ifs.eof() != true) {
		ifs >> temp;
		cout << temp << endl;
		temp[0] = NULL;
	}

	ifs.close();
	cout << "Read File End!" << endl;

	return 0;
}
