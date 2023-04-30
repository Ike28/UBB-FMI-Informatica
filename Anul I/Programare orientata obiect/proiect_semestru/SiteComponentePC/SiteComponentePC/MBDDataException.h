#pragma once
#include "BaseException.h"
#include <ostream>

class MBDDataException : public BaseException
{
public:
	MBDDataException(string message) : BaseException(message) { }
	friend ostream& operator<<(ostream& os, const MBDDataException& other)
	{
		os << (BaseException&)other; return os;
	}
};
