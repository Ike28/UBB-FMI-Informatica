#include "ServiceFile.h"
#include "InvalidIDException.h"

ServiceFile::ServiceFile()
{

}

ServiceFile::ServiceFile(FileRepo& repoDat)
{
	this->repo = repoDat;
}

ServiceFile::~ServiceFile()
{
}

FileRepo& ServiceFile::getRepo()
{
	return this->repo;
}

void ServiceFile::setRepo(FileRepo repoDat)
{
	this->repo = repoDat;
}

int ServiceFile::size()
{
	return this->repo.getDim();
}

Book ServiceFile::findByCod(int codDat)
{
	return this->repo.findByID(codDat);
}

void ServiceFile::addElem(Book elem)
{
	this->validator.validate(elem);
	this->repo.addElem(elem);
}

void ServiceFile::deleteElem(int codDat)
{
	if (this->findByCod(codDat).getAutor() == nullptr)
		throw InvalidIDException("\nCod invalid.");
	this->repo.deleteElem(codDat);
}

void ServiceFile::updateElem(int codDat, Book elem)
{
	this->validator.validate(elem);
	if (this->findByCod(codDat).getAutor() == nullptr)
		throw InvalidIDException("\nCod invalid.");
	this->repo.updateElem(codDat, elem);
}

vector<Book> ServiceFile::read()
{
	return this->repo.getAll();
}

void ServiceFile::orderBooks(vector<int> codes, int& pretTotal, int& reducere)
{
	for (vector<int>::iterator i = codes.begin(); i != codes.end(); i++)
		if (this->findByCod((*i)).getAutor() == nullptr)
			throw InvalidIDException("\nCod invalid.");
	pretTotal = 0;  reducere = 0;
	vector<Book> books = this->repo.getAll(); Book bAux;
	char dezvPers[] = "dezvoltare personala", fict[] = "fictiune", art[] = "arta";
	int dezvBooks = 0, fictBooks = 0, artBooks = 0;
	for (int i = 0; i < codes.size(); i++)
	{
		for (int j = 0; j < books.size(); j++)
			if (books[j].getCod() == codes[i])
			{
				bAux = books[j];
				int stoc = bAux.getStoc();
				bAux.setStoc(stoc - 1);
				this->repo.updateElem(bAux.getCod(), bAux);
				pretTotal += bAux.getPret();
				if (strcmp(bAux.getGen(), dezvPers) == 0)
					dezvBooks++;
				if (strcmp(bAux.getGen(), fict) == 0)
					fictBooks++;
				if (strcmp(bAux.getGen(), art) == 0)
					artBooks++;
			}
	}
	if (artBooks > 0 && fictBooks > 0)
		reducere += 18;
	if (dezvBooks > 1)
		reducere += 15;
}

ServiceFile& ServiceFile::operator=(const ServiceFile& other)
{
	this->repo = other.repo;
	return *this;
}
