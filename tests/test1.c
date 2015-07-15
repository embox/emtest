

#include <stdio.h>

static void test_func_1(void) {
	printf("test 1\n");
}

static void (*all_tests_item_1)(void) __attribute__((used,
		section(".array_spread.all_tests_1_body.rodata,\"a\",%progbits;#")))= test_func_1;
