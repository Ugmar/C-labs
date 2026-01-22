#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

#define MATRIX_INIT_SIZE(rows, cols) { .ptr_free = NULL, .data = NULL, .row = (rows), .col = (cols) }

struct matrix
{
    double **data;
    int row;
    int col;
    double **ptr_free;
};

typedef int (*operation_t)(const struct matrix *, const struct matrix *, struct matrix *);

double **allocate_matrix(size_t n, size_t m);
int addition_matrix(const struct matrix *matrix1, const struct matrix *matrix2, struct matrix *matrix_res);
int multiply_matrix(const struct matrix *matrix1, const struct matrix *matrix2, struct matrix *matrix_res);
int solution_gaus(const struct matrix *matrix, const double *vector, double *solution);
void free_matrix(const struct matrix *matrix);
int create_matrix(FILE *f, struct matrix *matrix);
void print_matrix(const struct matrix *matrix_res, FILE *output);
int create_matrix_expand(FILE *f, struct matrix *matrix, double **vector);

#endif
