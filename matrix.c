#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <float.h>
#include <math.h>
#include <string.h>
#include "matrix.h"

double **
init_data(int m, int n) {
    double **data = (double **)malloc(sizeof(double *) * m);
    for (int i = 0; i < m; i++) {
        data[i] = (double *)malloc(sizeof(double) * n);
    }

    return data;
}

matrix *
matrix_create_va(int m, int n, ...) {
    va_list ap;
    matrix *M = NULL;
    if ((M = matrix_create_empty(m, n))) {
        va_start(ap, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                M->data[i][j] = va_arg(ap, double);
            }
        }

        va_end(ap);
    }
    return M;
}

matrix *
matrix_create_zeros(int m, int n) {
    matrix *M = NULL;
    if ((M = matrix_create_empty(m, n))) {
        matrix_fill(M, 0);
    }

    return M;
}

matrix *
matrix_create_ones(int m, int n) {
    matrix *M = NULL;
    if ((M = matrix_create_empty(m, n))) {
        matrix_fill(M, 1);
    }

    return M;
}

matrix *
matrix_copy(matrix *A) {
    matrix *B = matrix_create_empty(A->m, A->n);
    for (int i = 0; i < B->m; i++) {
        for (int j = 0; j < B->n; j++) {
            B->data[i][j] = A->data[i][j];
        }
    }

    return B;
}

void
matrix_fill(matrix *A, double v) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            A->data[i][j] = v;
        }
    }
}

void
matrix_map(matrix *A, double (*f)(double)) {
    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            A->data[i][j] = f(A->data[i][j]);
        }
    }
}

matrix *
matrix_create_empty(int m, int n) {
    if (m <= 0 || n <= 0) {
        return NULL;
    }
    matrix *M = (matrix *)malloc(sizeof(matrix));
    matrix s = (matrix){NULL, m, n};
    memcpy(M, &s, sizeof(matrix));

    M->data = init_data(m, n);

    return M;
}

int
matrix_same_order(matrix *A, matrix *B) {
    return A->m == B->m && A->n == B->n;
}

int
matrix_can_mult(matrix *A, matrix *B) {
    return A->n == B->m;
}

int
matrix_is_square(matrix *A) {
    return A->m == A->n;
}

matrix *
matrix_add(matrix *A, matrix *B) {
    if (!matrix_same_order(A, B)) {
        return NULL;
    }

    matrix *C = matrix_create_empty(A->m, A->n);
    for (int i = 0; i < C->m; i++) {
        for (int j = 0; j < C->n; j++) {
            C->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }

    return C;
}

matrix *
matrix_mult(matrix *A, matrix *B) {
    if (!matrix_can_mult(A, B)) {
        return NULL;
    }

    matrix *C = matrix_create_zeros(A->m, B->n);
    for (int i = 0; i < C->m; i++) {
        for (int j = 0; j < C->n; j++) {
            for (int k = 0; k < A->n; k++) {
                C->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
    return C;
}

int
matrix_eq(matrix *A, matrix *B) {
    if (A == B) {
        return 1;
    }
    if (A->m != B->m || A->n != B->n) {
        return 0;
    }

    for (int i = 0; i < A->m; i++) {
        for (int j = 0; j < A->n; j++) {
            if (fabs(A->data[i][j] - B->data[i][j]) > DBL_EPSILON) {
                return 0;
            }
        }
    }

    return 1;
}

void
matrix_print(matrix *M) {
    for (int i = 0; i < M->m; i++) {
        for (int j = 0; j < M->n; j++) {
            printf("%lf ", M->data[i][j]);
        }
        printf("\n");
    }
}

void
matrix_free(matrix *M) {
    for (int i = 0; i < M->m; i++) {
        free(M->data[i]);
    }
    free(M->data);
    free(M);
}
