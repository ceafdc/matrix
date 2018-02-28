#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"
#include "matrix.h"

int
test_fill() {
    matrix *A = matrix_create_empty(1000, 100);
    double value = 3.1415926535;
    matrix_fill(A, value);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            if (A->data[i][j] != value) {
                matrix_free(A);
                return 1;
            }
        }
    }

    matrix_free(A);
    return 0;
}

int
test_zeros_and_ones() {
    matrix *A = matrix_create_zeros(200, 300);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            if (A->data[i][j] != 0) {
                matrix_free(A);
                return 1;
            }
        }
    }

    matrix_free(A);
    A = matrix_create_ones(200, 300);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            if (A->data[i][j] != 1) {
                matrix_free(A);
                return 1;
            }
        }
    }

    matrix_free(A);
    return 0;
}

int
test_eq() {
    matrix *A = matrix_create_va(2, 3,
        1, 2, 3,
        4, 5, 6
        );

    matrix *B = matrix_create_va(3, 2,
        1, 2,
        3, 4,
        5, 6
        );

    if (matrix_eq(A, B)) {
        matrix_free(A);
        matrix_free(B);
        return 1;
    }

    matrix_free(A);
    matrix_free(B);

    A = matrix_create_va(3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );
    B = matrix_create_va(3, 3,
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
        );

    if (!matrix_eq(A, B)) {
        matrix_free(A);
        matrix_free(B);
        return 1;
    }

    matrix_free(A);
    matrix_free(B);
    return 0;
}

int
test_mult() {
    matrix *A = matrix_create_va(2, 3,
        1, 2, 3,
        4, 5, 6
        );

    matrix *B = matrix_create_va(3, 2,
        1, 2,
        3, 4,
        5, 6
        );

    matrix *C = matrix_mult(A, B);
    matrix *E = matrix_create_va(2, 2,
        22, 28,
        49, 64
        );

    if (!matrix_eq(C, E)) {
        matrix_free(A);
        matrix_free(B);
        matrix_free(C);
        matrix_free(E);
        return 1;
    }

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(E);

    return 0;
}


int
make_tests() {
    int error = 0;
    Test *tests = NULL;
    tests = test_append(tests, test_eq, "Teste de igualdade");
    tests = test_append(tests, test_mult, "Teste de multiplicação");
    tests = test_append(tests, test_zeros_and_ones, "Teste de zeros e uns");
    tests = test_append(tests, test_fill, "Teste de fill");

    Test *test_iter = tests;

    while (test_iter) {
        int this_result = test_iter->test_func();
        error |= this_result;
        printf("%s %s\n", test_iter->name, this_result ? "not passed" : "passed");
        test_iter = test_iter->next;
    }


    if (!error) {
        printf("\nALL TESTS PASSED\n\n");
    }

    test_free(tests);

    return error;
}

int
main(int argc, char *argv[]) {
    return make_tests();
}
