#include "tests.h"
#include "problem.h"
#include <assert.h>

void testDeterminareVecinFibo()
{
	assert(determinareVecinFibo(1) == 2);
	assert(determinareVecinFibo(15) == 21);
	assert(determinareVecinFibo(300) == 377);
}
