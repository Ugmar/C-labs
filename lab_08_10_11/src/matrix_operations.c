#include "matrix.h"
#include "errors.h"
#include "matrix_operations.h"

int arithmetic_operations(char *file1, char *file2, char *file_output, operation_t opearion)
{
    if (!file1 || !file2 || !file_output || !opearion)
        return ERROR_EMPTY_PTR;

    int rc;

    FILE *f1 = fopen(file1, "r");
    if (!f1)
        return ERROR_IO_FILE;

    struct matrix matrix1 = MATRIX_INIT_SIZE(0, 0);

    rc = create_matrix(f1, &matrix1);
    fclose(f1);

    if (rc)
        return rc;

    FILE *f2 = fopen(file2, "r");

    if (!f2)
    {
        free_matrix(&matrix1);
        return ERROR_IO_FILE;
    }

    struct matrix matrix2 = MATRIX_INIT_SIZE(0, 0);

    rc = create_matrix(f2, &matrix2);
    fclose(f2);

    if (rc)
    {
        free_matrix(&matrix1);
        return rc;
    }

    struct matrix matrix_res = MATRIX_INIT_SIZE(0, 0);

    rc = opearion(&matrix1, &matrix2, &matrix_res);

    if (rc)
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);

        return rc;
    }

    FILE *output = fopen(file_output, "w");

    if (!output)
    {
        free_matrix(&matrix1);
        free_matrix(&matrix2);
        free_matrix(&matrix_res);

        return ERROR_IO_FILE;
    }

    print_matrix(&matrix_res, output);

    fclose(output);

    free_matrix(&matrix1);
    free_matrix(&matrix2);
    free_matrix(&matrix_res);

    return rc;
}

int solution_gauss_row(char *file_in, char *file_out)
{
    if (!file_in || !file_out)
        return ERROR_EMPTY_PTR;

    int rc;

    FILE *f1 = fopen(file_in, "r");
    if (!f1)
        return ERROR_IO_FILE;

    struct matrix matrix = MATRIX_INIT_SIZE(0, 0);
    double *vector = NULL;

    rc = create_matrix_expand(f1, &matrix, &vector);
    fclose(f1);

    if (rc)
        return rc;

    double *vector_solution = malloc(matrix.row * sizeof(double));

    if (!vector_solution)
    {
        free_matrix(&matrix);
        free(vector);

        return ERROR_MEMORY;
    }

    rc = solution_gaus(&matrix, vector, vector_solution);

    if (rc)
    {
        free_matrix(&matrix);
        free(vector);
        free(vector_solution);

        return rc;
    }

    struct matrix matrix_solution = MATRIX_INIT_SIZE(matrix.row, 1);

    matrix_solution.data = allocate_matrix(matrix.row, 1);
    matrix_solution.ptr_free = matrix_solution.data;

    if (matrix_solution.data == NULL)
    {
        free_matrix(&matrix);
        free(vector);
        free(vector_solution);
        return ERROR_MEMORY;
    }

    for (size_t i = 0; i < matrix.row; i++)
        matrix_solution.data[i][0] = vector_solution[i];

    FILE *output = fopen(file_out, "w");

    if (!output)
    {
        free_matrix(&matrix);
        free_matrix(&matrix_solution);
        free(vector);
        free(vector_solution);

        return ERROR_IO_FILE;
    }

    print_matrix(&matrix_solution, output);

    fclose(output);

    free_matrix(&matrix);
    free_matrix(&matrix_solution);
    free(vector);
    free(vector_solution);

    return OK;
}
