#pragma once
#include "Component.h"
#include <ostream>
#include <string>
using namespace std;

class CPU : public Component
{
	private:
		string socket;
		int threads;
		int cores;
		pair<double, double> clockSpeed; // first - base speed ; second - turbo speed (matches base if none)
		int cache;
		bool cooler;
		bool unlocked;
		pair<string, int> memory; // first - memory type supported ; second - max capacity supported
		int memorySpeed;
		string pciE;
	public:
		CPU();
		CPU(string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG, bool coolerG, bool unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG,
			string codG, string nameG, int priceG, int stockG);
		CPU(const CPU& other);
		~CPU();

		string getSocket() { return socket; }
		int getThreads() { return threads; }
		int getCores() { return cores; }
		pair<double, double> getClockSpeed() { return clockSpeed; }
		int getCache() { return cache; }
		bool hasCooler() { return cooler; }
		bool isUnlocked() { return unlocked; }
		pair<string, int> getMemoryData() { return memory; }
		int getMemorySpeed() { return memorySpeed; }
		string getPciEData() { return pciE; }

		friend ostream& operator<<(ostream& os, CPU& other);
};
