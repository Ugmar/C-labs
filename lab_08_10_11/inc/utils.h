#ifndef UTILS_H__
#define UTILS_H__

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define EPS DBL_EPSILON
#define COUNT_BYTES_CHANGE 4

void swap(void *a, void *b, size_t size);
size_t search_max_row(double *row, size_t len, size_t index);

#endif
