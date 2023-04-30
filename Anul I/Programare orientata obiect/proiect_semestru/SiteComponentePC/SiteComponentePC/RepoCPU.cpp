#include "RepoCPU.h"
#include <fstream>

void RepoCPU::loadFromFile()
{
	ifstream f(this->filename);
	if (f.is_open())
	{
		vector<CPU*> vEmpty;
		storage = vEmpty;
		string linie;
		string delim = " | ";

		while (getline(f, linie))
		{
			//CPU
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

			//socket - string
			pos = linie.find(delim);
			string socket = linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			//threads - int
			pos = linie.find(delim);
			int threads = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//cores - int
			pos = linie.find(delim);
			int cores = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);
			
			//clockSpeed - pair<double,double>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);
			
			int poSect = section1.find(" , ");
			double clock1 = stod(section1.substr(0, poSect));
			section1 = section1.erase(0, poSect + 3);
			double clock2 = stod(section1);

			pair<double, double> clockSpeed = pair<double, double>(clock1, clock2);
			linie = linie.erase(0, pos + 3);

			//cache - int
			pos = linie.find(delim);
			int cache = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//cooler - bool
			pos = linie.find(delim);
			bool cooler;
			string c = linie.substr(0, pos);
			if (c.compare("1") == 0)
				cooler = true;
			else cooler = false;
			linie = linie.erase(0, pos + 3);
			
			//unlocked - bool
			pos = linie.find(delim);
			bool unlocked;
			c = linie.substr(0, pos);
			if (c.compare("1") == 0)
				unlocked = true;
			else unlocked = false;
			linie = linie.erase(0, pos + 3);

			//memory - pair<string,int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(" , ");
			string mem1 = section2.substr(0, poSect);
			section2 = section2.erase(0, poSect + 3);
			int mem2 = stoi(section2);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 3);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//pciE - string
			string pciE= linie.substr(0, pos);
			linie = linie.erase(0, pos + 3);

			CPU* newObj = new CPU(socket, threads, cores, clockSpeed, cache, cooler, unlocked, memory, memorySpeed, pciE, cod, name, price, stock);
			vEmpty.push_back(newObj);
		}
		storage = vEmpty;
		f.close();
	}
}

void RepoCPU::writeToFile()
{
	ofstream f(this->filename);
	if (f.is_open())
	{
		for (int i = 0; i < storage.size(); i++)
			f << (*storage[i]) << endl;
	}
}

RepoCPU::~RepoCPU()
{
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		delete (*i);
	RepoFile::~RepoFile();
}

CPU* RepoCPU::findByID(string cod)
{
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
		if ((*i)->getCode().compare(cod) == 0)
			return (*i);
	return nullptr;
}

void RepoCPU::add(CPU* newObj)
{
	storage.push_back(newObj);
	writeToFile();
}

void RepoCPU::deleteByID(string ID)
{
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			storage.erase(i);
			writeToFile();
			return;
		}
	}
}

void RepoCPU::updateByID(string ID, CPU* newObj)
{
	for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			(*i) = newObj;
			writeToFile();
		}
	}
}
