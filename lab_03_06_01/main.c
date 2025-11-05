#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

int main(void)
{
    int matrix[N][M];
    size_t row, col;

    if (scanf("%zu %zu", &row, &col) != 2)
    {
        return ERROR_INVALID_SIZE;
    }

    if (row == 0 || col == 0 || row > N || col > M)
    {
        return ERROR_SIZE_NOT_RANGE;
    }

    if (row != col)
    {
        return ERROR_NOT_SQUARE;
    }

    matrix_input(matrix, row);
    matrix_print(matrix, row, col);

    return OK;
}
