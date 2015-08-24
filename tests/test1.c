#include <stdio.h>

#include "util/array_spread.h"
#include "emtest.h"

ARRAY_SPREAD_DECLARE(test_routine_t, all_tests);

static int test_func_1(void) {
	return 0;
}

ARRAY_SPREAD_ADD(all_tests, test_func_1);
