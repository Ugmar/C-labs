#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
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

void matrix_delete_row(int (*matrix)[M], size_t row, size_t col, size_t i_min)
{
    for (size_t i = i_min; i < row - 1; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            matrix[i][j] = matrix[i + 1][j];
        }
    }
}

void matrix_delete_col(int (*matrix)[M], size_t row, size_t col, size_t j_min)
{
    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = j_min; j < col - 1; j++)
        {
            matrix[i][j] = matrix[i][j + 1];
        }
    }
}

void matrix_search_min_el(int (*matrix)[M], size_t row, size_t col, size_t *i_min, size_t *j_min)
{
    int min_el = sum_digit(matrix[0][0]);

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            int current = sum_digit(matrix[i][j]);

            if (current < min_el)
            {
                *i_min = i;
                *j_min = j;
                min_el = current;
            }
        }
    }
}
