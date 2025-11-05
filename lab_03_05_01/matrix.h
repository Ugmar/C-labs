#ifndef MATRIX_H__
#define MATRIX_H__

#define N 10
#define M 10

#define ERROR_SIZE_NOT_RANGE 3
#define ERROR_INVALID_EL 2
#define ERROR_INVALID_SIZE 1
#define ERROR_NOT_VALID_EL 4
#define OK 0

int matrix_input(int (*matrix)[M], size_t row, size_t col);
void matrix_print(int (*matrix)[M], size_t row, size_t col);
void matrix_change(int (*matrix)[M], size_t row, size_t col, int *arr);

#endif
