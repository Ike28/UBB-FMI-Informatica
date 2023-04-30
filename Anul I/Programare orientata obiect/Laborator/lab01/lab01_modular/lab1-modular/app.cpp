#include "problem.h"
#include "tests.h"
#include <iostream>

using namespace std;

int main()
{
    testDeterminareVecinFibo();
    int n;
    citireNumar(n);
    int nextNumber = determinareVecinFibo(n);
    afisareNumar(nextNumber);
    return 0;
}
