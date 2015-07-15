#include <stddef.h>
#include <stdio.h>

void (*all_tests[])(void) __attribute__((section(".array_spread.all_tests_0_head.rodata"))) = {};
void (*all_tests__tail[])(void) __attribute__((section(".array_spread.all_tests_9_tail.rodata"))) = {};

int main(void){
    int i;

    printf("%zu tests start\n", (size_t)(all_tests__tail - all_tests));

    for(i = 0; i < (size_t)(all_tests__tail - all_tests); i ++) {
        all_tests[i]();
    }
    return 0;
}
