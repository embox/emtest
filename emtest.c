#include <stddef.h>
#include <stdio.h>

#include "util/array_spread.h"

#include "emtest.h"

ARRAY_SPREAD_DEF(test_routine_t,all_tests);

int main(void){
    int i;
    void (*test) (void);

    printf("%zu tests start\n", ARRAY_SPREAD_SIZE(all_tests));

    array_spread_foreach(test, all_tests) {
    	test();
    }

    return 0;
}
