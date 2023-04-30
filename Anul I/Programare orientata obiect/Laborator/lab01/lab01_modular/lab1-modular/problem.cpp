#include <iostream>
#include "problem.h"

using namespace std;

void citireNumar(int& x)
{
    cout << "Dati numarul: ";
    cin >> x;
    cout << "\n";
}

void afisareNumar(int x)
{
    cout << "Numarul cautat este: " << x << "\n";
}

int determinareVecinFibo(int x)
{
    if (x < 1)
        return 1;
    int f1 = 1, f2 = 1, f3;
    do {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    } while (f3 <= x);
    return f3;
}
