#pragma once
#include "RepoRAM.h"

class TestRepoRAM
{
	private:
		static void testRepo();
		static void testAdd();
		static void testDelete();
		static void testUpdate();
	public:
		static void runTests();
};
