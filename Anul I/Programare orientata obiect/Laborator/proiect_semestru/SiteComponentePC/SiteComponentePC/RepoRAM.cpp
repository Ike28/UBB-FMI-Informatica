#include "RepoRAM.h"
#include <fstream>

void RepoRAM::loadFromFile()
{
	ifstream f(this->filename);
	if (f.is_open())
	{
		vector<RAM*> vEmpty;
		storage = vEmpty;
		string linie;
		string delim = " | ";

		while (getline(f, linie))
		{
			//RAM
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

			//capacity - int
			pos = linie.find(delim);
			int capacity = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//cellType - string
			pos = linie.find(delim);
			string cellType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//memoryType - string
			pos = linie.find(delim);
			string memoryType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//memorySpeed - int
			int memorySpeed = stoi(linie);

			RAM* newObj = new RAM(capacity, cellType, memoryType, memorySpeed, cod, name, price, stock);
			vEmpty.push_back(newObj);
		}
		storage = vEmpty;
		f.close();
	}
}

void RepoRAM::writeToFile()
{
	ofstream f(this->filename);
	if (f.is_open())
	{
		for (int i = 0; i < storage.size(); i++)
			f << (*storage[i]) << endl;
	}
}

RepoRAM::~RepoRAM()
{
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
		delete (*i);
	RepoFile::~RepoFile();
}

RAM* RepoRAM::findByID(string cod)
{
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
		if ((*i)->getCode().compare(cod) == 0)
			return (*i);
	return nullptr;
}

void RepoRAM::add(RAM* newObj)
{
	storage.push_back(newObj);
	writeToFile();
}

void RepoRAM::deleteByID(string ID)
{
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			storage.erase(i);
			writeToFile();
			return;
		}
	}
}

void RepoRAM::updateByID(string ID, RAM* newObj)
{
	for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			(*i) = newObj;
			writeToFile();
		}
	}
}
