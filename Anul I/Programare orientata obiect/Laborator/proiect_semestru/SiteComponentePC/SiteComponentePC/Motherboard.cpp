#include "Motherboard.h"

Motherboard::Motherboard(string socketG, pair<string, string> chipsetG, pair<string, int> memoryG, int memorySlotsG, map<string, int> connectorsG, map<string, int> pciEG,
						 string codG, string nameG, int priceG, int stockG)
	: Component(codG, nameG, priceG, stockG)
{
	this->socket = socketG;
	this->chipset = chipsetG;
	this->memory = memoryG;
	this->memorySlots = memorySlotsG;
	this->connectors = connectorsG;
	this->pciE = pciEG;
}

Motherboard::Motherboard(): Component()
{
	this->memory.second = 0;
	this->memorySlots = 0;

	this->connectors.insert(pair<string, int>("PS/2", -1));
	this->connectors.insert(pair<string, int>("DVI", -1));
	this->connectors.insert(pair<string, int>("HDMI", -1));
	this->connectors.insert(pair<string, int>("USB 2.0", -1));
	this->connectors.insert(pair<string, int>("USB 3.0", -1));
	this->connectors.insert(pair<string, int>("LAN", -1));
	this->connectors.insert(pair<string, int>("VGA", -1));
	this->connectors.insert(pair<string, int>("USB 3.1 A", -1));
	this->connectors.insert(pair<string, int>("USB 3.1 C", -1));

	this->pciE.insert(pair<string, int>("3.0 x16", -1));
	this->pciE.insert(pair<string, int>("2.0 x16", -1));
	this->pciE.insert(pair<string, int>("x1", -1));
}

Motherboard::Motherboard(const Motherboard& other) : Component(other)
{
	this->socket = other.socket;
	this->chipset = other.chipset;
	this->memory = other.memory;
	this->memorySlots = other.memorySlots;
	this->connectors = other.connectors;
	this->pciE = other.pciE;
}

Motherboard::~Motherboard()
{
	Component::~Component();
}

ostream& operator<<(ostream& os, Motherboard& other)
{
	if (&os == &cout)
	{
		string toString = "ID ";
		toString += other.getCode() + " | Placa de baza " + other.getName() + " | Pret: " + to_string(other.getPrice()) + " lei | Stoc: " + to_string(other.getStock());
		toString += " buc | Socket: " + other.socket + " | Chipset: " + other.chipset.first + " , " + other.chipset.second + " | Memorie suportata: " + other.memory.first + " , " + 
					to_string(other.memory.second) + " GB max | Sloturi memorie: " + to_string(other.memorySlots);
		os << toString;
	}
	else
	{
		string toString = "MBD | ";
		toString += other.getCode() + " | " + other.getName() + " | " + to_string(other.getPrice()) + " | " + to_string(other.getStock());
		toString += " | " + other.socket + " | " + other.chipset.first + " , " + other.chipset.second + " | " + other.memory.first + " , " + to_string(other.memory.second) + " | " + to_string(other.memorySlots) + " | ";
		toString += to_string(other.connectors["PS/2"]) + "," + to_string(other.connectors["DVI"]) + "," + to_string(other.connectors["HDMI"]) + "," + to_string(other.connectors["USB 2.0"]) + "," + to_string(other.connectors["USB 3.0"]) + "," +
			to_string(other.connectors["LAN"]) + "," + to_string(other.connectors["VGA"]) + "," + to_string(other.connectors["USB 3.1 A"]) + "," + to_string(other.connectors["USB 3.1 C"]) +
			+" | " + to_string(other.pciE["3.0 x16"]) + "," + to_string(other.pciE["2.0 x16"]) + "," + to_string(other.pciE["x1"]);
		os << toString;
	}
	return os;
}
