/*
 * TicketMachine.h
 *
 *  Created on: 2017��2��17��
 *      Author: SY
 */

#ifndef TICKETMACHINE_H_
#define TICKETMACHINE_H_

class TicketMachine {
public:
	TicketMachine();
	virtual ~TicketMachine();
	void showPrompt();
	void insertMoney(int money);
	void printTicket();
	void showTotal();
	void showBalance();

private:
	const int PRICE;
	int balance;
	int total;
};

#endif /* TICKETMACHINE_H_ */
