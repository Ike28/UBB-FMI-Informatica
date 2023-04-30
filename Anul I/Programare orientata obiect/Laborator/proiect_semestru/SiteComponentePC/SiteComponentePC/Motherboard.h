#pragma once
#include "Component.h"
#include <map>
#include <string>
using namespace std;

class Motherboard : public Component
{
	private:
		string socket;
		pair<string, string> chipset; // first - chipset manufacturer ; second - chipset model
		pair<string, int> memory; // first - memory type supported ; second - max capacity
		int memorySlots;
		map<string, int> connectors; // PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C
		map<string, int> pciE; // 3.0 x16, 2.0 x16, x1
	public:
		Motherboard(string socketG, pair<string, string> chipsetG, pair<string, int> memoryG, int memorySlotsG, map<string, int> connectorsG, map<string, int> pciEG,
					string codG, string nameG, int priceG, int stockG);
		Motherboard();
		Motherboard(const Motherboard& other);
		~Motherboard();

		string getSocket() { return socket; }
		pair<string, string> getChipsetData() { return chipset; }
		pair<string, int> getMemoryData() { return memory; }
		int getMemorySlots() { return memorySlots; }
		map<string, int> getConnectorsData() { return connectors; }
		map<string, int> getPciEData() { return pciE; }

		friend ostream& operator<<(ostream& os, Motherboard& other);
};
