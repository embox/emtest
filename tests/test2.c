

#include <stdio.h>

void test_func_2(void) {
	printf("test 2\n");
}

void (*all_tests_item_2)(void) __attribute__((section(".array_spread.all_tests_1_body.rodata"))) = test_func_2;
