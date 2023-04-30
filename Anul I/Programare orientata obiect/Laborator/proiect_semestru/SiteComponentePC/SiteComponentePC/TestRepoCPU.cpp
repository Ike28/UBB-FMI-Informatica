#include "TestRepoCPU.h"
#include "RepoCPU.h"
#include <assert.h>
#include <vector>
#include <fstream>
#include "utils.h"

void TestRepoCPU::testRepo()
{
	ofstream f("test_file1.txt");
	f.close();
	RepoCPU r1;
	assert(r1.getFilename().compare("") == 0);

	RepoCPU r2("test_file1.txt");
	assert(r2.getFilename().compare("test_file1.txt") == 0);
}

void TestRepoCPU::testAdd()
{
	ofstream f("test_file1.txt");
	f.close();
	RepoCPU r1("test_file1.txt");
	CPU* x = new CPU("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", generateCode(), "intel i7", 1000, 200);
	r1.add(x);
	vector<CPU*> storage = r1.getAll();
	assert((*storage[0]).getSocket().compare("1151") == 0);
}

void TestRepoCPU::testDelete()
{
	ofstream f("test_file1.txt");
	f.close();
	RepoCPU r1("test_file1.txt");
	CPU* x = new CPU("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", generateCode(), "intel i7", 1000, 200);
	r1.add(x);
	vector<CPU*> storage = r1.getAll();
	assert(storage.size() == 1);
	RepoCPU r3("test_file1.txt");
	assert(r3.getAll().size() == 1);

	r1.deleteByID(storage[0]->getCode());
	storage = r1.getAll();
	assert(storage.size() == 0);
	RepoCPU r2("test_file1.txt");
	assert(r2.getAll().size() == 0);

}

void TestRepoCPU::testUpdate()
{
	ofstream f("test_file1.txt");
	f.close();
	RepoCPU r1("test_file1.txt");
	CPU* x = new CPU("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", generateCode(), "intel i7", 1000, 200);
	r1.add(x);
	CPU* y = new CPU("2021", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", r1.getAll()[0]->getCode(), "intel i7", 1000, 200);
	r1.updateByID(r1.getAll()[0]->getCode(), y);
	
	RepoCPU r2("test_file1.txt");
	assert(r2.getAll()[0]->getSocket().compare("2021") == 0);
}

void TestRepoCPU::runTests()
{
	testRepo();
	testAdd();
	testDelete();
	testUpdate();
}
