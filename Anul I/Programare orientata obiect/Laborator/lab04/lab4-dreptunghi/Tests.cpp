#include "Tests.h"
#include "Punct.h"
#include "Dreptunghi.h"
#include <assert.h>
#include <Windows.h>
#include "utils.h"

void Tests::testPunct()
{
	Punct p1;
	assert(p1.getX() == 0 && p1.getY() == 0);
	
	Punct p2(5, 3);
	assert(p2.getX() == 5 && p2.getY() == 3);
}

void Tests::testDreptunghi()
{
	Dreptunghi d1;
	assert(d1.getFigura() == NULL);

	Dreptunghi d2(0, 0, 3, 2);
	assert(d2.getPunctA().getX() == 0 && d2.getPunctA().getY() == 0);
	assert(d2.getPunctC().getX() == 3 && d2.getPunctC().getY() == 2);
	assert(d2.getPunctB().getX() == 0 && d2.getPunctB().getY() == 2);
	assert(d2.getPunctD().getX() == 3 && d2.getPunctD().getY() == 0);
	assert(d2.aria() == 6);
	assert(d2.perimetrul() == 10);

	Dreptunghi d3 = d2;
	assert(d3.getPunctC().getX() == 3 && d3.getPunctC().getY() == 2);

	d3.setPunctC(4, 5);
	assert(d3.getPunctC().getX() == 4 && d3.getPunctC().getY() == 5);
	assert(d3.getLungime() == 5);
	assert(d3.getLatime() == 4);
	assert(d3.aria() == 20);
	assert(d3.perimetrul() == 18);
}

void Tests::testAdaugare()
{
	Dreptunghi* testFiguri = nullptr; int n = 0;
	adaugare(testFiguri, n, Dreptunghi(1, 9, 5, 7));
	assert(n == 1);
}

void Tests::testBiggest()
{
	Dreptunghi* tF = new Dreptunghi[3]{ Dreptunghi(1,1,-2,-2), Dreptunghi(3,3,-2,-2), Dreptunghi(2,2,-2,-2) };
	assert(pozBiggestDreptunghi(tF, 3) == 1);
	delete[] tF; tF = nullptr;
}

void Tests::testCadran1()
{
	Dreptunghi* tF = new Dreptunghi[3]{ Dreptunghi(8,17,16,8), Dreptunghi(-6,12,-3,9), Dreptunghi(-9,7,-6,4) };
	Dreptunghi* tR = nullptr; int dim = 0;
	cadran1(tF, 3, tR, dim);
	assert(dim == 1);
	//assert(tR[0] == Dreptunghi(8, 17, 16, 8));
	delete[] tF; tF = nullptr;
	delete[] tR; tR = nullptr;
}

void Tests::testSubsecv()
{
	Dreptunghi* tF = new Dreptunghi[3]{ Dreptunghi(2,6,5,3), Dreptunghi(8,5,11,2), Dreptunghi(14,7,17,4) };
	int i, j;
	subsecvMaxima(tF, 3, egaleDreptunghiuri, i, j);
	assert(i == 0 && j == 2);
	delete[] tF; tF = nullptr;
}
