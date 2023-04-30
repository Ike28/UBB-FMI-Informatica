#include <iostream>
#include "subalg.h"
#include "tests.h"
using namespace std;

int main()
{
	testSecvMaximaElementeInterval;
	testSecvMaximaSemneAlternante;
	char option;
	int v[100], n;
	bool existFlag = false;
	while (1)
	{
		cout << "\nMeniu functionalitati\n1.Citire lista de numere intregi\n2.Afisare lista de numere intregi\n3.Cea mai lunga secventa cu toate numerele intr-un interval dat\nX.Oprire\n";
		cout << "\nIntroduceti optiunea dorita: ";
		cin >> option;
		switch (option)
		{
		case '1':
			citire(v, n);
			existFlag = true;
			break;
		case '2':
			switch (existFlag)
			{
			case true:
				afisare(v, n);
				break;
			default:
				cout << "\nNicio lista nu a fost memorata inca.\n";
				break;
			}
			break;
		case '3':
			switch (existFlag)
			{
			case true:
				int a, b;
				while (1)
				{
					cout << "\nIntroduceti capetele intervalului [a,b]:";
					cout << "\na= ";
					cin >> a;
					cout << "\nb= ";
					cin >> b;
					if (a > b)
						cout << "\nEroare: interval invalid. Reincercati!\n";
					else break;
				}
				int start, fin;
				secvMaximaInterval(v, n, start, fin, a, b);
				if (start == -1)
					cout << "\nNu exista o astfel de secventa in lista data.\n";
				else
				{
					cout << "\nSecventa cautata este: ";
					for (int i = start; i <= fin; i++)
						cout << v[i] << " ";
					cout << "\n";
				}
				break;
			default:
				cout << "\nNicio lista nu a fost memorata inca.\n";
				break;
			}
			break;

		case '4':
			switch (existFlag)
			{
			case true:
				int start, fin;
				secvMaximaSemne(v, n, start, fin);
				if (start == -1)
					cout << "\nNu exista o astfel de secventa in lista data.\n";
				else
				{
					cout << "\nSecventa cautata este: ";
					for (int i = start; i <= fin; i++)
						cout << v[i] << " ";
					cout << "\n";
				}
				break;
			default:
				cout << "\nNicio lista nu a fost memorata inca.\n";
				break;
			}
			break;
		case 'X':
			cout << "\nPROGRAMUL A FOST OPRIT DE CATRE UTILIZATOR\n";
			return 0;
		default:
			cout << "\nOptiune invalida.\n";
		}
	}
}
