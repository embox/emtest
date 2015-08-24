#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#include "util/array_spread.h"

#include "emtest.h"

ARRAY_SPREAD_DEF(test_routine_t,all_tests);

int main(void){
    int i;
    test_routine_t test;

    printf("%zu tests start", ARRAY_SPREAD_SIZE(all_tests));

    array_spread_foreach(test, all_tests) {
    	if (test()) {
    		printf("error in test 0x%zu\n", (uintptr_t)test);
    		return 0;
    	}
    	printf(".");
    }
    printf("OK\n");

    return 0;
}
