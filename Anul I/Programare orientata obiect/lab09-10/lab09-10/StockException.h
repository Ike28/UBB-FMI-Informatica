#pragma once
#include <string>
#include <ostream>
using namespace std;

class StockException
{
private:
	string message;

public:
	StockException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const StockException& other)
	{
		os << other.message;
		return os;
	}
};
