#pragma once
#include <string>
#include <ostream>
using namespace std;

class PriceException
{
private:
	string message;

public:
	PriceException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const PriceException& other)
	{
		os << other.message;
		return os;
	}
};
