#pragma once
#include "RepoCPU.h"

class TestRepoCPU
{
	private:
		static void testRepo();
		static void testAdd();
		static void testDelete();
		static void testUpdate();
	public:
		static void runTests();
};
