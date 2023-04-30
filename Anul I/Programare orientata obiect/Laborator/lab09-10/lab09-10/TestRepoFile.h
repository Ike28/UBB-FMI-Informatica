#pragma once
#include "TestRepo.h"
class TestRepoFile : TestRepo
{
private:
	static void testFileRepo();
	static void testAddElem();
	static void testUpdateElem();
	static void testDeleteElem();
	static void testOperators();
public:
	static void runTests();
};