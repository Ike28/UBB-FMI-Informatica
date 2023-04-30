#include "TestPayment.h"
#include "TestRepo.h"
#include "TestService.h"
#include <iostream>
#include "Payment.h"
#include "Service.h"
#include "UserInterface.h"

using namespace std;

int main()
{
	TestPayment::runTests();
	TestRepo::runTests();
	TestService::runTests();

	cout << "\nTestele functioneaza!\n";

	UserInterface UI;
	UI.runInterface();
}
