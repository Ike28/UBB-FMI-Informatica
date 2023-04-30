#include "TestBook.h"
#include "TestRepo.h"
#include "TestService.h"
#include "TestRepoFile.h"
#include "TestBookValidator.h"
#include "Service.h"
#include "RepoFile.h"
#include "UI.h"
#include <iostream>

using namespace std;

int main()
{
	TestBook::runTests();
	TestRepo::runTests();
	TestService::runTests();
	TestRepoFile::runTests();
	TestBookValidator::runTests();
	cout << "\nMerg testele!\n";

	FileRepo repo("carti.txt");
	ServiceFile service(repo);
	UserInterface UI(service);
	UI.runInterface();
}