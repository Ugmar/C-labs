#include "errors.h"
#include "matrix.h"
#include "utils.h"
#include "matrix_operations.h"

#define LEN_ACTION 1
#define COUNT_ARGS 4

int main(int argc, char **argv)
{
    int rc;

    if (argc < COUNT_ARGS)
        return ERROR_ARGC;

    if (strncmp(argv[1], "a", LEN_ACTION) == 0 && strlen(argv[1]) == LEN_ACTION)
    {
        if (argc != COUNT_ARGS + 1)
            return ERROR_ARGC;

        rc = arithmetic_operations(argv[2], argv[3], argv[4], addition_matrix);

        return rc;
    }

    if (strncmp(argv[1], "m", LEN_ACTION) == 0 && strlen(argv[1]) == LEN_ACTION)
    {
        if (argc != COUNT_ARGS + 1)
            return ERROR_ARGC;

        rc = arithmetic_operations(argv[2], argv[3], argv[4], multiply_matrix);

        return rc;
    }

    if (strncmp(argv[1], "o", LEN_ACTION) == 0 && strlen(argv[1]) == LEN_ACTION)
    {
        if (argc != 4)
            return ERROR_ARGC;

        rc = solution_gauss_row(argv[2], argv[3]);

        return rc;
    }

    return ERROR_INVALID_ACTION;
}
