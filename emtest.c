#include <stddef.h>
#include <stdio.h>

void test_func_1(void) {
	printf("test 1\n");
}
void test_func_2(void) {
	printf("test 2\n");
}

void (*all_tests_item_1)(void) __attribute__((section(".array_spread.all_tests_1_body.rodata"))) = test_func_1;
void (*all_tests_item_2)(void) __attribute__((section(".array_spread.all_tests_1_body.rodata"))) = test_func_2;
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
