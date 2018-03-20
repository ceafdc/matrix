#ifndef matrix_h
#define matrix_h

typedef struct
{
    double **data;
    const unsigned int m; // #rows
    const unsigned int n; // #cols
} matrix;


// Initialization
matrix *matrix_create_empty(unsigned int m, unsigned int n);
matrix *matrix_create_va(unsigned int m, unsigned int n, ...);
matrix *matrix_create_zeros(unsigned int m, unsigned int n);
matrix *matrix_create_ones(unsigned int m, unsigned int n);
matrix *matrix_copy(const matrix *A);


// Arithmetic
matrix *matrix_mult_scalar(const matrix *A, double scalar);
matrix *matrix_add(const matrix *A, const matrix *B);
matrix *matrix_mult(const matrix *A, const matrix *B);


// Inplace arithmetic
void matrix_mult_scalar_inplace(matrix *A, double scalar);
void matrix_add_inplace(matrix *A, const matrix *B); // ads to A


// Helpers
int matrix_same_order(const matrix *A, const matrix *B);
int matrix_can_mult(const matrix *A, const matrix *B);
int matrix_is_square(const matrix *A);
int matrix_eq(const matrix *A, const matrix *B);
int matrix_is_singular(const matrix *A);


// Matrix stuff
matrix *matrix_transpose(const matrix *A);
matrix *matrix_diagonal(const matrix *A);
matrix *matrix_row(const matrix *A, unsigned int r);
matrix *matrix_col(const matrix *A, unsigned int c);
double matrix_minor(const matrix *A, unsigned int i, unsigned int j);
double matrix_cofactor(const matrix *A, unsigned int i, unsigned int j);
double matrix_determinant(const matrix *A);

matrix *matrix_delete_col(const matrix *A, unsigned int col);
matrix *matrix_delete_row(const matrix *A, unsigned int row);
void matrix_swap_col_inplace(matrix *A, unsigned int c1, unsigned int c2);
void matrix_swap_row_inplace(matrix *A, unsigned int r1, unsigned int r2);


// Functional
void matrix_map(matrix *A, double (*f)(double));
void matrix_fill(matrix *A, double v);


void matrix_print(const matrix *M);
void matrix_free(matrix *M);

#endif
