#include "RAM.h"

RAM::RAM() : Component()
{
	capacity = 0;
	memorySpeed = 0;
}

RAM::RAM(int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG, 
		 string codG, string nameG, int priceG, int stockG)
	: Component(codG, nameG, priceG, stockG)
{
	capacity = capacityG;
	cellType = cellTypeG;
	memoryType = memoryTypeG;
	memorySpeed = memorySpeedG;
}

RAM::RAM(const RAM& other) : Component(other)
{
	capacity = other.capacity;
	cellType = other.cellType;
	memoryType = other.memoryType;
	memorySpeed = other.memorySpeed;
}

RAM::~RAM()
{
	Component::~Component();
}

ostream& operator<<(ostream& os, RAM& other)
{
	if (&os == &cout)
	{
		string toString = "ID ";
		toString += other.getCode() + " | Memorie RAM " + other.getName() + " | Pret: " + to_string(other.getPrice()) + " lei | Stoc: " + to_string(other.getStock());
		toString += " buc | " + to_string(other.capacity) + " GB | " + other.cellType + " | " + other.memoryType + " | " + to_string(other.memorySpeed) + " MHz";
		os << toString;
	}
	else
	{
		string toString = "RAM | ";
		toString += other.getCode() + " | " + other.getName() + " | " + to_string(other.getPrice()) + " | " + to_string(other.getStock());
		toString += " | " + to_string(other.capacity) + " | " + other.cellType + " | " + other.memoryType + " | " + to_string(other.memorySpeed);
		os << toString;
	}
	return os;
}
