#pragma once
#include "Book.h"
#include "Service.h"
#include "ServiceFile.h"

class UserInterface
{
private:
	ServiceFile serviceBook;
	void addBook();
	void deleteBook();
	void updateBook();
	void readBooks();
	void orderBooks();

	static void printMenu();
public:
	UserInterface();
	UserInterface(ServiceFile serviceGiven);
	~UserInterface();

	void runInterface();
};
