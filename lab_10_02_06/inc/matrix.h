#ifndef MATRIX_H__
#define MATRIX_H__

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

typedef struct elem elem_t;

struct elem
{
    size_t i;
    size_t j;
    int value;
};

int get_value(void *data);
size_t get_i(void *data);
size_t get_j(void *data);
void free_matrix(node_t *matrix);
node_t *input_matrix(FILE *f);
void print_matrix(node_t *head, FILE *f);
void print_elem(elem_t *elem, FILE *f);
node_t *add_matrix(node_t *head1, node_t *head2);
node_t *mul_matrix(node_t *head1, node_t *head2);
node_t *lin_matrix(node_t *head);
int compare_elem(const void *a, const void *b);
node_t *transpose_matrix(node_t *head);

#endif
