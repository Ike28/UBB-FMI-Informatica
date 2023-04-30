#pragma once
#include "BaseException.h"
#include <ostream>

class GPUDataException : public BaseException
{
public:
	GPUDataException(string message) : BaseException(message) { }
	friend ostream& operator<<(ostream& os, const GPUDataException& other)
	{
		os << (BaseException&)other; return os;
	}
};
