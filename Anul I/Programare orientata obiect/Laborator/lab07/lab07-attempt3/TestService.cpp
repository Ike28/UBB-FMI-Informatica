#include "TestService.h"
#include "Service.h"
#include "Payment.h"
#include <assert.h>

void TestService::testService()
{
	Service<Payment> s1;
	assert(s1.size() == 0);

	Repo<Payment> r1; char tip[] = "menaj";
	r1.addElem(Payment(tip, 1, 2));
	Service<Payment> s2(r1);
	assert(s2.size() == 1);
}

void TestService::testAdd()
{
	Service<Payment> s1; char tip[] = "jocuri video";
	s1.addElem(Payment(tip, 1, 2));
	assert(s1.size() == 1 && s1.read()[0] == Payment(tip, 1, 2));
}

void TestService::testDelete()
{
	Service<Payment> s1; char tip[] = "jocuri video";
	s1.addElem(Payment(tip, 1, 2));
	s1.addElem(Payment(tip, 3, 4));
	int idCautat = s1.read()[1].getID();
	s1.deleteByID(idCautat);
	assert(s1.size() == 1 && s1.read()[0] == Payment(tip, 1, 2));
}

void TestService::testUpdate()
{
	Service<Payment> s1; char tip[] = "jocuri video";
	s1.addElem(Payment(tip, 1, 2));
	int idCautat = s1.read()[0].getID();
	s1.updateByID(idCautat, Payment(tip, 5, 6));
	assert(s1.read()[0].getDay() == 5);
}

void TestService::testDeletions()
{
	Service<Payment> s1; char tip[] = "blabla"; char tip2[] = "prostie curata";
	s1.addElem(Payment(tip, 21, 100));
	s1.deleteByDay(21);
	assert(s1.size() == 0);
	s1.addElem(Payment(tip, 21, 100));
	s1.deleteByInterval(1, 20);
	assert(s1.size() == 1);
	s1.deleteByInterval(19, 25);
	assert(s1.size() == 0);
	s1.addElem(Payment(tip, 21, 100));
	s1.deleteByType(tip2);
	assert(s1.size() == 1);
	s1.deleteByType(tip);
	assert(s1.size() == 0);
}

void TestService::testList()
{
	Service<Payment> s1; char tip[] = "ceas gucci"; char tip2[] = "masini de lux";
	s1.addElem(Payment(tip2, 21, 100));
	vector<Payment> result = s1.listByType(tip, '=', 100);
	assert(result.size() == 0);
	result = s1.listByType(tip2, '>', 100);
	assert(result.size() == 0);
	result = s1.listByType(tip2, '=', 100);
	assert(result.size() == 1);
	result = s1.listByType(tip2, '-', 100);
	assert(result.size() == 1);
}

void TestService::testStats()
{
	Service<Payment> s1; char tip[] = "ceas gucci"; char tip2[] = "masini de lux";
	s1.addElem(Payment(tip2, 21, 100));
	s1.addElem(Payment(tip, 22, 100));
	s1.addElem(Payment(tip2, 21, 50));
	s1.addElem(Payment(tip2, 19, 40));
	pair<int, int> result = s1.maxDayBySums();
	assert(result.first == 21 && result.second == 150);

	int sum = s1.sumByType(tip2);
	assert(sum == 190);

	vector<pair<int, int>> result2 = s1.sortSumsByType(tip2);
	assert(result2[0].first == 19);
}

void TestService::testFilter()
{
	Service<Payment> s1; char tip[] = "ceas gucci"; char tip2[] = "masini de lux";
	s1.addElem(Payment(tip2, 21, 100));
	s1.addElem(Payment(tip, 22, 100));
	s1.addElem(Payment(tip2, 21, 50));
	s1.addElem(Payment(tip2, 19, 40));
	
	s1.filterByType(tip2, '>', 45);
	assert(s1.size() == 2);
}

void TestService::runTests()
{
	testService();
	testAdd();
	testDelete();
	testUpdate();
	testDeletions();
	testList();
	testStats();
	testFilter();
}
