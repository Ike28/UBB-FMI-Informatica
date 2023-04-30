#pragma once
#include <string>
#include <ostream>
using namespace std;

class InvalidIDException
{
private:
	string message;

public:
	InvalidIDException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const InvalidIDException& other)
	{
		os << other.message;
		return os;
	}
};
