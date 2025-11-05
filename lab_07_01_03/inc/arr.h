#ifndef ARR_H__
#define ARR_H__

#include <stdio.h>

int create_arr(FILE *input_file, int **start_arr, int **end_arr);
int key(const int *start_arr, const int *end_arr, int **start_filter_arr, int **end_filter_arr);
int fprint_arr(FILE *output_file, const int *start_arr, const int *end_arr);
int fill_arr(FILE *input_file, int **start_arr, int **end_arr);

#endif
