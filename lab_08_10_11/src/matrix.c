#include "matrix.h"
#include "errors.h"
#include "utils.h"

double **allocate_matrix(size_t n, size_t m)
{
    double **matrix = malloc(n * sizeof(double *) + n * m * sizeof(double));

    if (!matrix)
        return NULL;

    for (size_t i = 0; i < n; i++)
        matrix[i] = (double *)((char *)matrix + n * sizeof(double *) + i * m * sizeof(double));

    return matrix;
}

void free_matrix(const struct matrix *matrix)
{
    free(matrix->ptr_free);
}

int addition_matrix(const struct matrix *matrix1, const struct matrix *matrix2, struct matrix *matrix_res)
{
    if (!matrix_res || !matrix1 || !matrix2)
        return ERROR_EMPTY_PTR;

    if (matrix1->row != matrix2->row || matrix1->col != matrix2->col)
        return ERROR_RANGE_SUM;

    matrix_res->row = matrix1->row;
    matrix_res->col = matrix1->col;

    matrix_res->data = allocate_matrix(matrix_res->row, matrix_res->col);
    matrix_res->ptr_free = matrix_res->data;

    if (!matrix_res->data)
        return ERROR_MEMORY;

    for (size_t i = 0; i < matrix_res->row; i++)
        for (size_t j = 0; j < matrix_res->col; j++)
            matrix_res->data[i][j] = matrix1->data[i][j] + matrix2->data[i][j];

    return OK;
}

int multiply_matrix(const struct matrix *matrix1, const struct matrix *matrix2, struct matrix *matrix_res)
{
    if (!matrix_res || !matrix1 || !matrix2)
        return ERROR_EMPTY_PTR;

    if (matrix1->col != matrix2->row)
        return ERROR_RANGE_MULT;

    matrix_res->row = matrix1->row;
    matrix_res->col = matrix2->col;

    matrix_res->data = allocate_matrix(matrix_res->row, matrix_res->col);
    matrix_res->ptr_free = matrix_res->data;

    if (!matrix_res->data)
        return ERROR_MEMORY;

    for (size_t i = 0; i < matrix1->row; i++)
        for (size_t j = 0; j < matrix2->col; j++)
        {
            matrix_res->data[i][j] = 0;

            for (size_t k = 0; k < matrix1->col; k++)
                matrix_res->data[i][j] += matrix1->data[i][k] * matrix2->data[k][j];
        }

    return OK;
}

int solution_gaus(const struct matrix *matrix, const double *vector, double *solution)
{
    if (!vector || !matrix || !solution)
        return ERROR_EMPTY_PTR;

    size_t n = matrix->row;
    double **copy_matrix = allocate_matrix(n, n);
    double **ptr_free_matrix_copy = copy_matrix;

    if (!copy_matrix)
        return ERROR_MEMORY;

    double *copy_vector = malloc(n * sizeof(double));

    if (!copy_vector)
    {
        free(ptr_free_matrix_copy);
        return ERROR_MEMORY;
    }

    size_t *vector_index_col = malloc(n * sizeof(size_t));

    if (!vector_index_col)
    {
        free(ptr_free_matrix_copy);
        free(copy_vector);
        return ERROR_MEMORY;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
            copy_matrix[i][j] = matrix->data[i][j];

        copy_vector[i] = vector[i];
    }

    for (size_t i = 0; i < n; i++)
        vector_index_col[i] = i;

    size_t index_row_max = 0;

    for (size_t i = 0; i < n; i++)
    {
        index_row_max = search_max_row(copy_matrix[i], n, i);

        if (index_row_max >= n)
        {
            free(copy_vector);
            free(ptr_free_matrix_copy);
            free(vector_index_col);
            return ERROR_INAVLID_MAX_ROW;
        }

        if (fabs(copy_matrix[i][index_row_max]) < EPS)
        {
            free(copy_vector);
            free(ptr_free_matrix_copy);
            free(vector_index_col);
            return ERROR_DEGENERATE_MATRIX;
        }

        if (index_row_max != i)
            for (size_t j = 0; j < n; j++)
                swap(&copy_matrix[j][i], &copy_matrix[j][index_row_max], sizeof(copy_matrix[i][j]));

        swap(&vector_index_col[i], &vector_index_col[index_row_max], sizeof(vector_index_col[i]));

        for (size_t j = i + 1; j < n; j++)
        {
            double multiplier = copy_matrix[j][i] / copy_matrix[i][i];

            for (size_t k = i; k < n; k++)
                copy_matrix[j][k] -= multiplier * copy_matrix[i][k];

            copy_vector[j] -= multiplier * copy_vector[i];
        }
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
            copy_vector[i] -= copy_matrix[i][j] * copy_vector[j];

        copy_vector[i] /= copy_matrix[i][i];
    }

    for (size_t i = 0; i < n; i++)
        solution[vector_index_col[i]] = copy_vector[i];

    free(copy_vector);
    free(vector_index_col);
    free(ptr_free_matrix_copy);

    return OK;
}

