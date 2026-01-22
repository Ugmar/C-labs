#ifndef IO_H__
#define IO_H__

#include <stdio.h>

int count_all_elems(FILE *input_file, size_t *const len);
int create_arr(FILE *input_file, int **start_arr, int **end_arr);
int fprint_arr(FILE *output_file, const int *start_arr, const int *end_arr);
int fill_arr(FILE *input_file, int **start_arr, int **end_arr);

#endif
