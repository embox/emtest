#include <stdio.h>

#include "util/array_spread.h"
#include "emtest.h"

ARRAY_SPREAD_DECLARE(test_routine_t, all_tests);

static void test_func_2(void) {
	printf("test 2\n");
}

ARRAY_SPREAD_ADD(all_tests, test_func_2);
ARRAY_SPREAD_ADD(all_tests, test_func_2);
