#pragma once
#include "Punct.h";
#include <ostream>
#include <map>

class Dreptunghi {
	private:
		Punct* figura;
		int lungime;
		int latime;
		void setLaturi();
		static  map<char, int> pointKeys;
	public:
		Dreptunghi();
		Dreptunghi(int x1, int y1, int x2, int y2);
		Dreptunghi(const Dreptunghi& other);
		~Dreptunghi();

		Punct getPunctA();
		Punct getPunctB();
		Punct getPunctC();
		Punct getPunctD();
		Punct* getFigura();

		int getLungime();
		int getLatime();

		void setPunctA(int x, int y);
		void setPunctB(int x, int y);
		void setPunctC(int x, int y);
		void setPunctD(int x, int y);

		Dreptunghi& operator=(const Dreptunghi& other);
		bool operator>(Dreptunghi& other);
		bool operator<(Dreptunghi& other);
		bool operator==(Dreptunghi& other);

		friend std::ostream& operator<<(std::ostream& os, const Dreptunghi& other);
		friend std::istream& operator>>(std::istream& os, Dreptunghi& other);

		void lineEquation(char*& equ, char point1, char point2);
		int aria();
		int perimetrul();
};
