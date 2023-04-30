#include "TestRepoGPU.h"
#include "RepoGPU.h"
#include <assert.h>
#include <vector>
#include <fstream>
#include "utils.h"

void TestRepoGPU::testRepo()
{
	/*string series;
		pair<string, int> memory; // first - memory type (DDRX) ; second - capacity
		int memorySpeed;
		pair<int, int> maxRes;
		int busWidth;
		int cuda;
		string pciE;*/
	ofstream f("test_file2.txt");
	f.close();
	RepoGPU r1;
	assert(r1.getFilename().compare("") == 0);

	RepoGPU r2("test_file2.txt");
	assert(r2.getFilename().compare("test_file2.txt") == 0);
}

void TestRepoGPU::testAdd()
{
	ofstream f("test_file2.txt");
	f.close();
	RepoGPU r1("test_file2.txt");
	GPU* x = new GPU("900", pair<string,int>("DDR4",4), 3000, pair<int,int>(1920,1080), 128, 4000, "3.0 x16", generateCode(), "nVIDIA GTX 960", 900, 400);
	r1.add(x);
	vector<GPU*> storage = r1.getAll();
	assert((*storage[0]).getSeries().compare("900") == 0);
}

void TestRepoGPU::testDelete()
{
	ofstream f("test_file2.txt");
	f.close();
	RepoGPU r1("test_file2.txt");
	GPU* x = new GPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", generateCode(), "nVIDIA GTX 960", 900, 400);
	r1.add(x);
	vector<GPU*> storage = r1.getAll();
	assert(storage.size() == 1);
	RepoGPU r3("test_file2.txt");
	assert(r3.getAll().size() == 1);

	r1.deleteByID(storage[0]->getCode());
	storage = r1.getAll();
	assert(storage.size() == 0);
	RepoGPU r2("test_file2.txt");
	assert(r2.getAll().size() == 0);

}

void TestRepoGPU::testUpdate()
{
	ofstream f("test_file2.txt");
	f.close();
	RepoGPU r1("test_file2.txt");
	GPU* x = new GPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", generateCode(), "nVIDIA GTX 960", 900, 400);
	r1.add(x);
	GPU* y = new GPU("1000", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", r1.getAll()[0]->getCode(), "nVIDIA GTX 960", 900, 400);
	r1.updateByID(r1.getAll()[0]->getCode(), y);

	RepoGPU r2("test_file2.txt");
	assert(r2.getAll()[0]->getSeries().compare("1000") == 0);
}

void TestRepoGPU::runTests()
{
	testRepo();
	testAdd();
	testDelete();
	testUpdate();
}
