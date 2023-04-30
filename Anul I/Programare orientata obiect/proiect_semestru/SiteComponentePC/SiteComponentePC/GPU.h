#pragma once
#include "Component.h"
#include <string>
using namespace std;

class GPU : public Component
{
	private:
		string series;
		pair<string, int> memory; // first - memory type (DDRX) ; second - capacity
		int memorySpeed;
		pair<int, int> maxRes;
		int busWidth;
		int cuda;
		string pciE;
	public:
		GPU();
		GPU(string seriesG, pair<string, int> memoryG, int memorySpeedG, pair<int, int> maxResG, int busWidthG, int cudaG, string pciEG,
			string codG, string nameG, int priceG, int stockG);
		GPU(const GPU& other);
		~GPU();

		string getSeries() { return series; }
		pair<string, int> getMemoryData() { return memory; }
		int getMemorySpeed() { return memorySpeed; }
		pair<int, int> getMaxRes() { return maxRes; }
		int getBusWidth() { return busWidth; }
		int getCuda() { return cuda; }
		string getPciE() { return pciE; }

		friend ostream& operator<<(ostream& os, GPU& other);
};
