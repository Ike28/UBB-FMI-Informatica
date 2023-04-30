#include "utils.h"
#include <iostream>
#include <cstring>

using namespace std;

void copyIntToString(char* orig, int x)
{
	char digits[12];
	int n = abs(x), i=0;
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

void adaugare(Dreptunghi*& oldDs, int& n, Dreptunghi dnew)
{
	Dreptunghi* newDs = new Dreptunghi[n + 2];
	if (oldDs != nullptr)
	{
		for (int i = 0; i < n; i++)
			newDs[i] = oldDs[i];
	}

	newDs[n++] = dnew;

	oldDs = new Dreptunghi[n + 2];
	
	for (int i = 0; i < n; i++)
		oldDs[i] = newDs[i];
}

Dreptunghi citireDreptunghi()
{
	Dreptunghi dnew;
	cin >> dnew;

	return dnew;
}

void afisare(Dreptunghi* figuri, int n)
{
	if (figuri != nullptr)
	{
		char* equs;
		for (int i = 0; i < n; i++)
		{
			cout << "\n" <<"d"<<i+1<<": "<< figuri[i]
				<< "\n\naria: " << figuri[i].aria()
				<< " ; perimetrul: " << figuri[i].perimetrul();

			cout << "\n\nEcuatiile laturilor:";
			figuri[i].lineEquation(equs, 'A', 'B');
			cout << "\nAB: " << equs;
			figuri[i].lineEquation(equs, 'B', 'C');
			cout << "\nBC: " << equs;
			figuri[i].lineEquation(equs, 'C', 'D');
			cout << "\nCD: " << equs;
			figuri[i].lineEquation(equs, 'D', 'A');
			cout << "\nDA: " << equs;

			cout << "\n\nEcuatiile diagonalelor:";
			figuri[i].lineEquation(equs, 'A', 'C');
			cout << "\nAC: " << equs;
			figuri[i].lineEquation(equs, 'B', 'D');
			cout << "\nBD: " << equs << "\n";
			cout << "\n***********\n";
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

int pozBiggestDreptunghi(Dreptunghi* figuri, int n)
{
	if (n == 1)
		return 0;

	int pozMax = 0;
	for (int i = 1; i < n; i++)
		if (figuri[i] > figuri[pozMax])
			pozMax = i;

	return pozMax;
}

void cadran1(Dreptunghi* figuri, int n, Dreptunghi*& rezultat, int& dim)
{
	dim = 0; rezultat = nullptr;
	bool valid;
	for (int i = 0; i < n; i++)
	{
		valid = true;
		for (int j = 0; j < 4; j++)
			if (figuri[i].getFigura()[j].getCadran() != 1)
				valid = false;

		if (valid)
			adaugare(rezultat, dim, figuri[i]);
	}
}

bool egaleDreptunghiuri(Dreptunghi* figuri, int i, int j)
{
	for (int k = i; k < j; k++)
		if (!(figuri[k] == figuri[j]))
			return false;
	return true;
}

void subsecvMaxima(Dreptunghi* figuri, int n, bool proprietate(Dreptunghi*, int, int), int& start, int& fin)
{
	start = fin = -1;

	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (proprietate(figuri, i, j) && j - i > fin - start)
				start = i, fin = j;
}
