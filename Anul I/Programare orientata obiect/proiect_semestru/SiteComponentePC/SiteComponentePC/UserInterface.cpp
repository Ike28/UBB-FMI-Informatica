#include "UserInterface.h"
#include "CPUDataException.h"
#include "GPUDataException.h"
#include "RAMDataException.h"
#include "MBDDataException.h"
#include "InvalidIDException.h"
#include <string>
#include <iostream>

using namespace std;

void UI::printMenu()
{
	cout << "\n-----------";
	cout << "\nA. CRUD Procesoare";
	cout << "\nB. CRUD Placi de baza";
	cout << "\nC. CRUD Placi video";
	cout << "\nD. CRUD Placi de memorie RAM";
	cout << "\n\nX---> Oprire";
	cout << "\n-----------";
	cout << "\n\n   Selectati optiunea dorita: ";
}

void UI::printTerminal()
{
	cout << "*** P C   M A D N E S S ***";
	cout << "\n############################";
	cout << "\n\nTERMINAL INVENTAR";
	cout << "\n> ";
}

void UI::printCRUDMenu(string specifier)
{
	cout << "\n------------";
	cout << "\n1. Adaugare " + specifier;
	cout << "\n2. Afisare " + specifier;
	cout << "\n3. Stergere " + specifier;
	cout << "\n4. Update " + specifier;
	cout << "\n\nX. Inapoi";
	cout << "\n------------";
	cout << "\n\n   Selectati optiunea dorita: ";
}

void UI::runCRUDInterface(string specifier, string menuInstance)
{
	system("CLS");
	char option;
	while (1)
	{
		printCRUDMenu(menuInstance);
		cin >> option;
		switch (option)
		{
		case '1':
			this->handleAdd(specifier);
		case '2':
			this->handleShow(specifier);
		case '3':
			break;
		case '4':
			break;
		case 'X':
			return;
		}
	}
}

