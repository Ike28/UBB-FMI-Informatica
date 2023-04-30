#pragma once
#include "GPU.h"
#include "GPUDataException.h"

class GPUValidator
{
public:
	void validate(GPU* other)
	{
		/*string series;
		pair<string, int> memory; // first - memory type (DDRX) ; second - capacity
		int memorySpeed;
		pair<int, int> maxRes;
		int busWidth;
		int cuda;
		string pciE;*/

		string errors = "";
		if (other->getSeries().compare("") == 0)
			errors += "\nSeries: cannot be null";
		if (other->getMemoryData().first.compare("") == 0)
			errors += "\nMemory: memory type cannot be null";
		if (other->getMemoryData().second < 1)
			errors += "\nMemory: max memory capacity must be at least 1 (currently " + other->getMemoryData().second;
		if (other->getMemorySpeed() < 1)
			errors += "\nMemory speed: must be at least 1 (currently " + other->getMemorySpeed();
		if (other->getMaxRes().first < 1 || other->getMaxRes().second < 1)
			errors += "\nMax resolution: must be strictly positive";
		if (other->getBusWidth() < 1)
			errors += "\nBus width: must be strictly positive (currently " + other->getBusWidth();
		if (other->getCuda() < 0)
			errors += "\nCUDA cores: number cannot be less than 0 (currently " + other->getCuda();
		if (other->getName().compare("") == 0)
			errors += "\nModel name: cannot be null";
		if (other->getPrice() < 0)
			errors += "\nPrice: cannot be lower than zero";
		if (other->getStock() < 0)
			errors += "\nStock: cannot be lower than zero";

		if (errors.size() > 0)
			throw GPUDataException(errors);
	}
};