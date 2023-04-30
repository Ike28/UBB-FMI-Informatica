#pragma once
#include "RepoFile.h"
#include "RAM.h"
#include <vector>

class RepoRAM : public RepoFile
{
private:
	vector<RAM*> storage;
	void loadFromFile();
	void writeToFile();
public:
	RepoRAM() : RepoFile() { }
	RepoRAM(string filenameGiven) : RepoFile(filenameGiven) { loadFromFile(); }
	~RepoRAM();

	vector<RAM*> getAll() { return storage; }
	RAM* findByID(string cod);
	void add(RAM* newObj);
	void deleteByID(string ID);
	void updateByID(string ID, RAM* newObj);
};
