#include "TestBookValidator.h"
#include "BookValidator.h"
#include "ServiceFile.h"
#include "PriceException.h"
#include "NameException.h"
#include "StockException.h"
#include "InvalidIDException.h"
#include "Book.h"
#include <assert.h>

void TestBookValidator::testValidate()
{
	BookValidator BV;
	Book b1("titlu", "autor", "gen", 50, 0);
	bool ok = false;
	try {
		BV.validate(b1);
	}
	catch (PriceException pe)
	{
		ok = true;
	}
	assert(ok == true);

	Book b2("", "autor", "gen", 50, 80);
	ok = false;
	try {
		BV.validate(b2);
	}
	catch (NameException ne)
	{
		ok = true;
	}
	assert(ok == true);

	Book b3("titlu", "autor", "gen", -1, 80);
	ok = false;
	try {
		BV.validate(b3);
	}
	catch (StockException se)
	{
		ok = true;
	}
	assert(ok == true);
}

void TestBookValidator::testServiceExceptions()
{
	ofstream f("test_file2.txt");
	f.close();
	FileRepo repo("test_file2.txt");
	ServiceFile s1(repo);
	s1.addElem(Book("titlu", "autor", "gen", 450, 50));
	int idExistent = s1.read()[0].getCod();
	bool ok = false;
	try {
		s1.deleteElem(idExistent + 1);
	}
	catch (InvalidIDException ie)
	{
		ok = true;
	}
	assert(ok == true);
}

void TestBookValidator::runTests()
{
	testValidate();
	testServiceExceptions();
}
