#pragma once

class TestService
{
	private:
		static void testCRUDCPU();
		static void testCRUDGPU();
		static void testCRUDRAM();
		static void testCRUDMBD();
		static void testSearch();
		static void testFilter();
		static void testSort();
	public:
		static void runTests();
};
