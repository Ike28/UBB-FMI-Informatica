#pragma once
#include "BaseException.h"
#include <ostream>

class RAMDataException : public BaseException
{
public:
	RAMDataException(string message) : BaseException(message) { }
	friend ostream& operator<<(ostream& os, const RAMDataException& other)
	{
		os << (BaseException&)other; return os;
	}
};
