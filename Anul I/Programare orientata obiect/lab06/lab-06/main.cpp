#include "Tests.h"
#include "utils.h"
#include "Dreptunghi.h"
#include <iostream>
#include <map>

using namespace std;

int main()
{
	Tests t;
	t.testDreptunghi();
	t.testPunct();
	t.testAdaugare();
	t.testBiggest();
	t.testCadran1();
	//t.testSubsecv();
	std::cout << "Testele-s okei\n";

	int n;
	map <int, Dreptunghi> figuri;
	map <int, Dreptunghi> rezultat;
	Dreptunghi d;
	char p1, p2;
	char* s = nullptr;

	while (1)
	{
		printMenu();
		char option = getOption();
		switch (option)
		{
		case '1':
			figuri.clear();
			n = citireNumar("\nIntroduceti numarul de elemente: ");
			if (n > 0)
			{
				cout << "\nIntroduceti coordonatele perechilor (x1, y1) (x2, y2) pentru toate dreptunghiurile D:";
				cout << "\nD:  x1 y1 x2 y2";
				cout << "\n    |  |  |  |\n";
				for (int i = 0; i < n; i++)
				{
					cout << "d" << i + 1 << ": ";
					d = citireDreptunghi();
					adaugare(figuri, d);
				}
				cout << "\nDatele au fost memorate!\n";
			}
			else if (n == 0)
			{
				cout << "\nAu fost sterse dreptunghiurile inregistrate!\n";
			}
			else cout << "\nDimensiunea introdusa trebuie sa fie un numar strict pozitiv.\n";
			break;
		case '2':
			afisare(figuri);
			break;
		case '3':
			if (figuri.size() > 0)
			{
				n = pozBiggestDreptunghi(figuri);
				cout << "\nCel mai mare dreptunghi este\nd" << n + 1 << ": ";
				cout << figuri[n];
			}
			else cout << "\nNu exista dreptunghiuri memorate.\n";
			break;
		case '4':
			cadran1(figuri, rezultat);
			if (rezultat.size() == 0 || figuri.size() == 0)
				cout << "\nNu exista dreptunghiuri in cadranul I sau nu exista dreptunghiuri memorate.\n";
			else
			{
				cout << "\nAu fost identificate " << rezultat.size() << " dreptunghiuri in cadranul I:\n";
				for (map<int, Dreptunghi>::iterator i = rezultat.begin() ; i != rezultat.end() ; i++)
					cout << (*i).second << "\n\n";
			}
			break;
		case '5':
			int start, fin;
			subsecvMaxima(figuri, egaleDreptunghiuri, start, fin);
			if (start == -1)
				cout << "\nNu exista o astfel de secventa sau nu exista dreptunghiuri memorate.\n";
			else
			{
				cout << "\nSecventa maxima are lungimea " << fin - start + 1 << ": ";
				for (int i = start; i <= fin; i++)
					cout << "d" << i + 1 << " ";
				cout << '\n';
			}
			break;
		case 'x':
			cout << "\nSee ya!\n";
			return 0;
		default:
			cout << "\nMai incearca!\n";
			break;
		}
	}
}