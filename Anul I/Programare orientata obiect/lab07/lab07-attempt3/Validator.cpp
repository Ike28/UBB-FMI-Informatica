#include "Validator.h"
#include <string>
#include <vector>

void Validator::validatePayment(Payment& elem)
{
	string exceptions = "";

	if (elem.getDay() < 1 || elem.getDay() > 31)
		exceptions += "\nZiua cheltuielii trebuie sa existe in calendar.";

	if (elem.getSum() < 1)
		exceptions += "\nSuma cheltuita trebuie sa fie un numar pozitiv";

	bool validType = false;
	//for (vector<const char*>::iterator i = Payment::getTypes().begin(); i != Payment::getTypes().end(); i++)
		//if (strcmp((*i), elem.getTip()) == 0)
			//validType = true;
	if (!validType)
		exceptions += "\nTipul poate fi doar unul dintre:\n-----> menaj, mancare, transport, haine, internet, altele";
	
	if (exceptions.size() > 0)
		throw exceptions;
}
