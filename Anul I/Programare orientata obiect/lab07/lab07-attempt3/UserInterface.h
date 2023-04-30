#pragma once
#include "Payment.h"
#include "Service.h"

class UserInterface
{
	private:
		Service<Payment> servicePayment;
		void addPayment();
		void deletePayment();
		void updatePayment();
		void readPayments();
		void undo();
		void modifyData();
		void listData();
		void properties();
		void filter();

		static void printMenu();
		static void printOperationsMenu();
		void runOperationsInterface();
	public:
		UserInterface();
		UserInterface(Service<Payment> serviceGiven);
		~UserInterface();

		void runInterface();
};
