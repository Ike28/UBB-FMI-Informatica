#pragma once
#include "RepoFile.h"
#include "Motherboard.h"
#include <vector>

class RepoMBD : public RepoFile
{
	private:
		vector<Motherboard*> storage;
		void loadFromFile();
		void writeToFile();
	public:
		RepoMBD() : RepoFile() { }
		RepoMBD(string filenameGiven) : RepoFile(filenameGiven) { loadFromFile(); }
		~RepoMBD();

		vector<Motherboard*> getAll() { return storage; }
		Motherboard* findByID(string cod);
		void add(Motherboard* newObj);
		void deleteByID(string ID);
		void updateByID(string ID, Motherboard* newObj);
};
