#include "TestMotherboard.h"
#include <assert.h>
#include "utils.h"

void TestMBD::testMBD()
{
	/*string socket;
		pair<string, string> chipset; // first - chipset manufacturer ; second - chipset model
		pair<string, int> memory; // first - memory type supported ; second - max capacity
		int memorySlots;
		map<string, int> connectors; // PS/2, DVI, HDMI, USB 2.0, USB 3.0, LAN, VGA, USB 3.1 A, USB 3.1 C
		map<string, int> pciE; // 3.0 x16, 2.0 x16, x1*/
	Motherboard m1;
	assert(m1.getSocket().compare("") == 0);
	Motherboard m2("1151", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), generateCode(), "ASRock 7", 500, 200);
	assert(m2.getSocket().compare("1151") == 0);
	Motherboard m3(m2);
	assert(m2.getMemorySlots() == 4);
}

void TestMBD::runTests()
{
	testMBD();
}
