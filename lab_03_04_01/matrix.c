#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

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

void swap_row(int (*matrix)[M], size_t row, size_t col, size_t number_string)
{
    int tmp;

    for (size_t j = number_string; j < col - number_string; j++)
    {
        tmp = matrix[number_string][j];
        matrix[number_string][j] = matrix[row - number_string - 1][j];
        matrix[row - number_string - 1][j] = tmp;
    }
}

void matrix_swap(int (*matrix)[M], size_t row, size_t col)
{
    for (size_t i = 0; i < row / 2; i++)
    {
        swap_row(matrix, row, col, i);
    }
}
