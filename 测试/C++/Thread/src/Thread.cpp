//============================================================================
// Name        : Thread.cpp
// Author      : SY
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <pthread.h>
#include <iostream>
#include <windows.h>

using namespace std;

void* Thread_CallBack(void *para) {
	int num = 0;
	while (++num <= 3) {
		cout << "Hello World!" << endl;
		Sleep(1000);
	}

	cout << "Sub Thread Over!" << endl;

	return NULL;
}

int main() {
	pthread_t threadHandle;

	cout << "Hello ´óË®Ã¨!" << endl;

	pthread_create(&threadHandle, NULL, Thread_CallBack, NULL);

	void *tid;
	pthread_join(threadHandle, &tid);

	cout << "Its Over!" << endl;

	return 0;
}
