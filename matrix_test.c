#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <math.h>
#include "matrix.h"

#define FAIL() printf("\nfailure in %s() line %d\n", __func__, __LINE__)
#define _assert(test) do { if (!(test)) { FAIL(); return 1; } } while(0)
#define _verify(test) do { int r=test(); tests_run++; if(r) return r; } while(0)

int tests_run = 0;

int
test_delete() {
    matrix *A, *B, *C;
    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    _assert(matrix_delete_col(A, 10) == NULL);
    B = matrix_delete_col(A, 2);
    C = matrix_create_va(5, 4,
         3.0, -7.0,  7.0,  9.0,
         8.0,  2.0, -9.0, -7.0,
         4.0, -1.0,  0.0,  8.0,
         7.0,  7.0, -6.0, -6.0,
         3.0,  2.0,  8.0, -5.0
        );
    _assert(matrix_eq(B, C));
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    _assert(matrix_delete_row(A, 10) == NULL);
    B = matrix_delete_row(A, 2);
    C = matrix_create_va(4, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    _assert(matrix_eq(B, C));
    matrix_free(A);
    matrix_free(B);
    matrix_free(C);

    return 0;
}

int
test_swap() {
    matrix *A, *B, *C;

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    B = matrix_copy(A);
    matrix_swap_col_inplace(B, 9, 10);  // test columns greater than matrix size
    _assert(matrix_eq(A, B));

    matrix_swap_col_inplace(B, 0, 2);  // test columns greater than matrix size
    C = matrix_create_va(5, 5,
         -6.0, -7.0, 3.0,  7.0,  9.0,
          9.0,  2.0, 8.0, -9.0, -7.0,
          8.0, -1.0, 4.0,  0.0,  8.0,
          0.0,  7.0, 7.0, -6.0, -6.0,
         -3.0,  2.0, 3.0,  8.0, -5.0
        );
    _assert(matrix_eq(B, C));
    matrix_free(C);
    matrix_swap_row_inplace(B, 0, 2);
    C = matrix_create_va(5, 5,
          8.0, -1.0, 4.0,  0.0,  8.0,
          9.0,  2.0, 8.0, -9.0, -7.0,
          -6.0, -7.0, 3.0,  7.0,  9.0,
          0.0,  7.0, 7.0, -6.0, -6.0,
         -3.0,  2.0, 3.0,  8.0, -5.0
        );

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);

    return 0;
}

