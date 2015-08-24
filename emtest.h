#ifndef EMTEST_H_
#define EMTEST_H_

typedef int (*test_routine_t)(void);

struct test_case_desc {
	test_routine_t routine;
	char desc[];
};

#include <util/array_spread.h>
#include <util/macro.h>

ARRAY_SPREAD_DECLARE(struct test_case_desc *, all_tests);

#define TEST_CASE(desc) \
	__TEST_CASE_NM("" desc, MACRO_GUARD(__test_case_struct), \
					MACRO_GUARD(__test_case))

#define __TEST_CASE_NM(_desc, test_struct, test_func) \
	static int test_func(void);                      \
	static struct test_case_desc test_struct = { \
			.routine = test_func, \
			.desc = _desc,         \
	};                             \
	ARRAY_SPREAD_ADD(all_tests, &test_struct); \
	static int test_func(void)

#endif /* EMTEST_H_ */
