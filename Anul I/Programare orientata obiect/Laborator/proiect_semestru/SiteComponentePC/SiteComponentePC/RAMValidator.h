#pragma once
#include "RAM.h"
#include "RAMDataException.h"

class RAMValidator
{
public:
	void validate(RAM* other)
	{
		/*
		int capacity;
		string cellType;
		string memoryType;
		int memorySpeed;*/

		string errors = "";
		if (other->getCapacity() < 1)
			errors += "\nCapacity: must be at least 1";
		if (other->getCellType().compare("SRAM") != 0 && other->getCellType().compare("DRAM")!=0)
			errors += "\nCell Type: can only be DRAM or SRAM (currently "+ other->getCellType();
		if (other->getMemoryType().compare("") == 0)
			errors += "\nMemory Type: cannot be null";
		if (other->getMemorySpeed() < 1)
			errors += "\nMemory Speed: must be at least 1";
		if (other->getName().compare("") == 0)
			errors += "\nModel name: cannot be null";
		if (other->getPrice() < 0)
			errors += "\nPrice: cannot be lower than zero";
		if (other->getStock() < 0)
			errors += "\nStock: cannot be lower than zero";

		if (errors.size() > 0)
			throw RAMDataException(errors);
	}
};