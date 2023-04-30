#pragma once
#include "Motherboard.h"
#include "MBDDataException.h"

class MBDValidator
{
public:
	void validate(Motherboard* other)
	{
		/*string socket;
		pair<string, string> chipset; // first - chipset manufacturer ; second - chipset model
		pair<string, int> memory; // first - memory type supported ; second - max capacity
		int memorySlots;*/

		string errors = "";
		if (other->getSocket().compare("") == 0)
			errors += "\nSocket: cannot be null";
		if (other->getChipsetData().first.compare("") == 0 || other->getChipsetData().second.compare("") == 0)
			errors += "\nChipset: neither manufacturer nor model can be null";
		if (other->getMemoryData().first.compare("") == 0)
			errors += "\nMemory: memory type cannot be null";
		if (other->getMemoryData().second < 1)
			errors += "\nMemory: max memory capacity must be at least 1 (currently " + other->getMemoryData().second;
		if (other->getMemorySlots() < 1)
			errors += "\nMemory slots: must be at least 1 (currently " + other->getMemorySlots();
		if (other->getName().compare("") == 0)
			errors += "\nModel name: cannot be null";
		if (other->getPrice() < 0)
			errors += "\nPrice: cannot be lower than zero";
		if (other->getStock() < 0)
			errors += "\nStock: cannot be lower than zero";

		if (errors.size() > 0)
			throw MBDDataException(errors);
	}
};