#include "tests.h"
#include <assert.h>
#include "subalg.h"

void testSecvMaximaSemneAlternante()
{
	int* v = new int[5]{ 1, 3, 2, 10, 5 };
	int inceput, fin;
	secvMaximaSemne(v, 4, inceput, fin);
	assert(inceput == 0);
	assert(fin == 4);
	int* u = new int[3]{ 1, 1, 1 };
	secvMaximaSemne(u, 3, inceput, fin);
	assert(inceput == -1);
}

void testSecvMaximaElementeInterval()
{
	int* v = new int[10]{ 1, -5, -99000, 5, 6, 11, 7, 8, 9, 10 };
	int inceput, fin;
	secvMaximaInterval(v, 9, inceput, fin, 1, 10);
	assert(inceput == 6);
	assert(fin == 9);
	secvMaximaInterval(v, 9, inceput, fin, 5, 8);
	assert(inceput == 3);
	assert(fin == 4);
	secvMaximaInterval(v, 9, inceput, fin, 100, 101);
	assert(inceput == -1);
}