void UI::handleAdd(string linie)
{
	try {
		int pos = linie.find(" ");
		string specifier = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);
		if (specifier.compare("cpu") == 0)
		{

			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//socket - string
			pos = linie.find(delim);
			string socket = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//threads - int
			pos = linie.find(delim);
			int threads = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cores - int
			pos = linie.find(delim);
			int cores = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//clockSpeed - pair<double,double>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			int poSect = section1.find(",");
			double clock1 = stod(section1.substr(0, poSect));
			section1 = section1.erase(0, poSect + 1);
			double clock2 = stod(section1);

			pair<double, double> clockSpeed = pair<double, double>(clock1, clock2);
			linie = linie.erase(0, pos + 1);

			//cache - int
			pos = linie.find(delim);
			int cache = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cooler - bool
			pos = linie.find(delim);
			bool cooler;
			string c = linie.substr(0, pos);
			if (c.compare("true") == 0)
				cooler = true;
			else cooler = false;
			linie = linie.erase(0, pos + 1);

			//unlocked - bool
			pos = linie.find(delim);
			bool unlocked;
			c = linie.substr(0, pos);
			if (c.compare("true") == 0)
				unlocked = true;
			else unlocked = false;
			linie = linie.erase(0, pos + 1);

			//memory - pair<string,int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(",");
			string mem1 = section2.substr(0, poSect);
			section2 = section2.erase(0, poSect + 1);
			int mem2 = stoi(section2);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//pciE - string
			string pciE = linie;

			this->service->addCPU(socket, threads, cores, clockSpeed, cache, cooler, unlocked, memory, memorySpeed, pciE, name, price, stock);
			cout << "\n\n//Successfully added CPU";
		}
		else if (specifier.compare("mbd") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//socket - string
			pos = linie.find(delim);
			string socket = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//chipset - pair<string, string>
			pos = linie.find(delim);
			string section = linie.substr(0, pos);

			int poSect = section.find(",");
			string chip1 = section.substr(0, poSect);
			section = section.erase(0, poSect + 1);
			string chip2 = section;

			pair<string, string> chipset = pair<string, string>(chip1, chip2);
			linie = linie.erase(0, pos + 1);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			poSect = section1.find(",");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 1);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySlots - int
			pos = linie.find(" ");
			int memorySlots = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//connectors - map<string, int> { PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C }
			map<string, int> connectors;
			delim = "connectors=[";
			pos = linie.find(delim);
			if (pos != -1)
			{
				poSect = linie.find("]");
				string section2 = linie.substr(pos + 12, pos + 29);

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
				linie = linie.erase(0, pos + 30);

			}
			map<string, int> pciE;
			delim = "pcie=[1,1,1]";
			pos = linie.find(delim);
			if (pos != -1)
			{

				string section3 = linie.substr(pos + 6, pos + 12);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("3.0 x16", stoi(section3.substr(0, poSect))));
				section3 = section3.erase(0, poSect + 1);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("2.0 x16", stoi(section3.substr(0, poSect))));
				section3 = section3.erase(0, poSect + 1);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("x1", stoi(section3)));

			}

			this->service->addMBD(socket, chipset, memory, memorySlots, connectors, pciE, name, price, stock);
			cout << "\n\n//Successfully added motherboard";
		}
		else if (specifier.compare("gpu") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//series - string
			pos = linie.find(delim);
			string series = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			int poSect = section1.find(",");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 1);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//maxRes - pair<int, int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(",");
			int res1 = stoi(section2.substr(0, poSect));
			section2 = section2.erase(0, poSect + 1);
			int res2 = stoi(section2);

			pair<int, int> maxRes = pair<int, int>(res1, res2);
			linie = linie.erase(0, pos + 1);

			//busWidth - int
			pos = linie.find(delim);
			int busWidth = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cuda - int
			pos = linie.find(delim);
			int cuda = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//pciE - string
			string pciE = linie;

			this->service->addGPU(series, memory, memorySpeed, maxRes, busWidth, cuda, pciE, name, price, stock);
			cout << "\n\n//Successfully added GPU";

		}
		else if (specifier.compare("ram") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//capacity - int
			pos = linie.find(delim);
			int capacity = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cellType - string
			pos = linie.find(delim);
			string cellType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memoryType - string
			pos = linie.find(delim);
			string memoryType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(" ");
			int memorySpeed = stoi(linie.substr(0, pos));

			this->service->addRAM(capacity, cellType, memoryType, memorySpeed, name, price, stock);
			cout << "\n\n//Successfully added RAM";
		}
		else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
	}
	catch (CPUDataException ce)
	{
		cout << "\n\n//Encountered CPUDataException::" << ce<<"\n--->try again!";
	}
	catch (GPUDataException ge)
	{
		cout << "\n\n//Encountered GPUDataException::" << ge << "\n--->try again!";
	}
	catch (MBDDataException me)
	{
		cout << "\n\n//Encountered MotherboardDataException::" << me << "\n--->try again!";
	}
	catch (RAMDataException re)
	{
		cout << "\n\n//Encountered RAMDataException::" << re << "\n--->try again!";
	}
	catch (...)
	{
		cout << "\n\n//Encountered SyntaxException:: invalid command syntax" << "\n--->try again!";
	}
}

