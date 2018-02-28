#ifndef matrix_h
#define matrix_h

typedef struct
{
    double **data;
    const int m; // #rows
    const int n; // #cols
} matrix;


// Initialization
matrix *matrix_create_empty(int m, int n);
matrix *matrix_create_va(int m, int n, ...);
matrix *matrix_create_zeros(int m, int n);
matrix *matrix_create_ones(int m, int n);
matrix *matrix_copy(const matrix *A);

// Arithmetic
matrix *matrix_mult_scalar(const matrix *A, double scalar);
matrix *matrix_add(const matrix *A, const matrix *B);
matrix *matrix_mult(const matrix *A, const matrix *B);


// Inplace arithmetic
void matrix_mult_scalar_inplace(matrix *A, double scalar);


// Helpers
int matrix_same_order(const matrix *A, const matrix *B);
int matrix_can_mult(const matrix *A, const matrix *B);
int matrix_is_square(const matrix *A);
int matrix_eq(const matrix *A, const matrix *B);

// Matrix stuff
matrix *matrix_transpose(const matrix *A);

// Functional
void matrix_map(matrix *A, double (*f)(double));
void matrix_fill(matrix *A, double v);


void matrix_print(const matrix *M);
void matrix_free(matrix *M);

#endif
