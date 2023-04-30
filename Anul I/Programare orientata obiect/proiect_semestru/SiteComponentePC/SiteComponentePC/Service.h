#pragma once
#include "RepoCPU.h"
#include "RepoMotherboard.h"
#include "RepoRAM.h"
#include "RepoGPU.h"
#include "CPUValidator.h"
#include "GPUValidator.h"
#include "MBDValidator.h"
#include "RAMValidator.h"

class Service
{
private:
	RepoCPU* repoCPU;
	RepoGPU* repoGPU;
	RepoMBD* repoMBD;
	RepoRAM* repoRAM;

	CPUValidator CPUv;
	GPUValidator GPUv;
	MBDValidator MBDv;
	RAMValidator RAMv;

	void countSort(vector<RAM*>& arr, int exp);
public:
	Service() {
		repoCPU = nullptr;
		repoGPU = nullptr;
		repoMBD = nullptr;
		repoRAM = nullptr;
	}
	Service(RepoCPU* repoCPUG, RepoGPU* repoGPUG, RepoMBD* repoMBDG, RepoRAM* repoRAMG)
	{
		repoCPU = repoCPUG;
		repoGPU = repoGPUG;
		repoMBD = repoMBDG;
		repoRAM = repoRAMG;
	}
	~Service() { }

	//CRUD CPU
	void addCPU(string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG,
		bool coolerG, bool unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG,
		string nameG, int priceG, int stockG);
	void deleteCPU(string cod);
	void updateCPU(string codA, string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG,
		int cacheG, string coolerG, string unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG,
		string nameG, int priceG, int stockG);
	vector<CPU*> readCPU() { return this->repoCPU->getAll(); }
	vector<CPU*> searchCPU(vector<string> keywords);
	vector<CPU*> CPUByPrice();

	//CRUD GPU
	void addGPU(string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int, int> maxResG,
		int busWidthG, int cudaG, string pciEG,
		string nameG, int priceG, int stockG);
	void deleteGPU(string cod);
	void updateGPU(string codA, string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int,
		int> maxResG, int busWidthG, int cudaG, string pciEG,
		string nameG, int priceG, int stockG);
	vector<GPU*> readGPU() { return this->repoGPU->getAll(); }
	vector<GPU*> searchGPU(vector<string> keywords);
	void filterGPU(string memorySpeed, string bus, string cuda);
	vector<GPU*> GPUByPrice();

	//CRUD MOTHERBOARD
	void addMBD(string socketG, pair<string, string> chipsetG, pair<string, int> memoryG, int memorySlotsG,
		map<string, int> connectorsG, map<string, int> pciEG,
		string nameG, int priceG, int stockG);
	void deleteMBD(string cod);
	void updateMBD(string codA, string socketG, pair<string, string> chipsetG, pair<string, int> memoryG,
		int memorySlotsG, map<string, int> connectorsG, map<string, int> pciEG,
		string nameG, int priceG, int stockG);
	vector<Motherboard*> readMBD() { return this->repoMBD->getAll(); }
	vector<Motherboard*> searchMBD(vector<string> keywords);
	vector<Motherboard*> MBDByPrice();

	//CRUD RAM
	void addRAM(int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG,
		string nameG, int priceG, int stockG);
	void deleteRAM(string cod);
	void updateRAM(string codA, int capacityG, string cellTypeG, string memoryTypeG, int memorySpeedG,
		string nameG, int priceG, int stockG);
	vector<RAM*> readRAM() { return this->repoRAM->getAll(); }
	vector<RAM*> searchRAM(vector<string> keywords);
	vector<RAM*> RAMByPrice();

};