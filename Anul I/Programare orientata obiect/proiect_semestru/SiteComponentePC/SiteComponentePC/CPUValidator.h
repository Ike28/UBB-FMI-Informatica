#pragma once
#include "CPU.h"
#include "CPUDataException.h"

class CPUValidator
{
	public:
		void validate(CPU* other)
		{
			/*string socket;
		int threads;
		int cores;
		pair<double, double> clockSpeed; // first - base speed ; second - turbo speed (matches base if none)
		int cache;
		bool cooler;
		bool unlocked;
		pair<string, int> memory; // first - memory type supported ; second - max capacity supported
		int memorySpeed;
		string pciE;*/

			string errors = "";

			if (other->getSocket().compare("") == 0)
				errors += "\nSocket: cannot be null";
			if (other->getThreads() < 1)
				errors += "\nNumber of threads: must be at least 1";
			if (other->getCores() < 1)
				errors += "\nNumber of cores: must be at least 1";
			if (other->getClockSpeed().first <= 0.0 || other->getClockSpeed().second <= 0.0)
				errors += "\nClock speed: both values must be strictly positive";
			if (other->getClockSpeed().second < other->getClockSpeed().first)
				errors += "\nClock speed: turbo value cannot be lower than base value (currently " + to_string(other->getClockSpeed().first) + " base, " + to_string(other->getClockSpeed().second) + " turbo)";
			if (other->getCache() < 1)
				errors += "\nCache: must be at least 1";
			if (other->getMemoryData().first.compare("") == 0)
				errors += "\nMemory type: cannot be null";
			if (other->getMemoryData().second < 1)
				errors += "\nMemory max capacity: must be at least 1";
			if (other->getMemorySpeed() < 1)
				errors += "\nMemory speed: must be at least 1";
			if (other->getName().compare("") == 0)
				errors += "\nModel name: cannot be null";
			if (other->getPrice() < 0)
				errors += "\nPrice: cannot be lower than zero";
			if (other->getStock() < 0)
				errors += "\nStock: cannot be lower than zero";

			if (errors.size() > 0)
				throw CPUDataException(errors);
		}
};