int create_matrix(FILE *f, struct matrix *matrix)
{
    if (!matrix || !f)
        return ERROR_EMPTY_PTR;

    if (fscanf(f, "%d %d", &matrix->row, &matrix->col) != 2)
        return ERROR_INVALID_SIZE;

    if (matrix->row <= 0 || matrix->col <= 0)
        return ERROR_INVALID_RANGE;

    matrix->data = allocate_matrix(matrix->row, matrix->col);
    matrix->ptr_free = matrix->data;

    if (!matrix->data)
        return ERROR_MEMORY;

    for (size_t i = 0; i < matrix->row; i++)
        for (size_t j = 0; j < matrix->col; j++)
            if (fscanf(f, "%lf", &matrix->data[i][j]) != 1)
            {
                free_matrix(matrix);
                return ERRROR_INVALID_EL;
            }

    return OK;
}

void print_matrix(const struct matrix *matrix_res, FILE *output)
{
    fprintf(output, "%d %d\n", matrix_res->row, matrix_res->col);

    for (size_t i = 0; i < matrix_res->row; i++)
    {
        for (size_t j = 0; j < matrix_res->col; j++)
            fprintf(output, "%lf ", matrix_res->data[i][j]);
        fprintf(output, "\n");
    }
}

int create_matrix_expand(FILE *f, struct matrix *matrix, double **vector)
{
    if (!f || !matrix)
        return ERROR_EMPTY_PTR;

    if (fscanf(f, "%d %d", &matrix->row, &matrix->col) != 2)
        return ERROR_INVALID_SIZE;

    if (matrix->row <= 0 || matrix->col <= 0)
        return ERROR_INVALID_RANGE;

    matrix->col--;

    if (matrix->col != matrix->row)
        return ERROR_RANGE_GAUS;

    matrix->data = allocate_matrix(matrix->row, matrix->col);
    matrix->ptr_free = matrix->data;

    if (!matrix->data)
        return ERROR_MEMORY;

    double *tmp_vector = malloc(matrix->row * sizeof(double));

    if (!tmp_vector)
    {
        free_matrix(matrix);
        return ERROR_MEMORY;
    }

    for (size_t i = 0; i < matrix->row; i++)
    {
        for (size_t j = 0; j < matrix->col; j++)
            if (fscanf(f, "%lf", &matrix->data[i][j]) != 1)
            {
                free_matrix(matrix);
                free(tmp_vector);
                return ERRROR_INVALID_EL;
            }

        if (fscanf(f, "%lf", &tmp_vector[i]) != 1)
        {
            free_matrix(matrix);
            free(tmp_vector);
            return ERROR_INVALID_EL_VECTOR;
        }
    }

    *vector = tmp_vector;

    return OK;
}
