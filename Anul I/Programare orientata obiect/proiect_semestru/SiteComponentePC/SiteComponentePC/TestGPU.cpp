#include "TestGPU.h"
#include <assert.h>
#include "utils.h"

void TestGPU::testGPU()
{
	/*string socket;
		string series;
		pair<string, int> memory; // first - memory type (DDRX) ; second - capacity
		int memorySpeed;
		pair<int, int> maxRes;
		int busWidth;
		int cuda;
		string pciE;*/
	GPU g1;
	assert(g1.getSeries().compare("") == 0);
	GPU g2("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", generateCode(), "nVIDIA GTX 960", 900, 400);
	assert(g2.getMemorySpeed() == 3000);
	GPU g3(g2);
	assert(g2.getBusWidth() == 128);
}

void TestGPU::runTests()
{
	testGPU();
}
