#include "subalg.h"
#include <iostream>

using namespace std;

void citireNumar(int& x, const char* s)
{
    cout << s;
    cin >> x;
    cout << "\n";
}

void afisareNumar(int x, const char* s)
{
    cout << s << x << "\n";
}

int aLaRusse(int x, int y)
{
    if (x == 0)
        return 0;
    int result = 0;
    while (x > 0)
    {
        if (x % 2 == 1)
            result += y;
        x /= 2;
        y *= 2;
    }
    return result;
}
