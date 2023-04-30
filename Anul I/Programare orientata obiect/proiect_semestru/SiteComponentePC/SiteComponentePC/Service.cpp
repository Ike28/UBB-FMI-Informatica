#include "Service.h"
#include "utils.h"
#include "InvalidIDException.h"

void Service::deleteCPU(string cod)
{
	if (this->repoCPU->findByID(cod) == nullptr)
		throw InvalidIDException("\nNo CPU object with such ID exists");
	this->repoCPU->deleteByID(cod);
}

void Service::updateCPU(string codA, string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG, 
	string coolerG, string unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG, string nameG, int priceG, int stockG)
{
	CPU* found = this->repoCPU->findByID(codA);
	if (found != nullptr)
	{
		if (threadsG == -1) threadsG = found->getThreads();
		if (socketG.compare("") == 0) socketG = found->getSocket();
		if (coresG == -1) coresG = found->getCores();
		if (clockSpeedG.first == -1.0) clockSpeedG = found->getClockSpeed();
		if (cacheG == -1) cacheG = found->getCache();
		if (memoryG.second == -1) memoryG = found->getMemoryData();
		if (memorySpeedG == -1) memorySpeedG = found->getMemorySpeed();
		if (pciEG.compare("") == 0) pciEG = found->getPciEData();
		if (nameG.compare("") == 0) nameG = found->getName();
		if (priceG == -1) priceG = found->getPrice();
		if (stockG == -1) stockG = found->getStock();

		bool cooler;
		if (coolerG.compare("") == 0) cooler = found->hasCooler();
		else if (coolerG.compare("true") == 0) cooler = true;
		else cooler = false;

		bool unlocked;
		if (unlockedG.compare("") == 0) unlocked = found->isUnlocked();
		else if (unlockedG.compare("true") == 0) unlocked = true;
		else unlocked = false;
		CPU* x = new CPU(socketG, threadsG, coresG, clockSpeedG, cacheG, cooler, unlocked, memoryG, memorySpeedG, pciEG, codA, nameG, priceG, stockG);
		this->CPUv.validate(x);
		this->repoCPU->updateByID(codA, x);
	}
	else throw InvalidIDException("\nNo CPU object with such ID exists");
}

vector<CPU*> Service::searchCPU(vector<string> keywords)
{
	vector<CPU*> storage = this->repoCPU->getAll();
	vector<CPU*> results;
	bool ok = false;
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		ok = true;
		for (vector<string>::iterator j = keywords.begin(); j != keywords.end(); j++)
			if ((*i)->getName().find(*j) == string::npos)
				ok = false;
		if (ok)
			results.push_back(*i);
	}
	return results;
}

vector<CPU*> Service::CPUByPrice()
{
	vector<CPU*> storage = this->repoCPU->getAll();
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		for (vector<CPU*>::iterator j = i; j != storage.end(); j++)
			if ((*i)->getPrice() > (*j)->getPrice())
			{
				CPU* aux = (*i);
				(*i) = (*j);
				(*j) = aux;
			}
	return storage;
}

void Service::addGPU(string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int, int> maxResG, int busWidthG, 
	int cudaG, string pciEG, string nameG, int priceG, int stockG)
{
	string codG = generateCode();
	GPU* x = new GPU(seriesG, memoryG, memorySpeedG, maxResG, busWidthG, cudaG, pciEG, codG, nameG, priceG, stockG);
	this->GPUv.validate(x);
	this->repoGPU->add(x);
}

void Service::deleteGPU(string cod)
{
	if (this->repoGPU->findByID(cod) == nullptr)
		throw InvalidIDException("\nNo GPU object with such ID exists");
	this->repoGPU->deleteByID(cod);
}

void Service::updateGPU(string codA, string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int, int> maxResG, 
	int busWidthG, int cudaG, string pciEG, string nameG, int priceG, int stockG)
{
	GPU* found = this->repoGPU->findByID(codA);
	if (found != nullptr)
	{
		if (seriesG.compare("") == 0) seriesG = found->getSeries();
		if (memoryG.second == -1) memoryG = found->getMemoryData();
		if (memorySpeedG == -1) memorySpeedG = found->getMemorySpeed();
		if (maxResG.first == -1) maxResG = found->getMaxRes();
		if (busWidthG == -1) busWidthG = found->getBusWidth();
		if (cudaG == -1) cudaG = found->getCuda();
		if (pciEG.compare("") == 0) pciEG = found->getPciE();
		if (nameG.compare("") == 0) nameG = found->getName();
		if (priceG == -1) priceG = found->getPrice();
		if (stockG == -1) stockG = found->getStock();
		GPU* x = new GPU(seriesG, memoryG, memorySpeedG, maxResG, busWidthG, cudaG, pciEG, codA, nameG, priceG, stockG);
		this->GPUv.validate(x);
		this->repoGPU->updateByID(codA, x);
	}
	else throw InvalidIDException("\nNo GPU object with such ID exists");
}

