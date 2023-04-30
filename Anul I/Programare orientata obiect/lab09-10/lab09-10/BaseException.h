#pragma once
#include <string>
#include <ostream>
using namespace std;

class BaseException
{
private:
	string message;

public:
	BaseException(string message)
	{
		this->message = message;
	}
	string getMessage()
	{
		return message;
	}
	friend ostream& operator<<(ostream& os, const BaseException& other)
	{
		os << other.message;
		return os;
	}
};
