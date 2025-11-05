#include <stdio.h>

#include "matrix.h"

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

    if (row != col)
    {
        return ERROR_NOT_SQUARE;
    }

    int successful = matrix_input(matrix, row, col);

    if (successful != OK)
    {
        return ERROR_INVALID_EL;
    }

    matrix_swap(matrix, row, col);

    printf("Matrix result: \n");
    matrix_print(matrix, row, col);

    return OK;
}