vector<GPU*> Service::searchGPU(vector<string> keywords)
{
	vector<GPU*> storage = this->repoGPU->getAll();
	vector<GPU*> results;
	bool ok = false;
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		ok = true;
		for (vector<string>::iterator j = keywords.begin(); j != keywords.end(); j++)
			if ((*i)->getName().find(*j) == string::npos)
				ok = false;
		if (ok)
			results.push_back(*i);
	}
	return results;
}

void Service::filterGPU(string memorySpeed, string bus, string cuda)
{
	vector<GPU*> storage = this->repoGPU->getAll();
	vector<string> deleteCodes;
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		int memSp = stoi(memorySpeed.substr(1, memorySpeed.size()));
		if (memorySpeed[0] == '>' && (*i)->getMemorySpeed() <= memSp ||
			memorySpeed[0] == '=' && (*i)->getMemorySpeed() != memSp ||
			memorySpeed[0] == '<' && (*i)->getMemorySpeed() >= memSp)
			deleteCodes.push_back((*i)->getCode());

		int busSp = stoi(bus.substr(1, bus.size()));
		if (bus[0] == '>' && (*i)->getBusWidth() <= busSp ||
			bus[0] == '=' && (*i)->getBusWidth() != busSp ||
			bus[0] == '<' && (*i)->getBusWidth() >= busSp)
			deleteCodes.push_back((*i)->getCode());

		int cudaSp = stoi(cuda.substr(1, cuda.size()));
		if (cuda[0] == '>' && (*i)->getCuda() <= cudaSp ||
			cuda[0] == '=' && (*i)->getCuda() != cudaSp ||
			cuda[0] == '<' && (*i)->getCuda() >= cudaSp)
			deleteCodes.push_back((*i)->getCode());
	}
	for (vector<string>::iterator i = deleteCodes.begin(); i != deleteCodes.end(); i++)
		this->repoGPU->deleteByID(*i);
}

vector<GPU*> Service::GPUByPrice()
{
	vector<GPU*> storage = this->repoGPU->getAll();
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		for (vector<GPU*>::iterator j = i; j != storage.end(); j++)
			if ((*i)->getPrice() > (*j)->getPrice())
			{
				GPU* aux = (*i);
				(*i) = (*j);
				(*j) = aux;
			}
	return storage;
}

void Service::addMBD(string socketG, pair<string, string> chipsetG, pair<string, int> memoryG, int memorySlotsG, 
	map<string, int> connectorsG, map<string, int> pciEG, string nameG, int priceG, int stockG)
{
	string codG = generateCode();
	Motherboard* x = new Motherboard(socketG, chipsetG, memoryG, memorySlotsG, connectorsG, pciEG, codG, nameG, priceG, stockG);
	this->MBDv.validate(x);
	this->repoMBD->add(x);
}

void Service::deleteMBD(string cod)
{
	if (this->repoMBD->findByID(cod) == nullptr)
		throw InvalidIDException("\nNo Motherboard object with such ID exists");
	this->repoMBD->deleteByID(cod);
}

void Service::updateMBD(string codA, string socketG, pair<string, string> chipsetG, pair<string, int> memoryG, 
	int memorySlotsG, map<string, int> connectorsG, map<string, int> pciEG, string nameG, int priceG, int stockG)
{
	Motherboard* found = this->repoMBD->findByID(codA);
	if (found != nullptr)
	{
		if (socketG.compare("") == 0) socketG = found->getSocket();
		if (chipsetG.first.compare("") == 0) chipsetG = found->getChipsetData();
		if (memoryG.second == -1) memoryG = found->getMemoryData();
		if (memorySlotsG == -1) memorySlotsG = found->getMemorySlots();
		if (connectorsG.size() == 0) connectorsG = found->getConnectorsData();
		if (pciEG.size() == 0) pciEG = found->getPciEData();
		if (nameG.compare("") == 0) nameG = found->getName();
		if (priceG == -1) priceG = found->getPrice();
		if (stockG == -1) stockG = found->getStock();
		Motherboard* x = new Motherboard(socketG, chipsetG, memoryG, memorySlotsG, connectorsG, pciEG, codA, nameG, priceG, stockG);
		this->MBDv.validate(x);
		this->repoMBD->updateByID(codA, x);
	}
	else throw InvalidIDException("\nNo Motherboard object with such ID exists");
}

