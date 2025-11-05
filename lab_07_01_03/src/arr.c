#include "arr.h"
#include "errors.h"
#include "utils.h"

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

int copy_arrs(const int *start_arr, const int *end_arr, int **start_filter_arr, int **end_filter_arr)
{
    if (start_arr == NULL || end_arr == NULL)
        return ERROR_EMPTY_POINT_ARR;

    if (*end_filter_arr == *start_filter_arr)
        return ERROR_EMPTY_ARR;

    if (*start_filter_arr > *end_filter_arr)
        return ERROR_INVALID_POINT;

    for (int *cur_el = *start_filter_arr; cur_el < *end_filter_arr; cur_el++)
    {
        *cur_el = *start_arr;
        start_arr++;
    }

    return OK;
}

// filter_arr
int key(const int *start_arr, const int *end_arr, int **start_filter_arr, int **end_filter_arr)
{
    if (start_arr == NULL || end_arr == NULL)
        return ERROR_EMPTY_POINT_ARR;

    if (start_arr == end_arr)
        return ERROR_EMPTY_ARR;

    if (start_arr > end_arr)
        return ERROR_INVALID_POINT;

    size_t len = end_arr - start_arr;

    int rc = count_filter_elems(start_arr, end_arr, &len);

    if (rc)
        return rc;

    if (!len)
        return ERROR_EMPTY_ARR;

    *start_filter_arr = malloc(len * sizeof(int));

    if (start_filter_arr == NULL)
    {
        start_arr = NULL;
        return ERROR_MEMORY;
    }

    *end_filter_arr = *start_filter_arr + len;

    rc = copy_arrs(start_arr, end_arr, start_filter_arr, end_filter_arr);

    start_arr = NULL;

    if (rc)
        return rc;

    return OK;
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