void UI::handleShow(string args)
{
	int pos = args.find(" ");
	string specifier = args.substr(0, pos);
	if (specifier.compare("cpu") == 0)
	{
		vector<CPU*> storage = this->service->readCPU();
		if (storage.size() == 0)
			cout << "\n  Nu exista elemente memorate.";
		for (vector<CPU*>::iterator i = storage.begin(); i != storage.end(); i++)
			cout << '\n' << (*(*i));
		cout << endl;
	}
	else if (specifier.compare("gpu") == 0)
	{
		vector<GPU*> storage = this->service->readGPU();
		if (storage.size() == 0)
			cout << "\n  Nu exista elemente memorate.";
		for (vector<GPU*>::iterator i = storage.begin(); i != storage.end(); i++)
			cout << '\n' << (*(*i));
		cout << endl;
	}
	else if (specifier.compare("mbd") == 0)
	{
		vector<Motherboard*> storage = this->service->readMBD();
		if (storage.size() == 0)
			cout << "\n  Nu exista elemente memorate.";
		for (vector<Motherboard*>::iterator i = storage.begin(); i != storage.end(); i++)
			cout << '\n' << (*(*i));
		cout << endl;
	}
	else if (specifier.compare("ram") == 0)
	{
		vector<RAM*> storage = this->service->readRAM();
		if (storage.size() == 0)
			cout << "\n  Nu exista elemente memorate.";
		for (vector<RAM*>::iterator i = storage.begin(); i != storage.end(); i++)
			cout << '\n' << (*(*i));
		cout << endl;
	}
	else cout << "\n\n//Encountered SyntaxException:: invalid command syntax" << "\n--->try again!";
}

void UI::handleDelete(string linie)
{
	try
	{
		int pos = linie.find(" ");
		string specifier = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);
		pos = linie.find(" ");
		string cod;
		if (pos != -1)
			cod = linie.substr(0, pos),
			linie = linie.erase(0, pos + 1);
		else cod = linie;
		if (specifier.compare("cpu") == 0)
		{
			this->service->deleteCPU(cod);
			cout << "\n\n//Successfully deleted CPU";
		}
		else if (specifier.compare("gpu") == 0)
		{
			this->service->deleteGPU(cod);
			cout << "\n\n//Successfully deleted GPU";
		}
		else if (specifier.compare("mbd") == 0)
		{
			this->service->deleteMBD(cod);
			cout << "\n\n//Successfully deleted motherboard";
		}
		else if (specifier.compare("ram") == 0)
		{
			this->service->deleteRAM(cod);
			cout << "\n\n//Successfully deleted RAM";
		}
		else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
	}
	catch (InvalidIDException ie)
	{
		cout << "\n\n//Encountered InvalidIDException::" << ie << "\n--->try again!";
	}
}

