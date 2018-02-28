#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "test.h"
#include "matrix.h"

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int tests_run = 0;

int
test_fill() {
    matrix *A = matrix_create_empty(1000, 100);
    double value = 3.1415926535;
    matrix_fill(A, value);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            _assert(A->data[i][j] == value);
        }
    }

    matrix_free(A);
    return 0;
}

int test_copy() {
    matrix *A = matrix_create_va(5, 4,
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand()
    );
    matrix *B = matrix_copy(A);
    _assert(A != B);

        for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            _assert(A->data[i][j] == B->data[i][j]);
        }
    }

    matrix_free(A);
    matrix_free(B);
    return 0;
}

int
test_zeros_and_ones() {
    matrix *A = matrix_create_zeros(200, 300);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            _assert(A->data[i][j] == 0);
        }
    }

    matrix_free(A);
    A = matrix_create_ones(200, 300);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            _assert(A->data[i][j] == 1);
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

    _assert(!matrix_eq(A, B));

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

    _assert(matrix_eq);

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

    _assert(matrix_eq(C, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(E);

    return 0;
}


int
make_tests() {
    _verify(test_eq);
    _verify(test_mult);
    _verify(test_zeros_and_ones);
    _verify(test_fill);
    _verify(test_copy);
    return 0;
}

int
main(int argc, char *argv[]) {
    srand(time(NULL));

    int result = make_tests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return make_tests();
}
