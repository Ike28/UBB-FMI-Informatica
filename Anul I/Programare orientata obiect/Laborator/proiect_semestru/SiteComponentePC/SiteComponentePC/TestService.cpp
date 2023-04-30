#include "TestService.h"
#include "Service.h"
#include "RepoCPU.h"
#include "RepoMotherboard.h"
#include "RepoRAM.h"
#include "RepoGPU.h"
#include <fstream>
#include <assert.h>

void TestService::testCRUDCPU()
{
	/*addCPU(string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG, int cacheG,
		bool coolerG, bool unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG,
		string nameG, int priceG, int stockG);
	void deleteCPU(string cod);
	void updateCPU(string codA, string socketG, int threadsG, int coresG, pair<double, double> clockSpeedG,
		int cacheG, string coolerG, string unlockedG, pair<string, int> memoryG, int memorySpeedG, string pciEG,
		string nameG, int priceG, int stockG);
	vector<CPU*> readCPU()*/
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);

	s1.addCPU("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", "intel i7", 1000, 200);
	assert(s1.readCPU().size() == 1 && s1.readCPU()[0]->getThreads() == 16);

	s1.updateCPU(s1.readCPU()[0]->getCode(), "", 19, -1, pair<double, double>(-1, -1), -1, "", "", pair<string, int>("", -1), -1, "", "", -1, -1);
	assert(s1.readCPU().size() == 1 && s1.readCPU()[0]->getThreads() == 19);

	s1.deleteCPU(s1.readCPU()[0]->getCode());
	assert(s1.readCPU().size() == 0);
}

void TestService::testCRUDGPU()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);

	s1.addGPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", "nVIDIA GTX 960", 900, 400);
	assert(s1.readGPU().size() == 1 && s1.readGPU()[0]->getMemorySpeed() == 3000);

	s1.updateGPU(s1.readGPU()[0]->getCode(), "", pair<string, int>("", -1), 5000, pair<int, int>(-1, -1), -1, -1, "", "", -1, -1);
	assert(s1.readGPU().size() == 1 && s1.readGPU()[0]->getMemorySpeed() == 5000);

	s1.deleteGPU(s1.readGPU()[0]->getCode());
	assert(s1.readGPU().size() == 0);
}

void TestService::testCRUDRAM()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);

	s1.addRAM(16, "DRAM", "DDR4", 2133, "Corsair Vengeance", 200, 5000);
	assert(s1.readRAM().size() == 1 && s1.readRAM()[0]->getCapacity() == 16);

	s1.updateRAM(s1.readRAM()[0]->getCode(), 8, "", "", -1, "", -1, -1);
	assert(s1.readRAM().size() == 1 && s1.readRAM()[0]->getCapacity() == 8);

	s1.deleteRAM(s1.readRAM()[0]->getCode());
	assert(s1.readRAM().size() == 0);
}

void TestService::testCRUDMBD()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);

	s1.addMBD("1151", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), "ASRock 7", 500, 200);
	assert(s1.readMBD().size() == 1 && s1.readMBD()[0]->getMemorySlots() == 4);

	s1.updateMBD(s1.readMBD()[0]->getCode(), "", pair<string, string>("", ""), pair<string, int>("", -1), 6, map<string, int>(), map<string, int>(), "", -1, -1);
	assert(s1.readMBD().size() == 1 && s1.readMBD()[0]->getMemorySlots() == 6);

	s1.deleteMBD(s1.readMBD()[0]->getCode());
	assert(s1.readMBD().size() == 0);
}

void TestService::testSearch()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);
	s1.addMBD("1151", pair<string, string>("Intel", "BG50"), pair<string, int>("DDR4", 128), 4, map<string, int>(), map<string, int>(), "ASRock 7", 500, 200);
	s1.addRAM(16, "DRAM", "DDR4", 2133, "Corsair Vengeance", 200, 5000);
	s1.addGPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", "nVIDIA GTX 960", 900, 400);
	s1.addCPU("1151", 16, 8, pair<double, double>(3.5, 5.5), 12, true, false, pair<string, int>("DDR4", 128), 3050, "3.0 x16", "intel i7", 1000, 200);

	vector<CPU*> resultsC;
	vector<GPU*> resultsG;
	vector<RAM*> resultsR;
	vector<Motherboard*> resultsM;

	vector<string> keywords;
	keywords.push_back("intel");
	resultsC = s1.searchCPU(keywords);
	assert(resultsC.size() == 1);
	keywords.clear(); keywords.push_back("intel"); keywords.push_back("i9");
	resultsC = s1.searchCPU(keywords);
	assert(resultsC.size() == 0);
	keywords.clear();
	resultsC = s1.searchCPU(keywords);
	assert(resultsC.size() == 1);

	keywords.clear(); keywords.push_back("Corsair");
	resultsR = s1.searchRAM(keywords);
	assert(resultsR.size() == 1);

	keywords.clear(); keywords.push_back("nVIDIA");
	resultsG = s1.searchGPU(keywords);
	assert(resultsG.size() == 1);

	keywords.clear(); keywords.push_back("ASRock");
	resultsM = s1.searchMBD(keywords);
	assert(resultsM.size() == 1);
}

void TestService::testFilter()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);
	s1.addGPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", "nVIDIA GTX 960", 900, 400);
	s1.filterGPU(">0", ">128", ">2000");
	assert(s1.readGPU().size() == 0);
}

void TestService::testSort()
{
	ofstream f("test_file1.txt");
	f.close();
	ofstream g("test_file2.txt");
	g.close();
	ofstream h("test_file3.txt");
	h.close();
	ofstream i("test_file4.txt");
	i.close();
	RepoCPU* rCPU = new RepoCPU("test_file1.txt");
	RepoGPU* rGPU = new RepoGPU("test_file2.txt");
	RepoRAM* rRAM = new RepoRAM("test_file3.txt");
	RepoMBD* rMBD = new RepoMBD("test_file4.txt");

	Service s1(rCPU, rGPU, rMBD, rRAM);
	s1.addGPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", "nVIDIA GTX 960", 900, 400);
	s1.addGPU("900", pair<string, int>("DDR4", 4), 3000, pair<int, int>(1920, 1080), 128, 4000, "3.0 x16", "nVIDIA GTX 960", 1200, 400);
	vector<GPU*> sorted = s1.GPUByPrice();
	assert(sorted[0]->getPrice() == 900);
}

void TestService::runTests()
{
	testCRUDCPU();
	testCRUDGPU();
	testCRUDMBD();
	testCRUDRAM();
	testSearch();
	testFilter();
	testSort();
}
