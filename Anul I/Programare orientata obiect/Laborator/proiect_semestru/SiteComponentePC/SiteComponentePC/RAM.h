#pragma once
#include "Component.h"
#include <string>
using namespace std;

class RAM : public Component
{
	private:
		int capacity;
		string cellType;
		string memoryType;
		int memorySpeed;
	public:
		RAM();
		RAM(int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG,
			string codG, string nameG, int priceG, int stockG);
		RAM(const RAM& other);
		~RAM();

		int getCapacity() { return capacity; }
		string getCellType() { return cellType; }
		string getMemoryType() { return memoryType; }
		int getMemorySpeed() { return memorySpeed; }

		friend ostream& operator<<(ostream& os, RAM& other);
};
