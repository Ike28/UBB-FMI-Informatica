#pragma once
#include "Service.h"
#include <stdlib.h>

class UI
{
	private:
		Service* service;

		static void printMenu();
		static void printTerminal();
		static void printCRUDMenu(string specifier);

		void runCRUDInterface(string specifier, string menuInstance);

		void handleAdd(string args);
		void handleShow(string args);
		void handleDelete(string args);
		void handleUpdate(string args);

		void handleSearch(string args);
		void handleFilter(string args);
		void handleSort(string args);
		void handleHelp();
	public:
		UI() { }
		UI(Service* serviceGiven) { service = serviceGiven; }
		~UI() { }

		void runInterface();
		
};
