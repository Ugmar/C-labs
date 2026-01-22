#include "utils.h"

void swap(void *a, void *b, size_t size)
{
    char *el1 = a;
    char *el2 = b;

    char tmp[COUNT_BYTES_CHANGE];
    size_t remains = size % COUNT_BYTES_CHANGE;

    for (size_t i = 0; i + COUNT_BYTES_CHANGE <= size; i += COUNT_BYTES_CHANGE)
    {
        memcpy(tmp, el1 + i, COUNT_BYTES_CHANGE);
        memcpy(el1 + i, el2 + i, COUNT_BYTES_CHANGE);
        memcpy(el2 + i, tmp, COUNT_BYTES_CHANGE);
    }

    if (remains > 0)
    {
        memcpy(tmp, el1 + (size - remains), remains);
        memcpy(el1 + (size - remains), el2 + (size - remains), remains);
        memcpy(el2 + (size - remains), tmp, remains);
    }
}

size_t search_max_row(double *row, size_t len, size_t index)
{
    size_t index_max = index;

    for (size_t i = index + 1; i < len; i++)
        if (fabs(row[i]) > fabs(row[index_max]))
            index_max = i;

    return index_max;
}
