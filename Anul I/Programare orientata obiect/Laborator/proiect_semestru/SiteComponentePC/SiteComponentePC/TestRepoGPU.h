#pragma once
#include "RepoGPU.h"

class TestRepoGPU
{
	private:
		static void testRepo();
		static void testAdd();
		static void testDelete();
		static void testUpdate();
	public:
		static void runTests();
};
