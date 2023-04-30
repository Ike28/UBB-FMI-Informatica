#pragma once
#include <Windows.h>
#include "Dreptunghi.h"

void copyIntToString(char* orig, int x);
void printMenu();
char getOption();
void citirePuncteEcuatie(char&x, char&y);
void citireDreptunghi(int& x1, int& y1, int& x2, int& y2);
void adaugare(Dreptunghi*& figuri, int& n, Dreptunghi dnew);
Dreptunghi citireDreptunghi();
void afisare(Dreptunghi* figuri, int n);
void dealocare(Dreptunghi*& figuri);
int citireNumar(const char* s);
int pozBiggestDreptunghi(Dreptunghi* figuri, int n);
void cadran1(Dreptunghi* figuri, int n, Dreptunghi*& rezultat, int& dim);
bool egaleDreptunghiuri(Dreptunghi* figuri, int i, int j);
void subsecvMaxima(Dreptunghi* figuri, int n, bool proprietate(Dreptunghi*, int, int), int& start, int& fin);
