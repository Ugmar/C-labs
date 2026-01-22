#ifndef FILTER_H__
#define FILTER_H__

int count_filter_elems(const int *start_arr, const int *end_arr, size_t *const len);
int key(const int *start_arr, const int *end_arr, int **start_filter_arr, int **end_filter_arr);

#endif