vector<Motherboard*> Service::searchMBD(vector<string> keywords)
{
	vector<Motherboard*> storage = this->repoMBD->getAll();
	vector<Motherboard*> results;
	bool ok = false;
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		ok = true;
		for (vector<string>::iterator j = keywords.begin(); j != keywords.end(); j++)
			if ((*i)->getName().find(*j) == string::npos)
				ok = false;
		if (ok)
			results.push_back(*i);
	}
	return results;
}

vector<Motherboard*> Service::MBDByPrice()
{
	vector<Motherboard*> storage = this->repoMBD->getAll();
	// Find the maximum number to know number of digits
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
		for (vector<Motherboard*>::iterator j = i; j != storage.end(); j++)
			if ((*i)->getPrice() > (*j)->getPrice())
			{
				Motherboard* aux = (*i);
				(*i) = (*j);
				(*j) = aux;
			}
	return storage;
}

void Service::addRAM(int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG, string nameG, 
	int priceG, int stockG)
{
	string codG = generateCode();
	RAM* x = new RAM(capacityG, cellTypeG, memoryTypeG, memorySpeedG, codG, nameG, priceG, stockG);
	this->RAMv.validate(x);
	this->repoRAM->add(x);
}

void Service::deleteRAM(string cod)
{
	if (this->repoRAM->findByID(cod) == nullptr)
		throw InvalidIDException("\nNo RAM object with such ID exists");
	this->repoRAM->deleteByID(cod);
}

void Service::updateRAM(string codA, int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG, 
	string nameG, int priceG, int stockG)
{
	RAM* found = this->repoRAM->findByID(codA);
	if (found != nullptr)
	{
		if (capacityG == -1) capacityG = found->getCapacity();
		if (cellTypeG.compare("") == 0) cellTypeG = found->getCellType();
		if (memoryTypeG.compare("") == 0) memoryTypeG = found->getMemoryType();
		if (memorySpeedG == -1) memorySpeedG = found->getMemorySpeed();
		if (nameG.compare("") == 0) nameG = found->getName();
		if (priceG == -1) priceG = found->getPrice();
		if (stockG == -1) stockG = found->getStock();
		RAM* x = new RAM(capacityG, cellTypeG, memoryTypeG, memorySpeedG, codA, nameG, priceG, stockG);
		this->RAMv.validate(x);
		this->repoRAM->updateByID(codA, x);
	}
	else throw InvalidIDException("\nNo RAM object with such ID exists");
}

vector<RAM*> Service::searchRAM(vector<string> keywords)
{
	vector<RAM*> storage = this->repoRAM->getAll();
	vector<RAM*> results;
	bool ok = false;
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		ok = true;
		for (vector<string>::iterator j = keywords.begin(); j != keywords.end(); j++)
			if ((*i)->getName().find(*j) == string::npos)
				ok = false;
		if (ok)
			results.push_back(*i);
	}
	return results;
}


vector<RAM*> Service::RAMByPrice()
{
	vector<RAM*> storage = this->repoRAM->getAll();
	// Find the maximum number to know number of digits
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
		for (vector<RAM*>::iterator j = i; j != storage.end(); j++)
			if ((*i)->getPrice() > (*j)->getPrice())
			{
				RAM* aux = (*i);
				(*i) = (*j);
				(*j) = aux;
			}
	return storage;
}

void Service::addCPU(string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG, bool coolerG, 
	bool unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG, string nameG, int priceG, int stockG)
{
	string codG = generateCode();
	CPU* x = new CPU(socketG, threadsG, coresG, clockSpeedG, cacheG, coolerG, unlockedG, memoryG, memorySpeedG, pciEG, codG, nameG, priceG, stockG);
	this->CPUv.validate(x);
	this->repoCPU->add(x);
}
