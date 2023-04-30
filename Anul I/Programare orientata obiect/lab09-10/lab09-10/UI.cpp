#include "UI.h"
#include "InvalidIDException.h"
#include "NameException.h"
#include "PriceException.h"
#include "StockException.h"
#include "CastException.h"
#include <iostream>
using namespace std;


void UserInterface::addBook()
{
	try
	{
		char autor[50], titlu[100], gen[100]; string ci; int stoc, pret;
		cout << "\nIntroduceti autorul cartii: ";
		cin.get();
		cin.getline(autor, 50);
		cout << "\nIntroduceti titlul cartii: ";
		//cin.get();
		cin.getline(titlu, 100);
		cout << "\nIntroduceti genul cartii: ";
		//cin.get();
		cin.getline(gen, 100);
		cout << "\nIntroduceti stocul: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		stoc = stoi(ci);
		cout << "\nIntroduceti pretul: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		pret = stoi(ci);
		Book newBook(titlu, autor, gen, stoc, pret);
		this->serviceBook.addElem(newBook);
		cout << "\nCartea a fost inregistrata cu succes!\n";
	}
	catch (PriceException pe)
	{
		cout << "\nEroare:\n" << pe << "\n---> reincercati!\n";
	}
	catch (StockException se)
	{
		cout << "\nEroare:\n" << se << "\n---> reincercati!\n";
	}
	catch (NameException ne)
	{
		cout << "\nEroare:\n" << ne << "\n---> reincercati!\n";
	}
	catch (CastException ce)
	{
		cout << "\nEroare:\n" << ce << "\n---> reincercati!\n";
	}
}

void UserInterface::deleteBook()
{
	try
	{
		int codDat; string ci;
		cout << "\nIntroduceti codul cartii de sters: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		codDat = stoi(ci);
		this->serviceBook.deleteElem(codDat);
		cout << "\nCartea a fost stearsa!\n";
	}
	catch (InvalidIDException ie)
	{
		cout << "\nEroare:\n" << ie << "\n---> reincercati!\n";
	}
}

void UserInterface::updateBook()
{
	try
	{
		char autor[50], titlu[100], gen[100]; int stoc, codDat, pret; string ci;
		cout << "\nIntroduceti codul: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		codDat = stoi(ci);
		cout << "\nIntroduceti autorul nou: ";
		cin.get();
		cin.getline(autor, 50);
		cout << "\nIntroduceti titlul nou: ";
		//cin.get();
		cin.getline(titlu, 100);
		cout << "\nIntroduceti genul nou: ";
		//cin.get();
		cin.getline(gen, 100);
		cout << "\nIntroduceti stocul nou: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		stoc = stoi(ci);
		cout << "\nIntroduceti pretul: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		pret = stoi(ci);
		this->serviceBook.updateElem(codDat, Book(titlu, autor, gen, stoc, pret));
		cout << "\nCartea a fost actualizata cu succes!\n";
	}
	catch (PriceException pe)
	{
		cout << "\nEroare:\n" << pe << "\n---> reincercati!\n";
	}
	catch (StockException se)
	{
		cout << "\nEroare:\n" << se << "\n---> reincercati!\n";
	}
	catch (NameException ne)
	{
		cout << "\nEroare:\n" << ne << "\n---> reincercati!\n";
	}
	catch (InvalidIDException ie)
	{
		cout << "\nEroare:\n" << ie << "\n---> reincercati!\n";
	}
	catch (CastException ce)
	{
		cout << "\nEroare:\n" << ce << "\n---> reincercati!\n";
	}
}

void UserInterface::readBooks()
{
	vector<Book> books = this->serviceBook.read();
	if (books.size() > 0)
	{
		for (vector<Book>::iterator i = books.begin(); i != books.end(); i++)
			cout << (*i) << '\n';
		cout << '\n';
	}
	else cout << "\nNu exista carti inregistrate";
}

void UserInterface::orderBooks()
{
	try
	{
		int bookCount, cod, pretTotal, reducere; string ci;
		cout << "\nIntroduceti numarul de carti comandate: ";
		cin >> ci;
		for (int i = 0; i < ci.size(); i++)
			if (!isdigit(ci[i]))
				throw CastException("\nDate invalide.");
		bookCount = stoi(ci);
		vector<int> bookCodes;
		cout << "\nIntroduceti ID-urile cartilor, separate prin spatiu: ";
		for (int i = 0; i < bookCount; i++)
		{
			cin >> ci;
			for (int i = 0; i < ci.size(); i++)
				if (!isdigit(ci[i]))
					throw CastException("\nDate invalide.");
			cod = stoi(ci);
			bookCodes.push_back(cod);
		}
		this->serviceBook.orderBooks(bookCodes, pretTotal, reducere);
		cout << "\nComanda are un pret de " << pretTotal << " lei.";
		if (reducere > 0)
		{
			cout << "\nA fost aplicata o reducere de " << reducere << "%!";
			float total = pretTotal;
			total -= ((float)reducere * (float)total) / 100;
			cout << "\nTOTAL: " << total << " lei.\n";
		}
		else cout << "\nNu a fost aplicata nicio reducere.\nTOTAL: " << pretTotal << " lei.";
	}
	catch (InvalidIDException ie)
	{
		cout << "\nEroare:\n" << ie << "\n---> reincercati!\n";
	}
	catch (CastException ce)
	{
		cout << "\nEroare:\n" << ce << "\n---> reincercati!\n";
	}
}

void UserInterface::printMenu()
{
	cout << "\n1.Adauga carti";
	cout << "\n2.Afiseaza carti";
	cout << "\n3.Sterge carti";
	cout << "\n4.Modifica carti";
	cout << "\n5.Plasare comanda";
	cout << "\n\nx ---> Oprire\n";
}

UserInterface::UserInterface()
{
}

UserInterface::UserInterface(ServiceFile serviceGiven)
{
	this->serviceBook = serviceGiven;
}

UserInterface::~UserInterface()
{
}

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
			this->addBook();
			break;
		case '2':
			this->readBooks();
			break;
		case '3':
			this->deleteBook();
			break;
		case '4':
			this->updateBook();
			break;
		case '5':
			this->orderBooks();
			break;
		case 'x':
			cout << "\nProgramul a fost oprit cu succes!\n";
			return;
		default:
			cout << "\nMai incearca!\n";
			break;
		}
	}
}
