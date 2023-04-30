#pragma once
#include "RepoFile.h"
#include "ServiceFile.h"
#include "BookValidator.h"

class ServiceFile
{
private:
	FileRepo repo;
	BookValidator validator;
public:
	ServiceFile();
	ServiceFile(FileRepo& repoDat);
	~ServiceFile();

	FileRepo& getRepo();
	void setRepo(FileRepo repoDat);
	int size();
	Book findByCod(int codDat);

	void addElem(Book elem);
	void deleteElem(int codDat);
	void updateElem(int codDat, Book elem);
	vector<Book> read();

	void orderBooks(vector<int> codes, int& pretTotal, int& reducere);

	ServiceFile& operator=(const ServiceFile& other);
};