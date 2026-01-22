#include <stdlib.h>

#include "filter.h"
#include "errors.h"

int count_filter_elems(const int *start_arr, const int *end_arr, size_t *const len)
{
    if (start_arr == NULL || end_arr == NULL)
        return ERROR_EMPTY_POINT_ARR;

    if (len == NULL)
        return ERROR_EMPTY_POINT_LEN;

    if (end_arr == start_arr)
        return ERROR_EMPTY_ARR;

    if (start_arr > end_arr)
        return ERROR_INVALID_POINT;

    const int *index_last_negative = NULL;

    for (const int *cur_el = start_arr; cur_el < end_arr; cur_el++)
    {
        if (*cur_el < 0)
        {
            index_last_negative = cur_el;
        }
    }

    if (index_last_negative != NULL)
        *len = index_last_negative - start_arr;

    return OK;
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

    // size_t len = end_arr - start_arr;

    // int rc = count_filter_elems(start_arr, end_arr, &len);

    // if (rc)
    //     return rc;

    // *start_filter_arr = malloc(len * sizeof(int));

    if (start_filter_arr == NULL)
    {
        start_arr = NULL;
        return ERROR_MEMORY;
    }

    // *end_filter_arr = *start_filter_arr + len;

    int rc = copy_arrs(start_arr, end_arr, start_filter_arr, end_filter_arr);

    start_arr = NULL;

    if (rc)
        return rc;

    return OK;
}