int
test_determinant() {
    matrix *A;
    double determinant;
    double expected;
    A = matrix_create_va(1, 1,
        3.0);
    determinant = matrix_determinant(A);
    expected = 3;
    _assert(fabs(determinant - expected) <= DBL_EPSILON);
    matrix_free(A);


    A = matrix_create_va(2, 2,
        3.0, -4.0,
        -1.1, -9.0
        );
    determinant = matrix_determinant(A);
    expected = -31.4;
    _assert(fabs(determinant - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(3, 3,
        3.0, -4.0, -666.0,
        -1.1, -9.0, -999.0,
        3.14, -6.8, 0.0
        );
    determinant = matrix_determinant(A);
    expected = -31635;
    _assert(fabs(determinant - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );

    determinant = matrix_determinant(A);
    expected = -108695;
    _assert(fabs(determinant - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0, -7.0,  9.0,
         8.0,  2.0,  9.0,  2.0, -7.0,
         4.0, -1.0,  8.0, -1.0,  8.0,
         7.0,  7.0,  0.0,  7.0, -6.0,
         3.0,  2.0, -3.0,  2.0, -5.0
        );

    determinant = matrix_determinant(A);
    expected = 0;
    _assert(fabs(determinant - expected) <= DBL_EPSILON);
    matrix_free(A);

    return 0;
}

int
test_cofactor() {
    matrix *A;
    double cofactor;
    double expected;

    A = matrix_create_va(2, 2,
        1.0, 2.0,
        3.0, 4.0
        );
    cofactor = matrix_cofactor(A, 0, 0);
    expected = 4.0;
    _assert(fabs(cofactor - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(3, 3,
        1.0, 2.0, 66.0,
        3.0, 4.0, 22.1,
        -3.14, 3.14, 142.0
        );
    cofactor = matrix_cofactor(A, 1, 2);
    expected = -9.42;
    _assert(fabs(cofactor - expected) <= DBL_EPSILON);

    cofactor = matrix_cofactor(A, 2, 2);
    expected = -2;
    _assert(fabs(cofactor - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );

    cofactor = matrix_cofactor(A, 3, 2);
    expected = 6933;
    _assert(fabs(cofactor - expected) <= DBL_EPSILON);
    matrix_free(A);
    return 0;
}

int
test_minor() {
    matrix *A;
    double minor;
    double expected;

    A = matrix_create_va(2, 2,
        1.0, 2.0,
        3.0, 4.0
        );
    minor = matrix_minor(A, 0, 0);
    expected = 4.0;
    _assert(fabs(minor - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(3, 3,
        1.0, 2.0, 66.0,
        3.0, 4.0, 22.1,
        -3.14, 3.14, 142.0
        );
    minor = matrix_minor(A, 1, 2);
    expected = 9.42;
    _assert(fabs(minor - expected) <= DBL_EPSILON);

    minor = matrix_minor(A, 2, 2);
    expected = -2;
    _assert(fabs(minor - expected) <= DBL_EPSILON);
    matrix_free(A);

    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );

    minor = matrix_minor(A, 3, 2);
    expected = -6933;
    _assert(fabs(minor - expected) <= DBL_EPSILON);
    matrix_free(A);
    return 0;
}

int
test_singular() {
    matrix *A;
    A = matrix_create_va(5, 5,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         4.0, -1.0,  8.0,  0.0,  8.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    _assert(!matrix_is_singular(A));
    matrix_free(A);
    A = matrix_create_va(5, 5,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0, -7.0, -6.0,  7.0,  9.0,
         8.0,  2.0,  9.0, -9.0, -7.0,
         7.0,  7.0,  0.0, -6.0, -6.0,
         3.0,  2.0, -3.0,  8.0, -5.0
        );
    _assert(matrix_is_singular(A));
    matrix_free(A);

    return 0;
}

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
        (double)rand(), (double)rand(), (double)rand(), (double)rand(),
        (double)rand(), (double)rand(), (double)rand(), (double)rand(),
        (double)rand(), (double)rand(), (double)rand(), (double)rand(),
        (double)rand(), (double)rand(), (double)rand(), (double)rand(),
        (double)rand(), (double)rand(), (double)rand(), (double)rand()
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

double
f(double v) {
    return v * v;
}

int
test_map() {
    matrix *A = matrix_create_empty(19, 37);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            A->data[i][j] = 10 * ((float)rand()/(float)RAND_MAX);
        }
    }

    matrix *B = matrix_copy(A);
    matrix_map(A, f);

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j< A->n; j++) {
            B->data[i][j] = f(B->data[i][j]);
        }
    }

    _assert(matrix_eq(A, B));

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
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
        );

    matrix *B = matrix_create_va(3, 2,
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
        );

    _assert(!matrix_eq(A, B));

    matrix_free(A);
    matrix_free(B);

    A = matrix_create_va(3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );
    B = matrix_create_va(3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    _assert(matrix_eq(A, B));

    matrix_free(A);
    matrix_free(B);

    A = matrix_create_va(3, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );
    B = matrix_create_va(3, 3,
        1.0, 2.0, -3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
        );

    _assert(!matrix_eq(A, B));

    matrix_free(A);
    matrix_free(B);
    return 0;
}

int
test_add() {
    matrix *A = matrix_create_va(3, 4,
        3.0, 13.0, 5.0, 2.0,
        213.0, 13.0, 53.0, -12.0,
        123.0, 3.14, 12.0, 42.0
        );
    matrix *B = matrix_create_va(3, 4,
        31.0, 21.0, 5423.0, 102.0,
        999.0, 0.0, 53.31, 12.0,
        666.0, 6.28, 2.71828, -123.0
        );

    matrix *C = matrix_add(A, B);
    matrix *E = matrix_create_va(3, 4,
        34.0, 34.0, 5428.0, 104.0,
        1212.0, 13.0, 106.31, 0.0,
        789.0, 9.42, 14.71828, -81.0
        );
    _assert(matrix_eq(C, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(E);

    return 0;
}

int
test_add_inplace() {
    matrix *A = matrix_create_va(3, 4,
        3.0, 13.0, 5.0, 2.0,
        213.0, 13.0, 53.0, -12.0,
        123.0, 3.14, 12.0, 42.0
        );
    matrix *B = matrix_create_va(3, 4,
        31.0, 21.0, 5423.0, 102.0,
        999.0, 0.0, 53.31, 12.0,
        666.0, 6.28, 2.71828, -123.0
        );

    matrix_add_inplace(A, B);
    matrix *E = matrix_create_va(3, 4,
        34.0, 34.0, 5428.0, 104.0,
        1212.0, 13.0, 106.31, 0.0,
        789.0, 9.42, 14.71828, -81.0
        );
    _assert(matrix_eq(A, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(E);

    return 0;
}

int
test_sub() {
    matrix *A = matrix_create_va(3, 4,
        3.0, 13.0, 5.0, 2.0,
        213.0, 13.0, 53.0, -12.0,
        123.0, 3.14, 12.0, 42.0
        );
    matrix *B = matrix_create_va(3, 4,
        31.0, 21.0, 5423.0, 102.0,
        999.0, 1.0, 53.0, 12.0,
        666.0, 6.28, 2.71828, -123.0
        );

    matrix *C = matrix_sub(A, B);
    matrix *E = matrix_create_va(3, 4,
    -2.80000e+01, -8.00000e+00, -5.41800e+03, -1.00000e+02,
    -7.86000e+02,  12.0, 0.0, -2.40000e+01,
    -5.43000e+02, -3.14000e+00,  9.28172e+00,  1.65000e+02
        );
    _assert(matrix_eq(C, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(E);

    return 0;
}

int
test_sub_inplace() {
    matrix *A = matrix_create_va(3, 4,
        3.0, 13.0, 5.0, 2.0,
        213.0, 13.0, 53.0, -12.0,
        123.0, 3.14, 12.0, 42.0
        );
    matrix *B = matrix_create_va(3, 4,
        31.0, 21.0, 5423.0, 102.0,
        999.0, 1.0, 53.0, 12.0,
        666.0, 6.28, 2.71828, -123.0
        );

    matrix_sub_inplace(A, B);
    matrix *E = matrix_create_va(3, 4,
    -2.80000e+01, -8.00000e+00, -5.41800e+03, -1.00000e+02,
    -7.86000e+02,  12.0, 0.0, -2.40000e+01,
    -5.43000e+02, -3.14000e+00,  9.28172e+00,  1.65000e+02
        );
    _assert(matrix_eq(A, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(E);

    return 0;
}

int
test_mult() {
    matrix *A = matrix_create_va(2, 3,
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0
        );

    matrix *B = matrix_create_va(3, 2,
        1.0, 2.0,
        3.0, 4.0,
        5.0, 6.0
        );

    matrix *C = matrix_mult(A, B);
    matrix *E = matrix_create_va(2, 2,
        22.0, 28.0,
        49.0, 64.0
        );

    _assert(matrix_eq(C, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(C);
    matrix_free(E);

    A = matrix_create_empty(3, 4);
    B = matrix_create_empty(3, 4);
    _assert(matrix_mult(A, B) == NULL);

    matrix_free(A);
    matrix_free(B);

    return 0;
}

int
test_mult_scalar() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    double scalar = -1;
    matrix *B = matrix_mult_scalar(A, scalar);

    matrix *E = matrix_create_va(3, 2,
        -12.0, -24.0,
        31.0, 24.0,
        -3.1415, 999.0
        );
    _assert(matrix_eq(B, E));

    matrix_free(A);
    matrix_free(B);
    matrix_free(E);

    return 0;
}

int
test_mult_scalar_inplace() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    double scalar = -1;
    matrix_mult_scalar_inplace(A, scalar);

    matrix *E = matrix_create_va(3, 2,
        -12.0, -24.0,
        31.0, 24.0,
        -3.1415, 999.0
        );
    _assert(matrix_eq(A, E));

    matrix_free(A);
    matrix_free(E);

    return 0;
}

int test_transpose() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    matrix *T = matrix_transpose(A);
    matrix *E = matrix_create_va(2, 3,
         12.0, -31.0, 3.1415,
         24.0, -24.0, -999.0
        );

    _assert(matrix_eq(T, E));

    matrix_free(A);
    matrix_free(T);
    matrix_free(E);

    return 0;
}

int
test_diagonal() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    matrix *diagonal = matrix_diagonal(A);
    matrix *E = matrix_create_va(1, 2,
        12.0, -24.0
        );
    _assert(matrix_eq(diagonal, E));

    matrix_free(A);
    matrix_free(diagonal);
    matrix_free(E);

    return 0;
}

int
test_row() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );

    matrix *row = matrix_row(A, 1);
    matrix *E = matrix_create_va(1, 2,
        -31.0, -24.0
        );

    _assert(matrix_eq(row, E));

    matrix_free(A);
    matrix_free(row);
    matrix_free(E);
    return 0;
}

int
test_col() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );

    matrix *col = matrix_col(A, 1);
    matrix *E = matrix_create_va(3, 1,
        24.0,
        -24.0,
        -999.0
        );

    _assert(matrix_eq(col, E));

    matrix_free(A);
    matrix_free(col);
    matrix_free(E);
    return 0;
}


int
test_norm_1() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    double norm = matrix_norm_1(A);
    double e = 1047.0;
    _assert(fabs(norm - e) < DBL_EPSILON);

    matrix_free(A);

    A = matrix_create_va(5, 1,
        4.0,
        -3.0,
        -1.0,
        10.0,
        -20.0
        );
    norm = matrix_norm_1(A);
    e = 38;
    _assert(fabs(norm - e) < DBL_EPSILON);

    matrix_free(A);
    return 0;
}

int
test_norm_inf() {
    matrix *A = matrix_create_va(3, 2,
        12.0, 24.0,
        -31.0, -24.0,
        3.1415, -999.0
        );
    double norm = matrix_norm_inf(A);
    double e = 1002.1415;
    _assert(fabs(norm - e) < DBL_EPSILON);

    matrix_free(A);

    A = matrix_create_va(5, 1,
        4.0,
        -3.0,
        -1.0,
        10.0,
        -20.0
        );
    norm = matrix_norm_inf(A);
    e = 20;
    _assert(fabs(norm - e) < DBL_EPSILON);

    matrix_free(A);

    return 0;
}


int
make_tests() {
    int (*tests[])() = {
        test_eq,
        test_mult_scalar,
        test_mult_scalar_inplace,
        test_mult,
        test_add,
        test_add_inplace,
        test_sub,
        test_sub_inplace,
        test_zeros_and_ones,
        test_fill,
        test_transpose,
        test_map,
        test_copy,
        test_diagonal,
        test_row,
        test_col,
        test_minor,
        test_delete,
        test_cofactor,
        test_determinant,
        test_singular,
        test_swap,
        test_norm_1,
        test_norm_inf,
        NULL
    };

    for (int i = 0; tests[i]; i++) {
        _verify(tests[i]);
    }

    return 0;
}

int
main(int argc, char *argv[]) {
    srand(time(NULL));

    int result = make_tests();
    if (result == 0)
        printf("PASSED\n");
    printf("Tests run: %d\n", tests_run);

    return result;
}
