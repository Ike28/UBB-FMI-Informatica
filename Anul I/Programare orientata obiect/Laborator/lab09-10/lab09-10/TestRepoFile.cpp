#include "TestRepoFile.h"
#include "RepoFile.h"
#include <assert.h>

void TestRepoFile::testFileRepo()
{
	TestRepo::testRepo();
	FileRepo r1;
	assert(r1.getFilename() == "");
}

void TestRepoFile::testAddElem()
{
	TestRepo::testAddElem();
	FileRepo r1("test_file1.txt");
	char autor[] = "blabla";
	r1.addElem(Book(autor, autor, autor, 50, 30));
	FileRepo r2("test_file1.txt");
	assert(r2.getDim() == 0);
}

void TestRepoFile::testUpdateElem()
{
	TestRepo::testUpdateElem();
	ofstream f("test_file1.txt");
	f.close();
	FileRepo r1("test_file1.txt");
	char str[] = "blublu";
	r1.addElem(Book(str, str, str, 50, 100));
	int i = r1.getAll()[0].getCod();
	r1.updateElem(i, Book(str, str, str, 60, 100));
	FileRepo r2("test_file1.txt");
	assert(r2.getAll()[0].getStoc() == 60);
}

void TestRepoFile::testDeleteElem()
{
	TestRepo::testDeleteElem();
	ofstream f("test_file1.txt");
	f.close();
	FileRepo r1("test_file1.txt");
	char str[] = "blublu";
	r1.addElem(Book(str, str, str, 50, 100));
	int i = r1.getAll()[0].getCod();
	r1.deleteElem(i);
	FileRepo r2("test_file1.txt");
	assert(r2.getDim() == 0);
}

void TestRepoFile::testOperators()
{
	TestRepo::testOperators;
	FileRepo r1("test_file1.txt"), r2("test_file2.txt");
	r1 = r2;
	assert(r1.getFilename() == r2.getFilename());
}

void TestRepoFile::runTests()
{
	testFileRepo();
	testOperators();
	testAddElem();
	testDeleteElem();
	testUpdateElem();
}
