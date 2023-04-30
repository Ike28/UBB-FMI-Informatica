#pragma once
#include <Windows.h>
#include "Dreptunghi.h"
#include <map>

using namespace std;

void copyIntToString(char* orig, int x);
void printMenu();
char getOption();
void citirePuncteEcuatie(char& x, char& y);
void citireDreptunghi(int& x1, int& y1, int& x2, int& y2);
void adaugare(map <int, Dreptunghi> &figuri, Dreptunghi dnew);
Dreptunghi citireDreptunghi();
void afisare(map <int, Dreptunghi> figuri);
void dealocare(Dreptunghi*& figuri);
int citireNumar(const char* s);
int pozBiggestDreptunghi(map <int, Dreptunghi> figuri);
void cadran1(map <int, Dreptunghi> figuri, map <int, Dreptunghi> &rezultat);
bool egaleDreptunghiuri(map <int, Dreptunghi> figuri, int i, int j);
void subsecvMaxima(map <int, Dreptunghi> figuri, bool proprietate(map <int, Dreptunghi>, int, int), int& start, int& fin);
