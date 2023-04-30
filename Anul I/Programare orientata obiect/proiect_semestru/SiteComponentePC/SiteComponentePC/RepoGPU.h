#pragma once
#include "RepoFile.h"
#include "GPU.h"
#include <vector>

class RepoGPU : public RepoFile
{
private:
	vector<GPU*> storage;
	void loadFromFile();
	void writeToFile();
public:
	RepoGPU() : RepoFile() { }
	RepoGPU(string filenameGiven) : RepoFile(filenameGiven) { loadFromFile(); }
	~RepoGPU();

	vector<GPU*> getAll() { return storage; }
	GPU* findByID(string cod);
	void add(GPU* newObj);
	void deleteByID(string ID);
	void updateByID(string ID, GPU* newObj);
};
