#ifndef MATRIX_H__

#include <stdlib.h>
#include <stdio.h>

struct matrix
{
    int *data;
    size_t n;
    size_t m;
};

int *allocate_matrix(int n, int m);
struct matrix create_matrix(int *data, int n, int m);
int fill_matrix(struct matrix matrix, FILE *f);
void free_matrix(struct matrix matrix);
void print_matrix(struct matrix matrix);
void rotate_matrix(struct matrix *matrix);

#endif
