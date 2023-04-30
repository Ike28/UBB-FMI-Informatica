#include "TestPayment.h"
#include "Payment.h"
#include <assert.h>
#include <string.h>

void TestPayment::testPayment()
{
	Payment c1;
	assert(c1.getTip() == nullptr && c1.getDay() == 0 && c1.getSum() == 0);

	char tip[] = "coafor";
	Payment c2(tip, 1, 2);
	assert(strcmp(c2.getTip(), tip) == 0 && c2.getDay() == 1 && c2.getSum() == 2);

	Payment c3 = c2;
	assert(strcmp(c2.getTip(), c3.getTip()) == 0 && c3.getDay() == 1 && c3.getSum() == 2);
}

void TestPayment::testOperators()
{
	char tip[] = "jocuri de noroc";
	Payment c1(tip, 1, 2), c2(tip, 1, 2);
	assert(c1 == c2);

	Payment c3 = c2;
	assert(c3 == c2);
}

void TestPayment::runTests()
{
	testPayment();
	testOperators();
}
