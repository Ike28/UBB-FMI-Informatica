#pragma once
#include "RepoFile.h"
#include "CPU.h"
#include <vector>

class RepoCPU : public RepoFile
{
	private:
		vector<CPU*> storage;
		void loadFromFile();
		void writeToFile();
	public:
		RepoCPU() : RepoFile() { }
		RepoCPU(string filenameGiven) : RepoFile(filenameGiven) { loadFromFile(); }
		~RepoCPU();

		vector<CPU*> getAll() { return storage; }
		CPU* findByID(string cod);
		void add(CPU* newObj);
		void deleteByID(string ID);
		void updateByID(string ID, CPU* newObj);
};
