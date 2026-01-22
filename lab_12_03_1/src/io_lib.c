#include <stdlib.h>

#include "io.h"
#include "errors.h"

int count_all_elems(FILE *input_file, size_t *const len)
{
    if (input_file == NULL)
        return ERROR_IO_FILE;

    if (len == NULL)
        return ERROR_EMPTY_POINT_LEN;

    long pos_start_file = ftell(input_file);

    int el;
    *len = 0;

    while (fscanf(input_file, "%d", &el) == 1)
        (*len)++;

    if (!feof(input_file))
        return ERROR_INVALID_DIGIT;

    fseek(input_file, pos_start_file, SEEK_SET);

    return OK;
}

int fill_arr(FILE *input_file, int **start_arr, int **end_arr)
{
    if (input_file == NULL)
        return ERROR_IO_FILE;

    if (start_arr == NULL || end_arr == NULL)
        return ERROR_EMPTY_POINT_ARR;

    if (*start_arr == *end_arr)
        return ERROR_EMPTY_ARR;

    if (*start_arr > *end_arr)
        return ERROR_INVALID_POINT;

    long pos_start_file = ftell(input_file);

    for (int *cur_elem = *start_arr; cur_elem < *end_arr; cur_elem++)
    {
        if (fscanf(input_file, "%d", cur_elem) != 1)
            return ERROR_READ_FILE;
    }

    fseek(input_file, pos_start_file, SEEK_SET);

    return OK;
}

int create_arr(FILE *input_file, int **start_arr, int **end_arr)
{
    if (input_file == NULL)
        return ERROR_IO_FILE;

    size_t len = 0;

    int rc = count_all_elems(input_file, &len);

    if (rc)
        return rc;

    if (!len)
        return ERRPR_EMPTY_FILE;

    *start_arr = malloc(len * sizeof(int));

    if (start_arr == NULL)
        return ERROR_MEMORY;

    *end_arr = *start_arr + len;

    rc = fill_arr(input_file, start_arr, end_arr);

    return rc;
}

int fprint_arr(FILE *output_file, const int *start_arr, const int *end_arr)
{
    if (output_file == NULL)
        return ERROR_IO_FILE;

    if (start_arr == NULL || end_arr == NULL)
        return ERROR_EMPTY_POINT_ARR;

    if (start_arr == end_arr)
        return ERROR_EMPTY_ARR;

    if (start_arr > end_arr)
        return ERROR_INVALID_POINT;

    for (const int *cur = start_arr; cur < end_arr; cur++)
    {
        fprintf(output_file, "%d ", *cur);
    }

    return OK;
}
