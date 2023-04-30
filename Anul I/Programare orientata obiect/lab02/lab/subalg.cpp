#include "subalg.h"
#include <iostream>
using namespace std;

void citire(int* v, int& n)
{
	int x;
	while (1)
	{
		cout << "\nIntroduceti lungimea listei: ";
		cin >> x;
		if (x < 1)
			cout << "\nLungimea trebuie sa fie cel putin 1. Reincercati!\n";
		else if (x > 100)
			cout << "\nLungimea poate fi maxim 100. Reincercati!\n";
		else break;
	} n = x;
	cout << "\nIntroduceti numerele separate prin spatiu: ";
	for (int i = 0; i < n; i++)
		cin >> v[i];
}

void afisare(int* v, int n)
{
	cout << "\nNumerele memorate in lista sunt: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	cout << "\n";
}

bool elementeInterval(int* v, int start, int fin, int a, int b)
{
	for (int i = start; i <= fin; i++)
		if (v[i]<a || v[i]>b)
			return false;
	return true;
}

bool diferenteAlternante(int* v, int start, int fin)
{
	bool last = (v[start] - v[fin] > 0);
	for (int i = start + 1; i < fin; i++)
	{
		if ((v[i] - v[i + 1] > 0) == last)
			return false;
		last = !last;
	}
	return true;
}

void secvMaximaInterval(int* v, int n, int& start, int& fin, int a, int b)
{
	int maxLungime = 0, maxStart = -1, maxFin = -1;
	for(int i=0; i<n; i++)
		for(int j=i; j<n; j++)
			if (elementeInterval(v, i, j, a, b) && j - i + 1 > maxLungime)
			{
				maxLungime = j - i + 1;
				maxStart = i;
				maxFin = j;
			}
	start = maxStart;
	fin = maxFin;
}

void secvMaximaSemne(int* v, int n, int& start, int& fin)
{
	int maxLungime = 0, maxStart = -1, maxFin = -1;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if (diferenteAlternante(v, i, j) && j - i + 1 > maxLungime)
			{
				maxLungime = j - i + 1;
				maxStart = i;
				maxFin = j;
			}
	start = maxStart;
	fin = maxFin;
}

