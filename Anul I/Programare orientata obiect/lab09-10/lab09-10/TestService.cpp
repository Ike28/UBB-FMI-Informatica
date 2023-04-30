#include "TestService.h"
#include "Service.h"
#include "Book.h"
#include <assert.h>
#include <iostream>

void TestService::testService()
{
	Service<Book> s1;
	assert(s1.size() == 0);

	Repo<Book> r1; char autor[] = "George Orwell", gen[] = "sci-fi", titlu[] = "1984";
	r1.addElem(Book(titlu, autor, gen, 500, 50));
	Service<Book> s2(r1);
	assert(s2.size() == 1);
}

void TestService::testAdd()
{
	Service<Book> s1; char autor[] = "George Orwell", gen[] = "sci-fi", titlu[] = "1984";
	s1.addElem(Book(titlu, autor, gen, 500, 50));
	assert(s1.size() == 1 && s1.read()[0] == Book(titlu, autor, gen, 500, 50));
}

void TestService::testDelete()
{
	Service<Book> s1; char autor[] = "George Orwell", autor2[]="Alex O.", gen[] = "sci-fi", titlu[] = "1984";
	s1.addElem(Book(titlu, autor, gen, 500, 50));
	s1.addElem(Book(titlu, autor2, gen, 500, 50));
	int codCautat = s1.read()[1].getCod();
	s1.deleteElem(codCautat);
	assert(s1.size() == 1);
	assert(s1.read()[0] == Book(titlu, autor, gen, 500, 50));
}

void TestService::testUpdate()
{
	Service<Book> s1; char autor[] = "George Orwell", autor2[] = "Alex O.", gen[] = "sci-fi", titlu[] = "1984";
	s1.addElem(Book(titlu, autor, gen, 500, 50));
	int codCautat = s1.read()[0].getCod();
	s1.updateElem(codCautat, Book(titlu, autor2, gen, 50000, 50));
	assert(s1.read()[0].getStoc() == 50000);
	assert(strcmp(s1.read()[0].getAutor(), autor2) == 0);
}

void TestService::testOrderBooks()
{
	Service<Book> s1; char str[] = "yougotit", tip1[] = "dezvoltare personala", tip2[] = "arta", tip3[] = "fictiune";
	s1.addElem(Book(str, str, tip1, 500, 50));
	s1.addElem(Book(str, str, tip1, 400, 40));
	s1.addElem(Book(str, str, tip2, 6, 400));
	s1.addElem(Book(str, str, tip3, 50, 500));
	int pretTotal, reducere; vector<int> codes;
	codes.push_back(s1.read()[0].getCod());
	codes.push_back(s1.read()[1].getCod());
	codes.push_back(s1.read()[2].getCod());
	codes.push_back(s1.read()[3].getCod());
	s1.orderBooks(codes, pretTotal, reducere);
	assert(reducere == 15);
}

void TestService::runTests()
{
	testService();
	testAdd();
	testDelete();
	testUpdate();
	testOrderBooks();
}
