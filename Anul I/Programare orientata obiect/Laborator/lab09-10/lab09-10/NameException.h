#pragma once
#include <string>
#include <ostream>
using namespace std;

class NameException
{
private:
	string message;

public:
	NameException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const NameException& other)
	{
		os << other.message;
		return os;
	}
};
