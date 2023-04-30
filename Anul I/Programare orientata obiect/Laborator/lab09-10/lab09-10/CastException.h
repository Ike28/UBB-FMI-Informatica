#pragma once
#include <string>
#include <ostream>
using namespace std;

class CastException
{
private:
	string message;

public:
	CastException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const CastException& other)
	{
		os << other.message;
		return os;
	}
};
