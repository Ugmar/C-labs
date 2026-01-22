#include "matrix.h"
#include "errors.h"

int *allocate_matrix(int n, int m)
{
    int *data = malloc(sizeof(int) * n * m);
    
    if (!data)
        return NULL;
            
    return data;
}

struct matrix create_matrix(int *data, int n, int m)
{
    struct matrix matrix = {.data = data, .n = n, .m = m};
    return matrix;
}

int fill_matrix(struct matrix matrix, FILE *f)
{
    if (!f)
        return ERROR_EMPTY_POINT;

    for (size_t i = 0; i < matrix.n; i++)
        for (size_t j = 0; j < matrix.m; j++)
            if (fscanf(f, "%d", &matrix.data[i * matrix.m + j]) != 1)
                return ERROR_INVALID_EL;

    return OK;
}

void free_matrix(struct matrix matrix)
{
    free(matrix.data);
}

void rotate_matrix(struct matrix *matrix)
{
    int *tmp = malloc(sizeof(int) * matrix->m * matrix->n);

    if (!tmp)
    {
        free_matrix(*matrix);
        matrix->data = NULL;
        return;
    }

    for (int i = 0; i < matrix->m; i++)
        for (int j = 0; j < matrix->n; j++)
            tmp[i * matrix->n + j] = matrix->data[(matrix->n - 1 - j) * matrix->m + i];

    free(matrix->data);
    matrix->data = tmp;

    int s = matrix->n;
    matrix->n = matrix->m;
    matrix->m = s;
}

void print_matrix(struct matrix matrix)
{
    for (size_t i = 0; i < matrix.n; i++)
    {
        for (size_t j = 0; j < matrix.m; j++)
            printf("%d ", matrix.data[i * matrix.m + j]);
        printf("\n");
    }
}
