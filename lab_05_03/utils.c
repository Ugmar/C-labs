#include <string.h>

#include "utils.h"

bool check_arg(char *arg, char *expected_arg, int len_arg)
{
    if (strncmp(arg, expected_arg, len_arg) == 0 && strlen(arg) == len_arg)
    {
        return true;
    }

    return false;
}

int get_number_by_pos(FILE *f, int position, int *number)
{
    if (fseek(f, position * sizeof(int), SEEK_SET) != 0)
    {
        return ERROR_SEEK_FILE;
    }

    if (fread(number, sizeof(int), 1, f) != 1)
    {
        return ERROR_READ_FILE;
    }

    return OK;
}

int put_number_by_pos(FILE *f, int position, int *number)
{
    if (fseek(f, position * sizeof(int), SEEK_SET) != 0)
    {
        return ERROR_SEEK_FILE;
    }

    if (fwrite(number, sizeof(int), 1, f) != 1)
    {
        return ERROR_BIN_WRITE;
    }

    return OK;
}

int swap_el(FILE *f, size_t i, size_t j)
{
    int number_i, number_j;
    int rc;

    if ((rc = get_number_by_pos(f, i, &number_i)) != OK)
    {
        return rc;
    }

    if ((rc = get_number_by_pos(f, j, &number_j)) != OK)
    {
        return rc;
    }

    if ((rc = put_number_by_pos(f, i, &number_j)) != OK)
    {
        return rc;
    }

    if ((rc = put_number_by_pos(f, j, &number_i)) != OK)
    {
        return rc;
    }

    return OK;
}

size_t get_size_file(FILE *f, size_t *n)
{
    if (fseek(f, 0, SEEK_END) != 0)
    {
        return ERROR_SEEK_FILE;
    }

    int rc = ftell(f);

    if (rc <= 0)
    {
        return ERROR_SEEK_FILE;
    }

    if (rc % sizeof(int) != 0)
    {
        return ERROR_READ_FILE;
    }

    if (fseek(f, 0, SEEK_SET) != 0)
    {
        return ERROR_SEEK_FILE;
    }

    *n = rc / sizeof(int);

    return OK;
}
