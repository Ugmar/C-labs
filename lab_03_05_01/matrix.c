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

void matrix_change(int (*matrix)[M], size_t row, size_t col, int *arr)
{
    int count = 0;

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if (sum_digit(matrix[i][j]) > SUM_DIGIT)
            {
                matrix[i][j] = arr[count];
                count++;
            }
        }
    }
}
