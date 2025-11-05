#include <stdio.h>

#include "matrix.h"
#include "utils.h"

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

    matrix_sort(matrix, row, col);
    matrix_print(matrix, row, col);

    return OK;
}
