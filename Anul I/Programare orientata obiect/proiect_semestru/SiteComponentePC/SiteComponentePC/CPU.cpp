#include "CPU.h"

CPU::CPU() :Component()
{
	cache = 0;
	cooler = false;
	unlocked = false;
	threads = 0;
	cores = 0;
	memory.second = 0;
	memorySpeed = 0;
	clockSpeed.first = 0;
	clockSpeed.second = 0;
}

CPU::CPU(string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG, bool coolerG, bool unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG, 
		 string codG, string nameG, int priceG, int stockG)
	: Component(codG, nameG, priceG, stockG)
{
	socket = socketG;
	cores = coresG;
	threads = threadsG;
	clockSpeed = clockSpeedG;
	cache = cacheG;
	cooler = coolerG;
	unlocked = unlockedG;
	memory = memoryG;
	memorySpeed = memorySpeedG;
	pciE = pciEG;
}

CPU::CPU(const CPU& other) : Component(other)
{
	socket = other.socket;
	cores = other.cores;
	threads = other.threads;
	clockSpeed = other.clockSpeed;
	cache = other.cache;
	cooler = other.cooler;
	unlocked = other.unlocked;
	memory = other.memory;
	memorySpeed = other.memorySpeed;
	pciE = other.pciE;
}

CPU::~CPU()
{
	Component::~Component();
}

ostream& operator<<(ostream& os, CPU& other)
{
	if (&os == &cout)
	{
		string toString = "ID: ";
		toString += other.getCode() + " | Procesor " + other.getName() + " | Pret: " + to_string(other.getPrice()) + " lei | Stoc: " + to_string(other.getStock());
		toString += " buc | Socket: " + other.socket + " | Threads: " + to_string(other.threads) + " | Cores: " + to_string(other.cores) + " | Frecventa: " +
			to_string(other.clockSpeed.first) + " base , " + to_string(other.clockSpeed.second) + " turbo | " + to_string(other.cache) + " cache | Cooler: " +
			to_string(other.cooler) + " | Unlocked: " + to_string(other.unlocked) + " | Memorie: " + other.memory.first + " , " + to_string(other.memory.second) + " GB max | " +
			to_string(other.memorySpeed) + " Mhz | PCI Express " + other.pciE;
		os << toString;
	}
	else
	{
		string toString = "CPU | ";
		toString += other.getCode() + " | " + other.getName() + " | " + to_string(other.getPrice()) + " | " + to_string(other.getStock());
		toString += " | " + other.socket + " | " + to_string(other.threads) + " | " + to_string(other.cores) + " | " +
					to_string(other.clockSpeed.first) + " , " + to_string(other.clockSpeed.second) + " | " + to_string(other.cache) + " | " +
					to_string(other.cooler) + " | " +to_string(other.unlocked) + " | " + other.memory.first + " , " + to_string(other.memory.second) + " | " +
					to_string(other.memorySpeed) + " | " + other.pciE;
		os << toString;
	}
	return os;
}
