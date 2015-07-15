

#include <stdio.h>

void test_func_1(void) {
	printf("test 1\n");
}

void (*all_tests_item_1)(void) __attribute__((section(".array_spread.all_tests_1_body.rodata"))) = test_func_1;
