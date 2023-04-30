#pragma once
#include "RepoMotherboard.h"

class TestRepoMBD
{
	private:
		static void testRepo();
		static void testAdd();
		static void testDelete();
		static void testUpdate();
	public:
		static void runTests();
};
