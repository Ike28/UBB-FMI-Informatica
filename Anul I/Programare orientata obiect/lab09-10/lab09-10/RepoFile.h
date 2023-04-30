#pragma once
#include "Repo.h"
#include "Book.h"
#include <string>
#include <fstream>
using namespace std;

class FileRepo : public Repo<Book>
{
	private:
		string filename;
		void writeToFile();
		void loadFromFile();
	public:
		FileRepo();
		FileRepo(string filenameGiven);
		~FileRepo();

		void setFilename(string filenameGiven);
		string getFilename();
		int getDim();

		FileRepo& operator=(const FileRepo& other);
		void addElem(Book elem);
		void deleteElem(int cod);
		void updateElem(int cod, Book newElem);
};

inline void FileRepo::writeToFile()
{
	ofstream f(this->filename);
	vector<Book> storage = this->getAll();
	if (f.is_open())
	{
		for (int i = 0; i < storage.size(); i++)
			f << storage[i] << endl;
	}
}

inline void FileRepo::loadFromFile()
{
	ifstream f(this->filename);
	if (f.is_open())
	{
		vector<Book> vEmpty;
		this->setStorage(vEmpty);
		string linie;
		string delim = " | ";

		while (getline(f, linie))
		{
			int pos = linie.find(delim);
			int cod = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			pos = linie.find(delim);
			char* autor = _strdup(linie.substr(0, pos).c_str());
			linie = linie.erase(0, pos + 3);

			pos = linie.find(delim);
			char* titlu = _strdup(linie.substr(0, pos).c_str());
			linie = linie.erase(0, pos + 3);

			pos = linie.find(delim);
			char* gen = _strdup(linie.substr(0, pos).c_str());
			linie = linie.erase(0, pos + 3);

			pos = linie.find(delim);
			int stoc = stoi(linie.substr(0, pos));
			linie = linie.erase(0, pos + 3);

			int pret = stoi(linie);

			Book bNew(titlu, autor, gen, stoc, pret);
			bNew.setCod(cod);
			vEmpty.push_back(bNew);
		}
		this->setStorage(vEmpty);
		f.close();
	}
}

inline FileRepo::FileRepo(): Repo<Book>()
{
}

inline FileRepo::FileRepo(string filenameGiven): Repo<Book>()
{
	this->filename = filenameGiven;
	this->loadFromFile();
}

inline FileRepo::~FileRepo()
{
}

inline void FileRepo::setFilename(string filenameGiven)
{
	this->filename = filenameGiven;
	this->loadFromFile();
}

inline string FileRepo::getFilename()
{
	return string();
}

inline int FileRepo::getDim()
{
	return 0;
}

inline FileRepo& FileRepo::operator=(const FileRepo& other)
{
	Repo<Book>::operator=(other);
	this->filename = other.filename;
	this->loadFromFile();
	return (*this);
}

inline void FileRepo::addElem(Book elem)
{
	Repo<Book>::addElem(elem);
	this->writeToFile();
}

inline void FileRepo::deleteElem(int cod)
{
	Repo<Book>::deleteElem(cod);
	this->writeToFile();
}

inline void FileRepo::updateElem(int cod, Book newElem)
{
	Repo<Book>::updateElem(cod, newElem);
	this->writeToFile();
}
