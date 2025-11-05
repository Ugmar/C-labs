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

    if (row <= 1 || col <= 1 || row > N || col > M)
    {
        return ERROR_SIZE_NOT_RANGE;
    }

    int successful = matrix_input(matrix, row, col);

    if (successful != OK)
    {
        return ERROR_INVALID_EL;
    }

    size_t i_min = 0, j_min = 0;

    matrix_search_min_el(matrix, row, col, &i_min, &j_min);
    matrix_delete_row(matrix, row, col, i_min);
    matrix_delete_col(matrix, row, col, j_min);
    matrix_print(matrix, row - 1, col - 1);

    return OK;
}
