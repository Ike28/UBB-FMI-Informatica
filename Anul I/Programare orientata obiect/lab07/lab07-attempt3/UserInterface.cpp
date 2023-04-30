#define _CRT_SECURE_NO_WARNINGS
#include "UserInterface.h"
#include "Validator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

/// <summary>
/// Administreaza in consola adaugarea unei noi cheltuieli prin service
/// </summary>
void UserInterface::addPayment()
{
	int sum, dayInt; char type[11], day[6];
	cout << "\nIntroduceti data platii (scrieti azi pentru data curenta): ";
	cin >> day; time_t dateNow = time(0);
	if (strcmp(day, "azi") == 0)
		dayInt = localtime(&(dateNow))->tm_mday;
	else dayInt = atoi(day);
	cout << "Introduceti suma platita: ";
	cin >> sum;
	cout << "Introduceti tipul cheltuielii: ";
	cin >> type;
	Payment newPayment(type, dayInt, sum);
	//Validator::validatePayment(newPayment);
	this->servicePayment.addElem(newPayment);
	cout << "\nCheltuiala adaugata cu succes!\n";
}

/// <summary>
/// Administreaza in consola stergerea unei cheltuieli dupa ID prin service
/// </summary>
void UserInterface::deletePayment()
{
	int idDat;
	cout << "\nIntroduceti ID-ul: ";
	cin >> idDat;
	this->servicePayment.deleteByID(idDat);
	cout << "\nCheltuiala a fost stearsa cu succes!\n";
}

/// <summary>
/// Administreaza in consola actualizarea unei cheltuieli dupa ID prin service
/// </summary>
void UserInterface::updatePayment()
{
	int idDat, day, sum; char type[11];
	cout << "\nIntroduceti ID-ul: ";
	cin >> idDat;
	cout << "\nIntroduceti data noua a platii: ";
	cin >> day;
	cout << "Introduceti noua suma platita: ";
	cin >> sum;
	cout << "Introduceti noul tip al cheltuielii: ";
	cin >> type;
	this->servicePayment.updateByID(idDat, Payment(type, day, sum));
	cout << "\nCheltuiala a fost actualizata cu succes!\n";
}

/// <summary>
/// Administreaza in consola afisarea cheltuielilor stocate prin service
/// </summary>
void UserInterface::readPayments()
{
	Payment* payments = this->servicePayment.read();
	int dim = this->servicePayment.size();
	if (dim == 0)
		cout << "\nNu exista cheltuieli inregistrate!\n";
	else
	{
		for (int i = 0; i < dim; i++)
			cout << payments[i] << '\n';
		cout << '\n';
	}
}

void UserInterface::undo()
{
	if (this->servicePayment.isUndo())
	{
		this->servicePayment.undo();
		cout << "\nUltima modificare a fost anulata!\n";
	}
	else cout << "\nNu avem sefule!";
}

void UserInterface::modifyData()
{
	char option[10];
	cout << "\nSelectati criteriul de eliminare (zi/interval/tip): ";
	cin >> option;
	if (strcmp(option, "zi") == 0)
	{
		int dayGiven;
		cout << "\nIntroduceti ziua: ";
		cin >> dayGiven;
		this->servicePayment.deleteByDay(dayGiven);
		cout << "\nCheltuielile au fost eliminate!";
	}
	else if (strcmp(option, "interval") == 0)
	{
		int dayStart, dayFinal;
		cout << "\nIntroduceti ziua de inceput a intervalului: ";
		cin >> dayStart;
		cout << "\nIntroduceti ziua de sfarsit a intervalului: ";
		cin >> dayFinal;
		this->servicePayment.deleteByInterval(dayStart, dayFinal);
		cout << "\nCheltuielile au fost eliminate!";
	}
	else if (strcmp(option, "tip") == 0)
	{
		char typeGiven[20];
		cout << "\nIntroduceti tipul\n(menaj/mancare/transport/haine/internet/altele): ";
		cin >> typeGiven;
		this->servicePayment.deleteByType(typeGiven);
		cout << "\nCheltuielile au fost eliminate!";
	}
	else cout << "\nCriteriul introdus nu este unul acceptat! Revenire la meniu...\n";
}

void UserInterface::listData()
{
	char typeGiven[20], disc; int val;
	cout << "\nIntroduceti tipul si formula de comparare a sumei\n(sau -1 pentru a cauta exclusiv dupa tip): ";
	cin >> typeGiven >> disc >> val;
	if (!(strchr("-><=", disc)))
		cout << "\nFormula contine un simbol indecidabil. Revenire la meniu...\n";
	else
	{
		vector<Payment> searchResults = this->servicePayment.listByType(typeGiven, disc, val);
		if (searchResults.size() == 0)
			cout << "\nNu exista cheltuieli care indeplinesc criteriile.";
		else
		{
			vector<Payment>::iterator i = searchResults.begin();
			while (i != searchResults.end())
			{
				cout << '\n' << (*i);
				i++;
			}
			cout << "\n\nTOTAL: " << searchResults.size() << " rezultate";
		}
	}
}

