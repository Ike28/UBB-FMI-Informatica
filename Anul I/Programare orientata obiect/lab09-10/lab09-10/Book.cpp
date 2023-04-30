#include "Book.h"
#include <string.h>
#include <iostream>

int Book::nextCod = 1;

Book::Book()
{
	this->cod = nextCod++;
	this->autor = nullptr;
	this->gen = nullptr;
	this->titlu = nullptr;
	this->stoc = 0;
	this->pret = 0;
}

Book::Book(char* titluDat, char* autorDat, char* genDat, int stocDat, unsigned int pretDat)
{
	this->cod = nextCod++;

	this->titlu = new char[strlen(titluDat) + 1];
	strcpy_s(this->titlu, strlen(titluDat) + 1, titluDat);

	this->autor = new char[strlen(autorDat) + 1];
	strcpy_s(this->autor, strlen(autorDat) + 1, autorDat);

	this->gen = new char[strlen(genDat) + 1];
	strcpy_s(this->gen, strlen(genDat) + 1, genDat);

	this->stoc = stocDat;
	this->pret = pretDat;
}

Book::Book(const char* titluDat, const char* autorDat, const char* genDat, int stocDat, unsigned int pretDat)
{
	this->cod = nextCod++;

	this->titlu = new char[strlen(titluDat) + 1];
	strcpy_s(this->titlu, strlen(titluDat) + 1, titluDat);

	this->autor = new char[strlen(autorDat) + 1];
	strcpy_s(this->autor, strlen(autorDat) + 1, autorDat);

	this->gen = new char[strlen(genDat) + 1];
	strcpy_s(this->gen, strlen(genDat) + 1, genDat);

	this->stoc = stocDat;
	this->pret = pretDat;
}

Book::Book(const Book& other)
{
	this->cod = other.cod;

	this->titlu = new char[strlen(other.titlu) + 1];
	strcpy_s(this->titlu, strlen(other.titlu) + 1, other.titlu);

	this->autor = new char[strlen(other.autor) + 1];
	strcpy_s(this->autor, strlen(other.autor) + 1, other.autor);

	this->gen = new char[strlen(other.gen) + 1];
	strcpy_s(this->gen, strlen(other.gen) + 1, other.gen);

	this->stoc = other.stoc;
	this->pret = other.pret;
}

Book::~Book()
{
	delete[] this->autor; this->autor = nullptr;
	delete[] this->gen; this->gen = nullptr;
	delete[] this->titlu; this->titlu = nullptr;
}

int Book::getCod()
{
	return this->cod;
}

void Book::setCod(int codNew)
{
	this->cod = codNew;
}

char* Book::getTitlu()
{
	return this->titlu;
}

void Book::setTitlu(char* titluDat)
{
	this->titlu = new char[strlen(titluDat) + 1];
	strcpy_s(this->titlu, strlen(titluDat) + 1, titluDat);
}

char* Book::getAutor()
{
	return this->autor;
}

void Book::setAutor(char* autorDat)
{
	this->autor = new char[strlen(autorDat) + 1];
	strcpy_s(this->autor, strlen(autorDat) + 1, autorDat);
}

char* Book::getGen()
{
	return this->gen;
}

void Book::setGen(char* genDat)
{
	this->gen = new char[strlen(genDat) + 1];
	strcpy_s(this->gen, strlen(genDat) + 1, genDat);
}

int Book::getStoc()
{
	return this->stoc;
}

void Book::setStoc(int stocDat)
{
	this->stoc = stocDat;
}

int Book::getPret()
{
	return this->pret;
}

void Book::setPret(unsigned int pretDat)
{
	this->pret = pretDat;
}

bool Book::operator==(const Book& other)
{
	return strcmp(this->autor, other.autor) == 0
		&& strcmp(this->gen, other.gen) == 0
		&& strcmp(this->titlu, other.titlu) == 0
		&& this->stoc == other.stoc
		&& this->pret == other.pret;
}

Book& Book::operator=(const Book& other)
{
	this->cod = other.cod;

	this->titlu = new char[strlen(other.titlu) + 1];
	strcpy_s(this->titlu, strlen(other.titlu) + 1, other.titlu);

	this->autor = new char[strlen(other.autor) + 1];
	strcpy_s(this->autor, strlen(other.autor) + 1, other.autor);

	this->gen = new char[strlen(other.gen) + 1];
	strcpy_s(this->gen, strlen(other.gen) + 1, other.gen);

	this->stoc = other.stoc;
	this->pret = other.pret;
	return *this;
}

ostream& operator<<(ostream& os, const Book& other)
{
	if (&os == &std::cout)
	{
		if (other.autor == nullptr)
			os << "Carte nedefinita";
		else
		{
			os << "COD: " << other.cod
				<< " | Autor: " << other.autor
				<< " | Titlu: '" << other.titlu
				<< "' | Gen: " << other.gen
				<< " | Stoc: " << other.stoc << " bucati"
				<< " | Pret: " << other.pret << " lei";
		}
	}
	else
	{
		if (other.autor == nullptr)
			os << 0 << " | " << "null" << " | " << "null" << " | " << "null" << " | " << 0 << " | " << 0;
		else
		{
			os  << other.cod
				<< " | " << other.autor
				<< " | " << other.titlu
				<< " | " << other.gen
				<< " | " << other.stoc
				<< " | " << other.pret;
		}
	}
	return os;
}
