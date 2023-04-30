#pragma once
#include <ostream>
#include <vector>

using namespace std;

class Payment
{
	private:
		unsigned int ID;
		char* tip;
		int day;
		int sum;

		static vector<const char*> types;
		static unsigned int nextID;
	public:
		Payment();
		Payment(char* tipDat, int dayGiven, int sumGiven);
		Payment(const Payment& other);
		~Payment();

		unsigned int getID();
		void setID(int newID);
		char* getTip();
		void setTip(char* tipDat);
		int getDay();
		void setDay(int dayGivem);
		int getSum();
		void setSum(int sumGiven);
		static vector<const char*>& getTypes() = delete;

		Payment& operator=(const Payment& other);
		bool operator==(const Payment& other);
		bool operator<(const Payment& other);
		friend ostream& operator<<(ostream& os, Payment& other);
};
