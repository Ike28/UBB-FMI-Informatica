#include "TestRepo.h"
#include "Repo.h"
#include "Book.h"
#include <assert.h>

void TestRepo::testRepo()
{
	Repo<Book> r1;
	assert(r1.getDim() == 0);

	Repo<Book> r2(r1);
	assert(r2.getDim() == 0);
}

void TestRepo::testAddElem()
{
	Repo<Book> r1;
	assert(r1.getDim() == 0);
	char autor[] = "H.P.Willmott", gen[] = "roman", titlu[] = "World War I";
	r1.addElem(Book(titlu, autor, gen, 500, 50));
	assert(r1.getDim() == 1 && r1.getAll()[0] == Book(titlu, autor, gen, 500, 50));
}

void TestRepo::testUpdateElem()
{
	Repo<Book> r1;
	assert(r1.getDim() == 0);
	char autor[] = "H.P.Willmott", gen[] = "roman", titlu[] = "World War I";
	r1.addElem(Book(titlu, autor, gen, 500, 50));
	char autor2[] = "Steven Zaloga";
	Book b2 = Book(titlu, autor, gen, 5000, 50);
	b2 = r1.getAll()[0];
	b2.setAutor(autor2);
	r1.updateElem(b2.getCod(), b2);
	assert(strcmp(r1.getAll()[0].getAutor(), autor2) == 0);
}

void TestRepo::testDeleteElem()
{
	Repo<Book> r1;
	char autor[] = "George Orwell", gen[] = "sci-fi", titlu[] = "1984";
	r1.addElem(Book(titlu, autor, gen, 500, 50));
	r1.deleteElem(r1.getAll()[0].getCod());
	assert(r1.getDim() == 0);
}

void TestRepo::testOperators()
{
	Repo<Book> r1;
	char autor[] = "George Orwell", gen[] = "sci-fi", titlu[] = "1984";
	r1.addElem(Book(titlu, autor, gen, 500, 50));
	Repo<Book> r2;
	r2 = r1;
	assert(r2.getDim() == 1);
}

void TestRepo::runTests()
{
	testRepo();
	testOperators();
	testAddElem();
	testUpdateElem();
	testDeleteElem();
}
