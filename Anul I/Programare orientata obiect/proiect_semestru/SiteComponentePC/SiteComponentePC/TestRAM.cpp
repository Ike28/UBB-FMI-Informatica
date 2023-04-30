#include "TestRAM.h"
#include <assert.h>
#include "utils.h"

void TestRAM::testRAM()
{
	/*int capacity;
		string cellType;
		string memoryType;
		int memorySpeed;*/
	RAM r1;
	assert(r1.getCapacity() == 0);
	RAM r2(16, "DRAM", "DDR4", 2133, generateCode(), "Corsair Vengeance", 200, 5000);
	assert(r2.getMemoryType().compare("DDR4") == 0);
	RAM r3(r2);
	assert(r2.getMemorySpeed() == 2133);
}

void TestRAM::runTests()
{
	testRAM();
}
