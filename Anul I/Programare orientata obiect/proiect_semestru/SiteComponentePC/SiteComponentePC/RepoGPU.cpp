#include "RepoGPU.h"
#include <fstream>

void RepoGPU::loadFromFile()
{
	ifstream f(this->filename);
	if (f.is_open())
	{
		vector<GPU*> vEmpty;
		storage = vEmpty;
		string linie;
		string delim = " | ";

		while (getline(f, linie))
		{
			//GPU
			int pos = linie.find(delim);
			linie = linie.erase(0, pos + 3);

			//cod
			pos = linie.find(delim);
			string cod = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//series - string
			pos = linie.find(delim);
			string series = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			int poSect = section1.find(" , ");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 3);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 3);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//maxRes - pair<int, int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(" , ");
			int res1 = stoi(section2.substr(0, poSect));
			section2 = section2.erase(0, poSect + 3);
			int res2 = stoi(section2);

			pair<int, int> maxRes = pair<int, int>(res1, res2);
			linie = linie.erase(0, pos + 3);

			//busWidth - int
			pos = linie.find(delim);
			int busWidth = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//cuda - int
			pos = linie.find(delim);
			int cuda = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//pciE - string
			string pciE = linie;

			GPU* newObj = new GPU(series, memory, memorySpeed, maxRes, busWidth, cuda, pciE, cod, name, price, stock);
			vEmpty.push_back(newObj);
		}
		storage = vEmpty;
		f.close();
	}
}

void RepoGPU::writeToFile()
{
	ofstream f(this->filename);
	if (f.is_open())
	{
		for (int i = 0; i < storage.size(); i++)
			f << (*storage[i]) << endl;
	}
}

RepoGPU::~RepoGPU()
{
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		delete (*i);
	RepoFile::~RepoFile();
}

GPU* RepoGPU::findByID(string cod)
{
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		if ((*i)->getCode().compare(cod) == 0)
			return (*i);
	return nullptr;
}

void RepoGPU::add(GPU* newObj)
{
	storage.push_back(newObj);
	writeToFile();
}

void RepoGPU::deleteByID(string ID)
{
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			storage.erase(i);
			writeToFile();
			return;
		}
	}
}

void RepoGPU::updateByID(string ID, GPU* newObj)
{
	for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			(*i) = newObj;
			writeToFile();
		}
	}
}
