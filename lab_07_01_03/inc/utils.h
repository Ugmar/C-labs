#ifndef UTILS_H__
#define UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_t)(const void *, const void *);

int count_all_elems(FILE *input_file, size_t *const len);
int count_filter_elems(const int *start_arr, const int *end_arr, size_t *const len);
void mysort(void *base, size_t num, size_t size, compare_t compare);

#endif
