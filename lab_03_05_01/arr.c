#include <stdlib.h>

#include "utils.h"
#include "arr.h"

void arr_shift(int *arr, size_t len, int k)
{
    if (k > 0)
    {
        int tmp = arr[0];

        for (size_t i = 0; i < len - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        arr[len - 1] = tmp;
        arr_shift(arr, len, k - 1);
    }
}

int arr_fill(int *arr, int (*matrix)[K], int row, int col)
{
    int index = 0;

    for (size_t i = 0; i < row; i++)
    {
        for (size_t j = 0; j < col; j++)
        {
            if (sum_digit(matrix[i][j]) > SUM_DIGIT)
            {
                arr[index] = matrix[i][j];
                index++;
            }
        }
    }

    return index;
}
