//============================================================================
// Name        : Signal.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <windows.h>
#include <signal.h>

using namespace std;

void Interrupt_Handler(int signal) {
	cout << "ÊÕµ½ÐÅºÅ" << signal << endl;

	exit(signal);
}

int main() {
	signal(SIGINT, Interrupt_Handler);

	int num = 0;
	while(true) {
		cout << "I am a Dog!" << endl;
		Sleep(1000);

		num++;
		if (num == 5) {
			raise(SIGINT);
		}
	}

	return 0;
}
