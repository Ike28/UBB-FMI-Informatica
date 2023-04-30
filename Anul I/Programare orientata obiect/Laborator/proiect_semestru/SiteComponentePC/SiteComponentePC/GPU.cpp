#include "GPU.h"

GPU::GPU() : Component()
{
	memory.second = 0;
	memorySpeed = 0;
	maxRes.first = 0;
	maxRes.second = 0;
	memorySpeed = 0;
	busWidth = 0;
	cuda = 0;
}

GPU::GPU(string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int, int> maxResG, int busWidthG, int cudaG, string pciEG, 
		 string codG, string nameG, int priceG, int stockG)
	: Component(codG, nameG, priceG, stockG)
{
	series = seriesG;
	memory = memoryG;
	memorySpeed = memorySpeedG;
	maxRes = maxResG;
	busWidth = busWidthG;
	cuda = cudaG;
	pciE = pciEG;
}

GPU::GPU(const GPU& other) : Component(other)
{
	series = other.series;
	memory = other.memory;
	memorySpeed = other.memorySpeed;
	maxRes = other.maxRes;
	busWidth = other.busWidth;
	cuda = other.cuda;
	pciE = other.pciE;
}

GPU::~GPU()
{
	Component::~Component();
}

ostream& operator<<(ostream& os, GPU& other)
{
	if (&os == &cout)
	{
		string toString = "ID: ";
		toString += other.getCode() + " | Placa video " + other.getName() + " | Pret: " + to_string(other.getPrice()) + " lei | Stoc: " + to_string(other.getStock());
		toString += " | Seria " + other.series + " | " + other.memory.first + " , " + to_string(other.memory.second) + " GB | " + to_string(other.memorySpeed) +
					" MHz | Rezolutie maxima " + to_string(other.maxRes.first) + "x" + to_string(other.maxRes.second) + " px | Marime BUS " + to_string(other.busWidth) + " biti | Nuclee CUDA: " +
					to_string(other.cuda) + " | PCI Express " + other.pciE;
		os << toString;
	}
	else
	{
		string toString = "GPU | ";
		toString += other.getCode() + " | " + other.getName() + " | " + to_string(other.getPrice()) + " | " + to_string(other.getStock());
		toString += " | " + other.series + " | " + other.memory.first + " , " + to_string(other.memory.second) + " | " + to_string(other.memorySpeed) +
					" | " + to_string(other.maxRes.first) + " , " + to_string(other.maxRes.second) + " | " + to_string(other.busWidth) + " | " +
					to_string(other.cuda) + " | " + other.pciE;
		os << toString;
	}
	return os;
}
