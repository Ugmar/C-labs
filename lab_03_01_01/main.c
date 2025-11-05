#include <stdio.h>

#include "arr.h"
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

    int successful = matrix_input(matrix, row, col);

    if (successful != OK)
    {
        return ERROR_INVALID_EL;
    }

    int res[N];

    for (int i = 0; i < row; i++)
    {
        res[i] = arr_check_symmetry(matrix[i], col);
    }

    arr_output(res, row);

    return OK;
}
