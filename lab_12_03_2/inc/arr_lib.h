#ifndef ARR_LIB_H__
#define ARR_LIB_H__

#define ERROR_ARR_SIZE -1
#define ERROR_INVALID_ARR -2

#define OK 0

int is_prime(int n);
int fill_arr_primary(int *arr, size_t size, size_t n);
int add_number_after_even(int *src, size_t size1, int *dst, size_t size2, int digit);

#endif