void UI::handleUpdate(string linie)
{
	try {
		int pos = linie.find(" ");
		string specifier = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);
		pos = linie.find(" ");
		string cod = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);
		if (specifier.compare("cpu") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//socket - string
			pos = linie.find(delim);
			string socket = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//threads - int
			pos = linie.find(delim);
			int threads = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cores - int
			pos = linie.find(delim);
			int cores = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//clockSpeed - pair<double,double>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			int poSect = section1.find(",");
			double clock1 = stod(section1.substr(0, poSect));
			section1 = section1.erase(0, poSect + 1);
			double clock2 = stod(section1);

			pair<double, double> clockSpeed = pair<double, double>(clock1, clock2);
			linie = linie.erase(0, pos + 1);

			//cache - int
			pos = linie.find(delim);
			int cache = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cooler - bool
			pos = linie.find(delim);
			string cooler = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//unlocked - bool
			pos = linie.find(delim);
			string unlocked = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memory - pair<string,int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(",");
			string mem1 = section2.substr(0, poSect);
			section2 = section2.erase(0, poSect + 1);
			int mem2 = stoi(section2);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//pciE - string
			string pciE = linie;

			this->service->updateCPU(cod, socket, threads, cores, clockSpeed, cache, cooler, unlocked, memory, memorySpeed, pciE, name, price, stock);

			cout << "\n\n//Successfully updated CPU";

		}
		else if (specifier.compare("gpu") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//series - string
			pos = linie.find(delim);
			string series = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			int poSect = section1.find(",");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 1);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(delim);
			int memorySpeed = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//maxRes - pair<int, int>
			pos = linie.find(delim);
			string section2 = linie.substr(0, pos);

			poSect = section2.find(",");
			int res1 = stoi(section2.substr(0, poSect));
			section2 = section2.erase(0, poSect + 1);
			int res2 = stoi(section2);

			pair<int, int> maxRes = pair<int, int>(res1, res2);
			linie = linie.erase(0, pos + 1);

			//busWidth - int
			pos = linie.find(delim);
			int busWidth = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cuda - int
			pos = linie.find(delim);
			int cuda = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//pciE - string
			string pciE = linie;

			this->service->updateGPU(cod, series, memory, memorySpeed, maxRes, busWidth, cuda, pciE, name, price, stock);
			cout << "\n\n//Successfully updated GPU";
		}
		else if (specifier.compare("mbd") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//socket - string
			pos = linie.find(delim);
			string socket = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//chipset - pair<string, string>
			pos = linie.find(delim);
			string section = linie.substr(0, pos);

			int poSect = section.find(",");
			string chip1 = section.substr(0, poSect);
			section = section.erase(0, poSect + 1);
			string chip2 = section;

			pair<string, string> chipset = pair<string, string>(chip1, chip2);
			linie = linie.erase(0, pos + 1);

			//memory - pair<string, int>
			pos = linie.find(delim);
			string section1 = linie.substr(0, pos);

			poSect = section1.find(",");
			string mem1 = section1.substr(0, poSect);
			section1 = section1.erase(0, poSect + 1);
			int mem2 = stoi(section1);

			pair<string, int> memory = pair<string, int>(mem1, mem2);
			linie = linie.erase(0, pos + 1);

			//memorySlots - int
			pos = linie.find(" ");
			int memorySlots = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//connectors - map<string, int> { PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C }
			map<string, int> connectors;
			delim = "connectors=[";
			pos = linie.find(delim);
			if (pos != -1)
			{
				poSect = linie.find("]");
				string section2 = linie.substr(pos + 12, pos + 29);

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
				linie = linie.erase(0, pos + 30);

			}
			map<string, int> pciE;
			delim = "pcie=[1,1,1]";
			pos = linie.find(delim);
			if (pos != -1)
			{

				string section3 = linie.substr(pos + 6, pos + 12);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("3.0 x16", stoi(section3.substr(0, poSect))));
				section3 = section3.erase(0, poSect + 1);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("2.0 x16", stoi(section3.substr(0, poSect))));
				section3 = section3.erase(0, poSect + 1);

				poSect = section3.find(",");
				pciE.insert(pair<string, int>("x1", stoi(section3)));

			}
			this->service->updateMBD(cod, socket, chipset, memory, memorySlots, connectors, pciE, name, price, stock);

			cout << "\n\n//Successfully updated motherboard";
		}
		else if (specifier.compare("ram") == 0)
		{
			string delim = "/";
			//name
			pos = linie.find(delim);
			string name = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//price
			pos = linie.find(delim);
			int price = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//stock
			pos = linie.find(delim);
			int stock = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//capacity - int
			pos = linie.find(delim);
			int capacity = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 1);

			//cellType - string
			pos = linie.find(delim);
			string cellType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memoryType - string
			pos = linie.find(delim);
			string memoryType = linie.substr(0, pos);
			linie = linie.erase(0, pos + 1);

			//memorySpeed - int
			pos = linie.find(" ");
			int memorySpeed = stoi(linie.substr(0, pos));

			this->service->updateRAM(cod, capacity, cellType, memoryType, memorySpeed, name, price, stock);

			cout << "\n\n//Successfully updated RAM";
		}
		else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
	}
	catch (CPUDataException ce)
	{
		cout << "\n\n//Encountered CPUDataException::" << ce << "\n--->try again!";
	}
	catch (GPUDataException ge)
	{
		cout << "\n\n//Encountered GPUDataException::" << ge << "\n--->try again!";
	}
	catch (MBDDataException me)
	{
		cout << "\n\n//Encountered MotherboardDataException::" << me << "\n--->try again!";
	}
	catch (RAMDataException re)
	{
		cout << "\n\n//Encountered RAMDataException::" << re << "\n--->try again!";
	}
	catch (InvalidIDException ie)
	{
		cout << "\n\n//Encountered InvalidIDException::" << ie << "\n--->try again!";
	}
	catch (...)
	{
		cout << "\n\n//Encountered SyntaxException:: invalid command syntax" << "\n--->try again!";
	}
}

