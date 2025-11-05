#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "utils.h"

int matrix_input(int (*matrix)[M], size_t row, size_t col)
{
    int el;

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if (scanf("%d", &el) != 1)
            {
                return ERROR_INVALID_EL;
            }

            matrix[i][j] = el;
        }
    }

    return OK;
}

void matrix_print(int (*matrix)[M], size_t row, size_t col)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void matrix_sort(int (*matrix)[M], size_t row, size_t col)
{
    int tmp;

    for (size_t n = 0; n < row; n++)
    {
        for (size_t i = 0; i < row - n - 1; i++)
        {
            if (max_el(matrix[i], col) < max_el(matrix[i + 1], col))
            {
                for (int j = 0; j < col; j++)
                {
                    tmp = matrix[i][j];
                    matrix[i][j] = matrix[i + 1][j];
                    matrix[i + 1][j] = tmp;
                }
            }
        }
    }
}
