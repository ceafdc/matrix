#ifndef matrix_h
#define matrix_h

typedef struct
{
    double **data;
    const int m; // #rows
    const int n; // #cols
} matrix;

matrix *matrix_create_empty(int m, int n);
matrix *matrix_create_va(int m, int n, ...);
matrix *matrix_create_zeros(int m, int n);
matrix *matrix_create_ones(int m, int n);
matrix *matrix_mult(matrix *A, matrix *B);
matrix *matrix_copy(matrix *A);

void matrix_map(matrix *A, double (*f)(double));
void matrix_fill(matrix *A, double v);

int matrix_eq(matrix *A, matrix *B);

void matrix_print(matrix *M);
void matrix_free(matrix *M);

#endif
