#include "matrix.h"
#include "errors.h"

#define N 3
#define M 5
#define NAME_FILE "test.txt"

int main(void)
{
    char *filename = NAME_FILE;
    int n = N, m = M;

    FILE *f = fopen(filename, "r");

    if (!f)
        return ERROR_IO_FILE;

    int *data = allocate_matrix(n, m);

    if (!data)
    {
        return ERROR_MEMORY;
    }

    struct matrix matrix = create_matrix(data, n, m);
    int rc = fill_matrix(matrix, f);

    fclose(f);

    if (rc)
    {
        free_matrix(matrix);
        return rc;
    }

    rotate_matrix(&matrix);
    
    if (!matrix.data)
    {
        return ERROR_MEMORY;
    }

    print_matrix(matrix);

    free_matrix(matrix);
    
    return OK;
}
