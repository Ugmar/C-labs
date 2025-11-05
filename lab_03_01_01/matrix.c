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
    return 0;
}
