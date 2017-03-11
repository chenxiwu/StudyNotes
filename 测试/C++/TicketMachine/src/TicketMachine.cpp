/*
 * TicketMachine.cpp
 *
 *  Created on: 2017Äê2ÔÂ17ÈÕ
 *      Author: SY
 */

#include "TicketMachine.h"
#include <iostream>

using namespace std;

TicketMachine::TicketMachine() : PRICE(50) {
	// TODO Auto-generated constructor stub
	balance = 0;
	total = 0;
}

TicketMachine::~TicketMachine() {
	// TODO Auto-generated destructor stub
}

void TicketMachine::showPrompt() {
	cout << "showPromote";
}

void TicketMachine::insertMoney(int money) {
	balance += money;
}

void TicketMachine::showBalance() {
	cout << "Óà¶î£º" << balance << endl;
}





