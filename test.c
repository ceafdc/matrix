#include <string.h>
#include <stdlib.h>
#include "test.h"

Test *
test_append(Test *tests, int (*test_func)(void), char *name) {
    Test *test = (Test *)malloc(sizeof(Test));
    test-> test_func = test_func;
    strcpy(test->name, name);
    test->next = tests;

    return test;
}

void
test_free(Test *tests) {
    while(tests) {
        Test *next = tests->next;
        free(tests);
        tests = next;
    }
}
