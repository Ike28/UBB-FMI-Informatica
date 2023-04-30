#include "TestCPU.h"
#include <assert.h>
#include "utils.h"

void TestCPU::testCPU()
{
	/*string socket;
		int threads;
		int cores;
		pair<double, double> clockSpeed; // first - base speed ; second - turbo speed (matches base if none)
		int cache;
		bool cooler;
		bool unlocked;
		pair<string, int> memory; // first - memory type supported ; second - max capacity supported
		int memorySpeed;
		string pciE;*/
	CPU c1;
	assert(c1.getCache() == 0 && c1.getMemoryData().first.compare("") == 0);
	CPU c2("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", generateCode(), "intel i7", 1000, 200);
	assert(c2.getSocket().compare("1151") == 0);
	CPU c3(c2);
	assert(c2.getCores() == 8);
}

void TestCPU::runTests()
{
	testCPU();
}
