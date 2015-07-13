#include <stdio.h>

void test_func_1(void) {
	printf("test 1\n");
}
void test_func_2(void) {
	printf("test 2\n");
}

int main(void){
    int i;
    void (*all_tests[])(void) = {test_func_1, test_func_2};

    printf("%zu tests start\n", sizeof(all_tests)/sizeof(all_tests[0]));

    for(i = 0; i < sizeof(all_tests)/sizeof(all_tests[0]); i ++) {
        all_tests[i]();
    }
    return 0;
}
