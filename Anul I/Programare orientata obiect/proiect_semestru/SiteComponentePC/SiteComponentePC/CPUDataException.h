#pragma once
#include "BaseException.h"
#include <ostream>

class CPUDataException : public BaseException
{
	public:
		CPUDataException(string message) : BaseException(message) { }
		friend ostream& operator<<(ostream& os, const CPUDataException& other) 
		{ os << (BaseException&)other; return os; }
};
