#include "TestRepoRAM.h"
#include "RepoRAM.h"
#include <assert.h>
#include <vector>
#include <fstream>
#include "utils.h"

void TestRepoRAM::testRepo()
{
	/*int capacity;
		string cellType;
		string memoryType;
		int memorySpeed;*/
	ofstream f("test_file3.txt");
	f.close();
	RepoRAM r1;
	assert(r1.getFilename().compare("") == 0);

	RepoRAM r2("test_file3.txt");
	assert(r2.getFilename().compare("test_file3.txt") == 0);
}

void TestRepoRAM::testAdd()
{
	ofstream f("test_file3.txt");
	f.close();
	RepoRAM r1("test_file3.txt");
	RAM* x = new RAM(16, "DRAM", "DDR4", 2133, generateCode(), "Corsair Vengeance", 200, 5000);
	r1.add(x);
	vector<RAM*> storage = r1.getAll();
	assert((*storage[0]).getCapacity() == 16);
}

void TestRepoRAM::testDelete()
{
	ofstream f("test_file3.txt");
	f.close();
	RepoRAM r1("test_file3.txt");
	RAM* x = new RAM(16, "DRAM", "DDR4", 2133, generateCode(), "Corsair Vengeance", 200, 5000);
	r1.add(x);
	vector<RAM*> storage = r1.getAll();
	assert(storage.size() == 1);
	RepoRAM r3("test_file3.txt");
	assert(r3.getAll().size() == 1);

	r1.deleteByID(storage[0]->getCode());
	storage = r1.getAll();
	assert(storage.size() == 0);
	RepoRAM r2("test_file3.txt");
	assert(r2.getAll().size() == 0);

}

void TestRepoRAM::testUpdate()
{
	ofstream f("test_file3.txt");
	f.close();
	RepoRAM r1("test_file3.txt");
	RAM* x = new RAM(16, "DRAM", "DDR4", 2133, generateCode(), "Corsair Vengeance", 200, 5000);
	r1.add(x);
	RAM* y = new RAM(32, "SRAM", "DDR4", 2133, r1.getAll()[0]->getCode(), "Corsair Vengeance", 200, 5000);
	r1.updateByID(r1.getAll()[0]->getCode(), y);

	RepoRAM r2("test_file3.txt");
	assert(r2.getAll()[0]->getCellType().compare("SRAM") == 0);
}

void TestRepoRAM::runTests()
{
	testRepo();
	testAdd();
	testDelete();
	testUpdate();
}
