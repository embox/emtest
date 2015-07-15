#include <stddef.h>
#include <stdio.h>

static void (*all_tests[])(void) __attribute__((used,
		section(".array_spread.all_tests_0_head.rodata,\"a\",%progbits;#"))) = {};
static void (*all_tests__tail[])(void) __attribute__((used,
		section(".array_spread.all_tests_9_tail.rodata,\"a\",%progbits;#"))) = {};

int main(void){
    int i;

    printf("%zu tests start\n", (size_t)(all_tests__tail - all_tests));

    for(i = 0; i < (size_t)(all_tests__tail - all_tests); i ++) {
        all_tests[i]();
    }
    return 0;
}
