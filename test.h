#ifndef test_h
#define test_h

typedef struct test {
    int (*test_func)();
    char name[100];
    struct test *next;
} Test;

Test *test_append(Test *tests, int (*test_func)(void), char *name);
void test_free(Test *tests);

#endif
