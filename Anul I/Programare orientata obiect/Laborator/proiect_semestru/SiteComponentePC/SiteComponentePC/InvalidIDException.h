#pragma once
#include "BaseException.h"
#include <ostream>

class InvalidIDException : public BaseException
{
public:
	InvalidIDException(string message) : BaseException(message) { }
	friend ostream& operator<<(ostream& os, const InvalidIDException& other)
	{
		os << (BaseException&)other; return os;
	}
};