void UI::handleSearch(string linie)
{
	int pos = linie.find(" ");
	string specifier = linie.substr(0, pos);
	linie = linie.erase(0, pos + 1);
	vector<string>keywords;
	pos = linie.find(" ");
	while (pos != -1)
	{
		keywords.push_back(linie.substr(0, pos));
		linie = linie.erase(0, pos + 1);
		pos = linie.find(" ");
	}
	keywords.push_back(linie);
	if (specifier.compare("cpu") == 0)
	{
		
		vector<CPU*> results = this->service->searchCPU(keywords);
		if (results.size() > 0)
		{
			for (vector<CPU*>::iterator i = results.begin(); i != results.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n No matching entries found.";
	}
	else if (specifier.compare("gpu") == 0)
	{
		vector<GPU*> results = this->service->searchGPU(keywords);
		if (results.size() > 0)
		{
			for (vector<GPU*>::iterator i = results.begin(); i != results.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n No matching entries found.";
	}
	else if (specifier.compare("mbd") == 0)
	{
		vector<Motherboard*> results = this->service->searchMBD(keywords);
		if (results.size() > 0)
		{
			for (vector<Motherboard*>::iterator i = results.begin(); i != results.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n No matching entries found.";
	}
	else if (specifier.compare("ram") == 0)
	{
		vector<RAM*> results = this->service->searchRAM(keywords);
		if (results.size() > 0)
		{
			for (vector<RAM*>::iterator i = results.begin(); i != results.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n No matching entries found.";
	}
	else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
}

void UI::handleFilter(string linie)
{
	try
	{
		int pos = linie.find(" ");
		string specifier = linie.substr(0, pos);
		linie = linie.erase(0, pos + 1);
		if (specifier.compare("gpu") == 0)
		{
			string speed = "", bus = "", cuda = "";

			pos = linie.find("speed");
			if (pos != -1)
			{
				linie = linie.erase(0, pos + 5);
				pos = linie.find(" ");
				string section = linie.substr(0, pos);
				if (section[0] == '>' || section[0] == '=' || section[0] == '<')
					speed += section[0] + to_string(stoi(section.substr(1, section.size())));
				else throw;
				linie = linie.erase(0, pos + 1);
			}
			else speed = ">0";

			pos = linie.find("bus");
			if (pos != -1)
			{
				linie = linie.erase(0, pos + 3);
				pos = linie.find(" ");
				string section = linie.substr(0, pos);
				if (section[0] == '>' || section[0] == '=' || section[0] == '<')
					bus += section[0] + to_string(stoi(section.substr(1, section.size())));
				else throw;
				linie = linie.erase(0, pos + 1);
			}
			else bus = ">0";

			pos = linie.find("cuda");
			if (pos != -1)
			{
				linie = linie.erase(0, pos + 4);
				pos = linie.find(" ");
				string section = linie.substr(0, pos);
				string speed = "";
				if (section[0] == '>' || section[0] == '=' || section[0] == '<')
					cuda += section[0] + to_string(stoi(section.substr(1, section.size())));
				else throw;
				linie = linie.erase(0, pos + 1);
			}
			else cuda = ">0";

			this->service->filterGPU(speed, bus, cuda);

			cout << "\n\n//Successfully filtered";

		}
		else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
	}
	catch (...)
	{

	}
}

void UI::handleSort(string linie)
{
	int pos = linie.find(" ");
	string specifier = linie.substr(0, pos);
	linie = linie.erase(0, pos + 1);
	if (specifier.compare("ram") == 0)
	{
		vector<RAM*> result = this->service->RAMByPrice();
		if (result.size() > 0)
		{
			for (vector<RAM*>::iterator i = result.begin(); i != result.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n   No entries.";
	}
	else if (specifier.compare("gpu") == 0)
	{
		vector<GPU*> result = this->service->GPUByPrice();
		if (result.size() > 0)
		{
			for (vector<GPU*>::iterator i = result.begin(); i != result.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n   No entries.";
	}
	else if (specifier.compare("mbd") == 0)
	{
		vector<Motherboard*> result = this->service->MBDByPrice();
		if (result.size() > 0)
		{
			for (vector<Motherboard*>::iterator i = result.begin(); i != result.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n   No entries.";
	}
	else if (specifier.compare("cpu") == 0)
	{
		vector<CPU*> result = this->service->CPUByPrice();
		if (result.size() > 0)
		{
			for (vector<CPU*>::iterator i = result.begin(); i != result.end(); i++)
				cout << '\n' << (*(*i));
		}
		else cout << "\n\n   No entries.";
	}
	else cout << "\n\n//Encountered SpecifierException:: invalid specifier (current is " + specifier << "\n--->try again!";
}

void UI::handleHelp()
{
	cout << "\n---------";
	cout << "\nCOMMANDS:";
	cout << "\n   add cpu name(str)/price(int)/stock(int)/socket(str)/threads(int)/cores(int)/clockSpeedbase(double),turbo(double)/cache(int)/cooler(bool)/unlocked(bool)/memoryType(str),memMaxCap(int)/memorySpeed(int)/pciE(str)";
	cout << "\n   add mbd name(str)/price(int)/stock(int)/socket(str)/chipsetMan(str),chipModel(str)/memoryType(str),memMax(int)/memSlots(int) connectors=[...] (optional) pcie=[...] (optional)";
	cout << "\n   add gpu name(str)/price(int)/stock(int)/series(str)/memType(str),memCap(int)/memSpeed(int)/maxRes(int,int)/bus(int)/cuda(int)/pciE(str)";
	cout << "\n   add ram name/price/stock/cap(int)/cellType(str)/memType(str)/memSpeed(int)";
	cout << "\n   delete specifier id";
	cout << "\n   show specifier";
	cout << "\n   update specifier [add args] (replace numerical values with -1 if not updating)";
	cout << "\n   ---> where specifier = [cpu, gpu, mbd, ram]";
	cout << "\n   filter gpu speedXval (optional) busXval (optional) cudaXval (optional) ";
	cout << "\n   ---> where X = [>,=,<]";
	cout << "\n   sort specifier";
	cout << "\n   search specifier [keywords] (separate keywords by spaces)";
	cout << "\n   ---> where specifier as above";
	cout << "\n   stop";
	cout << "\n\n";
}


void UI::runInterface()
{
	system("CLS");
	char option; string command;
	while (1)
	{
		//printMenu();
		printTerminal();
		getline(cin, command);
		int pos = command.find(" ");
		string commType = command.substr(0, pos);
		command = command.erase(0, pos + 1);

		if (commType.compare("add") == 0)
			handleAdd(command);
		else if (commType.compare("show") == 0)
			handleShow(command);
		else if (commType.compare("delete") == 0)
			handleDelete(command);
		else if (commType.compare("update") == 0)
			handleUpdate(command);
		else if (commType.compare("stop") == 0)
			return;
		else if (commType.compare("search") == 0)
			handleSearch(command);
		else if (commType.compare("filter") == 0)
			handleFilter(command);
		else if (commType.compare("sort") == 0)
			handleSort(command);
		else if (commType.compare("help") == 0)
			handleHelp();
		else cout << "\n\n//Encountered SyntaxException:: invalid command syntax" << "\n--->try again!";
	}
}
