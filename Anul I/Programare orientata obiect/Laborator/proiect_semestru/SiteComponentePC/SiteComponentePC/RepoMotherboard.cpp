#include "RepoMotherboard.h"
#include <fstream>

void RepoMBD::loadFromFile()
{
	ifstream f(this->filename);
	if (f.is_open())
	{
		vector<Motherboard*> vEmpty;
		storage = vEmpty;
		string linie;
		string delim = " | ";

		while (getline(f, linie))
		{
			//MBD
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

			//chipset - pair<string, string>
			pos = linie.find(delim);
			string section = linie.substr(0, pos);

			int poSect = section.find(" , ");
			string chip1 = section.substr(0, poSect);
			section = section.erase(0, poSect + 3);
			string chip2 = section;

			pair<string, string> chipset = pair<string, string>(chip1, chip2);
			linie = linie.erase(0, pos + 3);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			poSect = section1.find(" , ");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 3);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 3);

			//memorySlots - int
			pos = linie.find(delim);
			int memorySlots = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			//connectors - map<string, int> { PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C }
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			map<string, int> connectors;

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("PS/2", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("DVI", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("HDMI", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("USB 2.0", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("USB 3.0", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("LAN", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("VGA", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			poSect = section2.find(",");
			connectors.insert(pair<string, int>("USB 3.1 A", stoi(section2.substr(0, poSect))));
			section2 = section2.erase(0, poSect + 1);

			connectors.insert(pair<string, int>("USB 3.1 C", stoi(section2)));
			section2 = section2.erase(0, poSect + 1);


			linie = linie.erase(0, pos + 3);

			//pciE - map<string, int> { 3.0 x16, 2.0 x16, x1 }
			pos = linie.find(delim);
			string section3 = linie.substr(0, pos);

			map<string, int> pciE;

			poSect = section3.find(",");
			pciE.insert(pair<string, int>("3.0 x16", stoi(section3.substr(0, poSect))));
			section3 = section3.erase(0, poSect + 1);

			poSect = section3.find(",");
			pciE.insert(pair<string, int>("2.0 x16", stoi(section3.substr(0, poSect))));
			section3 = section3.erase(0, poSect + 1);

			poSect = section3.find(",");
			pciE.insert(pair<string, int>("x1", stoi(section3.substr(0, poSect))));
			section3 = section3.erase(0, poSect + 1);

			linie = linie.erase(0, pos + 3);

			Motherboard* newObj = new Motherboard(socket, chipset, memory, memorySlots, connectors, pciE, cod, name, price, stock);
			vEmpty.push_back(newObj);
		}
		storage = vEmpty;
		f.close();
	}
}

void RepoMBD::writeToFile()
{
	ofstream f(this->filename);
	if (f.is_open())
	{
		for (int i = 0; i < storage.size(); i++)
			f << (*storage[i]) << endl;
	}
}

RepoMBD::~RepoMBD()
{
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
		delete (*i);
	RepoFile::~RepoFile();
}

Motherboard* RepoMBD::findByID(string cod)
{
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
		if ((*i)->getCode().compare(cod) == 0)
			return (*i);
	return nullptr;
}

void RepoMBD::add(Motherboard* newObj)
{
	storage.push_back(newObj);
	writeToFile();
}

void RepoMBD::deleteByID(string ID)
{
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			storage.erase(i);
			writeToFile();
			return;
		}
	}
}

void RepoMBD::updateByID(string ID, Motherboard* newObj)
{
	for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
	{
		if ((*(*i)).getCode() == ID)
		{
			(*i) = newObj;
			writeToFile();
		}
	}
}
