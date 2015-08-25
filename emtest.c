#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "util/array_spread.h"

#include "emtest.h"

ARRAY_SPREAD_DEF(struct test_suite_desc *, all_tests);

int main(void){
    int i;
    const struct test_case_desc *test_case;
    struct test_suite_desc *test_suite;

    printf("%zu test suites start\n", ARRAY_SPREAD_SIZE(all_tests));

    array_spread_foreach(test_suite, all_tests) {
    	printf("%s", test_suite->desc);
    	array_spread_nullterm_foreach(test_case, test_suite->test_cases) {
			if (test_case->routine()) {
				printf("error in test 0x%s\n", test_case->desc);
				return 0;
			}
			printf(".");
    	}
    	printf("OK\n");
    }

    return 0;
}
