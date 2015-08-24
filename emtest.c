#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "util/array_spread.h"

#include "emtest.h"

ARRAY_SPREAD_DEF(struct test_case_desc *, all_tests);

int main(void){
    int i;
    struct test_case_desc *test;

    printf("%zu tests start", ARRAY_SPREAD_SIZE(all_tests));

    array_spread_foreach(test, all_tests) {
    	if (test->routine()) {
    		printf("error in test 0x%s\n", test->desc);
    		return 0;
    	}
    	printf(".");
    }
    printf("OK\n");

    return 0;
}
