#include "utils.h"
#include <iostream>
#include <cstring>

using namespace std;

void copyIntToString(char* orig, int x)
{
	char digits[12];
	int n = abs(x), i = 0;
	while (n)
		digits[i++] = '0' + n % 10, n /= 10;
	if (x == 0)
		digits[i++] = '0';
	if (x < 0)
		digits[i] = '-';
	else digits[i] = '+';

	int j = 0;
	while (i >= 0)
		orig[j++] = digits[i--];
	orig[j] = 0;
}

void printMenu()
{
	cout << "\n-------------\n";
	cout << "\n1. Citire dreptunghiuri";
	cout << "\n2. Afisare dreptunghiuri";
	cout << "\n3. Cel mai mare dreptunghi";
	cout << "\n4. Dreptunghiuri din cadranul I";
	cout << "\n5. Cea mai lunga secventa de entitati egale";
	cout << "\nx. Oprire\n";
	cout << "\n-------------\n";
}

char getOption()
{
	char op;
	cout << "\nSelectati optiunea dorita: ";
	cin >> op;
	return op;
}

void citirePuncteEcuatie(char& x, char& y)
{
	char a, b;
	char inp[2];
	while (1)
	{
		cout << "\nIntroduceti dreapta (de ex. AB): ";
		cin >> a >> b;

		if (a >= 'A' && a <= 'D' && b >= 'A' && b <= 'D')
			break;
		else
			cout << "\nCel putin unul din punctele alese este invalid (trebuie sa fie din dreptunghi)\nReincearca!";
	}
	x = a;
	y = b;
}

void citireDreptunghi(int& x1, int& y1, int& x2, int& y2)
{
	//int x1, x2, y1, y2;

	while (1)
	{
		cout << "\nDati coordonatele primului punct al diagonalei:\n";
		cout << "x = ";
		cin >> x1;
		cout << "y = ";
		cin >> y1;

		cout << "\nDati coordonatele celui de-al doilea punct al diagonalei:\n";
		cout << "x = ";
		cin >> x2;
		cout << "y = ";
		cin >> y2;

		if (x1 != x2 && y1 != y2)
			break;
		else
			cout << "\nPunctele date nu formeaza un dreptunghi nevid!";
	}
}

void adaugare(map <int, Dreptunghi> &oldDs, Dreptunghi dnew)
{
	oldDs.insert(pair<int, Dreptunghi>(oldDs.size(), dnew));
}

Dreptunghi citireDreptunghi()
{
	Dreptunghi dnew;
	cin >> dnew;

	return dnew;
}

void afisare(map <int, Dreptunghi> figuri)
{
	if (figuri.size()>0)
	{
		char* equs;
		map <int, Dreptunghi>::iterator it = figuri.begin();
		while(it != figuri.end())
		{
			cout << "\n" << "d" << (*it).first << ": " << (*it).second
				<< "\n\naria: " << (*it).second.aria()
				<< " ; perimetrul: " << (*it).second.perimetrul();

			cout << "\n\nEcuatiile laturilor:";
			(*it).second.lineEquation(equs, 'A', 'B');
			cout << "\nAB: " << equs;
			(*it).second.lineEquation(equs, 'B', 'C');
			cout << "\nBC: " << equs;
			(*it).second.lineEquation(equs, 'C', 'D');
			cout << "\nCD: " << equs;
			(*it).second.lineEquation(equs, 'D', 'A');
			cout << "\nDA: " << equs;

			cout << "\n\nEcuatiile diagonalelor:";
			(*it).second.lineEquation(equs, 'A', 'C');
			cout << "\nAC: " << equs;
			(*it).second.lineEquation(equs, 'B', 'D');
			cout << "\nBD: " << equs << "\n";
			cout << "\n***********\n";

			it++;
		}
	}
	else cout << "\nNu exista dreptunghiuri memorate.";
}

void dealocare(Dreptunghi*& figuri)
{
	if (figuri != nullptr)
	{
		delete[] figuri;
		figuri = nullptr;
	}
}

int citireNumar(const char* s)
{
	int n;
	cout << s;
	cin >> n;
	return n;
}

int pozBiggestDreptunghi(map <int, Dreptunghi> figuri)
{
	if (figuri.size() == 1)
		return 0;

	int keyMax = 0; map<int, Dreptunghi>::iterator i = figuri.begin();
	while (i != figuri.end())
	{
		if ((*i).second > figuri[keyMax])
			keyMax = (*i).first;
		i++;
	}

	return keyMax;
}

void cadran1(map <int, Dreptunghi> figuri, map <int, Dreptunghi> &rezultat)
{
	bool valid;
	for (map<int, Dreptunghi>::iterator i = figuri.begin(); i!=figuri.end() ; i++)
	{
		valid = true;
		for (int j = 0; j < 4; j++)
			if ((*i).second.getFigura()[j].getCadran() != 1)
				valid = false;

		if (valid)
			adaugare(rezultat, (*i).second);
	}
}

bool egaleDreptunghiuri(map <int, Dreptunghi> figuri, int i, int j)
{
	for (int k = i; k <= j; k++)
		if (!(figuri[k] == figuri[j]))
			return false;
	return true;
}

void subsecvMaxima(map <int, Dreptunghi> figuri, bool proprietate(map <int, Dreptunghi>, int, int), int& start, int& fin)
{
	start = fin = -1;

	for (int i =0;i<figuri.size(); i++)
		for (int j = i; j <figuri.size(); j++)
			if (proprietate(figuri, i, j) && i - j > fin - start)
				start = i, fin = j;
}
