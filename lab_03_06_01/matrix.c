#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

void matrix_input_top(int (*matrix)[M], size_t left, size_t right, size_t top, int *el)
{
    for (size_t i = left; i < right + 1; i++)
    {
        matrix[top][i] = *el;
        *el = *el + 1;
    }
}

void matrix_input_right(int (*matrix)[M], size_t top, size_t bottom, size_t right, int *el)
{
    for (size_t i = top; i < bottom + 1; i++)
    {
        matrix[i][right] = *el;
        *el = *el + 1;
    }
}

void matrix_input_bottom(int (*matrix)[M], size_t right, size_t left, size_t bottom, int *el)
{
    for (size_t i = right; i + 1 > left; i--)
    {
        matrix[bottom][i] = *el;
        *el = *el + 1;
    }
}

void matrix_input_left(int (*matrix)[M], size_t bottom, size_t top, size_t left, int *el)
{
    for (size_t i = bottom; i + 1 > top; i--)
    {
        matrix[i][left] = *el;
        *el = *el + 1;
    }
}

void matrix_input(int (*matrix)[M], size_t n)
{
    size_t top = 0, bottom = n - 1, left = 0, right = n - 1;
    size_t current = top;
    int el = 1;

    while (top <= bottom && left <= right)
    {
        switch (current)
        {
            case 0:
                matrix_input_top(matrix, left, right, top, &el);
                top++;
                break;
            case 1:
                matrix_input_right(matrix, top, bottom, right, &el);
                right--;
                break;
            case 2:
                matrix_input_bottom(matrix, right, left, bottom, &el);
                bottom--;
                break;
            case 3:
                matrix_input_left(matrix, bottom, top, left, &el);
                left++;
                break;
        }

        current = (current + 1) % 4;
    }
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
