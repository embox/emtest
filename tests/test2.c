

#include <stdio.h>

static void test_func_2(void) {
	printf("test 2\n");
}

static void (*all_tests_item_2)(void) __attribute__((used,
		section(".array_spread.all_tests_1_body.rodata,\"a\",%progbits;#"))) = test_func_2;
