#include <stdio.h>

#include "arr.h"
#include "matrix.h"

#define COEF_SHIFT 3

int main(void)
{
    int matrix[N][M];
    int row, col;

    if (scanf("%d %d", &row, &col) != 2)
    {
        return ERROR_INVALID_SIZE;
    }

    if (row <= 0 || col <= 0 || row > N || col > M)
    {
        return ERROR_SIZE_NOT_RANGE;
    }

    int successful = matrix_input(matrix, row, col);

    if (successful != OK)
    {
        return ERROR_INVALID_EL;
    }

    int arr[N * M];

    int index = arr_fill(arr, matrix, row, col);

    if (index == 0)
    {
        return ERROR_NOT_VALID_EL;
    }

    arr_shift(arr, index, COEF_SHIFT);
    matrix_change(matrix, row, col, arr);

    printf("Result: \n");
    matrix_print(matrix, row, col);

    return OK;
}
