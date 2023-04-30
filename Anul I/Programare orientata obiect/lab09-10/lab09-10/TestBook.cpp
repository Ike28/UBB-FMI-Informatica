#include "Book.h"
#include "TestBook.h"
#include <assert.h>
#include <string.h>

void TestBook::testBook()
{
	Book b1;
	assert(b1.getAutor() == nullptr && b1.getGen() == nullptr && b1.getTitlu() == nullptr && b1.getStoc() == 0 && b1.getPret() == 0);

	char autor[] = "Lucian Blaga"; char gen[] = "poezii"; char titlu[] = "Poemele luminii";
	Book b2(titlu, autor, gen, 100, 50);
	assert(strcmp(b2.getAutor(), autor) == 0 && strcmp(b2.getGen(), gen) == 0 && strcmp(b2.getTitlu(), titlu) == 0 && b2.getStoc() == 100 && b2.getPret() == 50);

	Book b3(b2);
	assert(b3.getStoc() == 100);
	char autor2[] = "Stephen King", gen2[] = "fantasy", titlu2[] = "The Dark Tower";
	b3.setAutor(autor2); assert(strcmp(b3.getAutor(), autor2) == 0);
	b3.setGen(gen2); assert(strcmp(b3.getGen(), gen2) == 0);
	b3.setTitlu(titlu2); assert(strcmp(b3.getTitlu(), titlu2) == 0);
	b3.setStoc(5000); assert(b3.getStoc() == 5000);
	b3.setPret(30); assert(b3.getPret() == 30);
}

void TestBook::runTests()
{
	testBook();
}
