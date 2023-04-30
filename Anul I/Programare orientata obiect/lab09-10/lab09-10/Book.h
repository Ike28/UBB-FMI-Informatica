#pragma once
#include <ostream>
using namespace std;

class Book
{
	private:
		int cod;
		char* titlu;
		char* autor;
		char* gen;
		int stoc;
		unsigned int pret;

		static int nextCod;
	public:
		Book();
		Book(char* titluDat, char* autorDat, char* genDat, int stocDat, unsigned int pretDat);
		Book(const char* titluDat, const char* autorDat, const char* genDat, int stocDat, unsigned int pretDat);
		Book(const Book& other);
		~Book();

		int getCod();
		void setCod(int codNew);
		char* getTitlu();
		void setTitlu(char* titluDat);
		char* getAutor();
		void setAutor(char* autorDat);
		char* getGen();
		void setGen(char* genDat);
		int getStoc();
		void setStoc(int stocDat);
		int getPret();
		void setPret(unsigned int pretDat);

		bool operator==(const Book& other);
		Book& operator=(const Book& other);
		friend ostream& operator<<(ostream& os, const Book& other);
};
