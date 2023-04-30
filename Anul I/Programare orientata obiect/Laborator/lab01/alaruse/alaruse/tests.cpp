#include "tests.h"
#include "subalg.h"
#include <assert.h>

void testALaRusse()
{
	assert(aLaRusse(300, 300) == 90000);
	assert(aLaRusse(59, 87) == 5133);
	assert(aLaRusse(1, 1) == 1);
}