void UserInterface::properties()
{
	char option;
	// -_-
	char typeGiven[20]; char typeAgain[20]; char def[] = "null"; vector<pair<int,int>> sorted, sortedAgain; pair<int, int> result;
	int sum;
	// /-_-
	cout << "\n   a. Suma cheltuielilor de un anume tip";
	cout << "\n   b. Ziua cu cheltuieli maxime";
	cout << "\n   c. Cheltuieli pe zi, descrescator";
	cout << "\n   d. Cheltuieli pe zi dupa tip, crescator";
	cout << "\nSelectati tipul de statistica: ";
	cin >> option;
	switch (option)
	{
	case 'a':
		
		cout << "\nIntroduceti tipul: ";
		cin >> typeGiven;
		sum = this->servicePayment.sumByType(typeGiven);
		cout << "\nSuma cheltuielilor de " << typeGiven << " este " << sum;
		break;
	case 'b':
		result = this->servicePayment.maxDayBySums();
		cout << "\nZiua cu cheltuieli maxime este " << result.first << ", avand cheltuieli de " << result.second << " lei.\n";
		break;
	case 'c':
		sorted = this->servicePayment.sortSumsByType(def);
		if (sorted.size() == 0)
			cout << "\nNu au fost gasite cheltuieli de afisat.";
		else for (vector<pair<int, int>>::reverse_iterator i = sorted.rbegin(); i != sorted.rend(); ++i)
			cout << "\nZiua " << (*i).first << " are cheltuieli totale de " << (*i).second << " lei";
		break;
	case 'd':
		
		cout << "\nIntroduceti tipul: ";
		cin >> typeAgain;
		sortedAgain = this->servicePayment.sortSumsByType(typeAgain);
		if (sortedAgain.size() == 0)
			cout << "\nNu au fost gasite cheltuieli de afisat.";
		else for (vector<pair<int, int>>::iterator i = sortedAgain.begin(); i != sortedAgain.end(); i++)
			cout << "\nZiua " << (*i).first << " are cheltuieli totale de " << typeAgain << " de " << (*i).second << " lei";
		break;
	default:
		cout << "\nOptiune invalida. Revenire la meniu...\n";
		break;
	}
}

void UserInterface::filter()
{
	char typeGiven[20], disc; int val;
	cout << "\nIntroduceti tipul si formula de comparare a sumei\n(sau -1 pentru a cauta exclusiv dupa tip): ";
	cin >> typeGiven >> disc >> val;
	if (!(strchr("-><=", disc)))
		cout << "\nFormula contine un simbol indecidabil. Revenire la meniu...\n";
	else
	{
		this->servicePayment.filterByType(typeGiven, disc, val);
		cout << "\nCheltuielile au fost filtrate!";
	}
}



/// <summary>
/// Afiseaza in consola meniul de functionalitati pentru service
/// </summary>
void UserInterface::printMenu()
{
	cout << "\n----------------------------";
	cout << "\nC. R. U. D.";
	cout << "\n|  1. Adauga cheltuieli";
	cout << "\n|  2. Afiseaza cheltuieli";
	cout << "\n|  3. Sterge cheltuieli";
	cout << "\n|  4. Modifica cheltuieli";
	cout << "\n\n5. Meniu operatiuni avansate";
	cout << "\n<. UNDO";
	cout << "\nx. <--- Oprire";
	cout << "\n----------------------------\n";
}

void UserInterface::printOperationsMenu()
{
	cout << "\n----------------------------";
	cout << "\nO P E R A T I U N I";
	cout << "\n|  1. Eliminari date";
	cout << "\n|  2. Cautari dupa proprietati";
	cout << "\n|  3. Statistici";
	cout << "\n|  4. Filtrari date";
	cout << "\n\n<. UNDO";
	cout << "\nx. <--- Inapoi";
	cout << "\n----------------------------\n";
}

void UserInterface::runOperationsInterface()
{
	char option;
	while (true)
	{
		this->printOperationsMenu();

		cout << "\nSelectati optiunea dorita: ";
		cin >> option;
		switch (option)
		{
		case '1':
			this->modifyData();
			break;
		case '2':
			this->listData();
			break;
		case '3':
			this->properties();
			break;
		case '4':
			this->filter();
			break;
		case 'x':
			system("CLS");
			return;
		case '<':
			this->undo();
			break;
		default:
			cout << "\nMai incearca!\n";
			break;
		}
	}
}

/// <summary>
/// Constructor implicit pentru interfata
/// </summary>
UserInterface::UserInterface()
{
}

/// <summary>
/// Constructor cu parametri pentru interfata
/// </summary>
/// <param name="serviceGiven">obiect Service pentru obiecte de tip Payment</param>
UserInterface::UserInterface(Service<Payment> serviceGiven)
{
	this->servicePayment = serviceGiven;
}

/// <summary>
/// Destructor pentru interfata
/// </summary>
UserInterface::~UserInterface()
{
}

/// <summary>
/// Ruleaza interfata cu utilizatorul pe consola
/// </summary>
void UserInterface::runInterface()
{
	char option;
	while (true)
	{
		this->printMenu();

		cout << "\nSelectati optiunea dorita: ";
		cin >> option;
		switch (option)
		{
		case '1':
			this->addPayment();
			break;
		case '2':
			this->readPayments();
			break;
		case '3':
			this->deletePayment();
			break;
		case '4':
			this->updatePayment();
			break;
		case '5':
			system("CLS");
			this->runOperationsInterface();
			break;
		case 'x':
			cout << "\nProgramul a fost oprit cu succes!\n";
			return;
		case '<':
			this->undo();
			break;
		default:
			cout << "\nMai incearca!\n";
			break;
		}
	}
}
