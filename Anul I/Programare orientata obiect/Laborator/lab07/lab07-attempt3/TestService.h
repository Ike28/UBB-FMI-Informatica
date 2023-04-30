#pragma once

class TestService
{
	private:
		static void testService();
		static void testAdd();
		static void testDelete();
		static void testUpdate();
		static void testDeletions();
		static void testList();
		static void testStats();
		static void testFilter();
	public:
		static void runTests();
};
