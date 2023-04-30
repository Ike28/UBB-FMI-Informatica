#include "TestRepo.h"
#include "Repo.h"
#include "Payment.h"
#include <assert.h>
#include <string.h>

void TestRepo::testRepo()
{
	Repo<Payment> r1;
	assert(r1.getAll() == NULL && r1.getDim() == 0);

	Repo<Payment> r2 = r1;
	assert(r2.getAll() == NULL && r2.getDim() == 0);
}

void TestRepo::testAddElem()
{
	Repo<Payment> r1; char tip[] = "menaj";
	Payment elem(tip, 1, 2);
	r1.addElem(elem);
	assert(r1.getAll()[0] == elem);
}

void TestRepo::testGetDim()
{
	Repo<Payment> r1; char tip[] = "sambata seara";
	r1.addElem(Payment(tip, 1, 2));
	assert(r1.getDim() == 1);
}

void TestRepo::testOperators()
{
	Repo<Payment> r1; Repo<Payment> r2;
	char tip[] = "masaj";
	Payment elem(tip, 1, 2);
	r1.addElem(elem);
	r2 = r1;
	assert(r2.getDim() == 1 && r2.getAll()[0] == elem);
}

void TestRepo::testDelete()
{
	Repo<Payment> r1; char tip[] = "masaj";
	Payment p1(tip, 1, 2);
	r1.deleteByID(0);
	r1.addElem(p1);
	assert(r1.getDim() == 1);
	r1.deleteByID(r1.getAll()[0].getID());
	assert(r1.getDim() == 0);
}

void TestRepo::testUpdate()
{
	Repo<Payment> r1;
	char tip1[] = "menaj";
	char tip2[] = "masaj";
	Payment p1(tip1, 1, 2), p2(tip2, 3, 4);
	r1.addElem(p1); int iD = r1.getAll()[0].getID();
	r1.updateByID(iD, p2);
	assert(strcmp(r1.getAll()[0].getTip(), tip2) == 0);
}

void TestRepo::runTests()
{
	testRepo();
	testAddElem();
	testGetDim();
	testOperators();
	testDelete();
	testUpdate();
}
