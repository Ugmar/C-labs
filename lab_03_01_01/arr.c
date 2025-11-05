#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool arr_check_symmetry(int *row, size_t len_row)
{
    for (int i = 0; i < len_row / 2; i++)
    {
        if (row[i] != row[len_row - i - 1])
        {
            return false;
        }
    }

    return true;
}

void arr_output(int *res, size_t row)
{
    for (size_t i = 0; i < row; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");
}
