#include "TestRepoMBD.h"
#include "RepoMotherboard.h"
#include <assert.h>
#include <vector>
#include <fstream>
#include "utils.h"

void TestRepoMBD::testRepo()
{
	/*string socket;
		pair<string, string> chipset; // first - chipset manufacturer ; second - chipset model
		pair<string, int> memory; // first - memory type supported ; second - max capacity
		int memorySlots;
		map<string, int> connectors; // PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C
		map<string, int> pciE; // 3.0 x16, 2.0 x16, x1*/
	ofstream f("test_file4.txt");
	f.close();
	RepoMBD r1;
	assert(r1.getFilename().compare("") == 0);

	RepoMBD r2("test_file4.txt");
	assert(r2.getFilename().compare("test_file4.txt") == 0);
}

void TestRepoMBD::testAdd()
{
	ofstream f("test_file4.txt");
	f.close();
	RepoMBD r1("test_file4.txt");
	Motherboard* x = new Motherboard("1151", pair<string,string>("Intel","BG50"), pair<string,int>("DDR4", 128), 4, map<string,int>(), map<string,int>(), generateCode(), "ASRock 7", 500, 200);
	r1.add(x);
	vector<Motherboard*> storage = r1.getAll();
	assert((*storage[0]).getChipsetData().first.compare("Intel") == 0);
}

void TestRepoMBD::testDelete()
{
	ofstream f("test_file4.txt");
	f.close();
	RepoMBD r1("test_file4.txt");
	Motherboard* x = new Motherboard("1151", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), generateCode(), "ASRock 7", 500, 200);
	r1.add(x);
	vector<Motherboard*> storage = r1.getAll();
	assert(storage.size() == 1);
	RepoMBD r3("test_file4.txt");
	assert(r3.getAll().size() == 1);

	r1.deleteByID(storage[0]->getCode());
	storage = r1.getAll();
	assert(storage.size() == 0);
	RepoMBD r2("test_file4.txt");
	assert(r2.getAll().size() == 0);

}

void TestRepoMBD::testUpdate()
{
	ofstream f("test_file4.txt");
	f.close();
	RepoMBD r1("test_file4.txt");
	Motherboard* x = new Motherboard("1151", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), generateCode(), "ASRock 7", 500, 200);
	r1.add(x);
	Motherboard* y = new Motherboard("1149", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), r1.getAll()[0]->getCode(), "ASRock 9", 500, 200);
	r1.updateByID(r1.getAll()[0]->getCode(), y);

	RepoMBD r2("test_file4.txt");
	assert(r2.getAll()[0]->getSocket().compare("1149") == 0);
}

void TestRepoMBD::runTests()
{
	testRepo();
	testAdd();
	testDelete();
	testUpdate();
}
