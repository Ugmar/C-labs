#include "sort.h"
#include <string.h>

#define COUNT_BYTES_CHANGE 4

size_t binary_search(void *base, void *cur, void *end, size_t size, compare_t compare)
{
    char *arr = base;

    size_t l = 0;
    size_t r = ((char *)end - arr) / size;
    size_t m = 0;

    while (l < r)
    {
        m = l + (r - l) / 2;

        if (compare(cur, arr + m * size) > 0)
            l = m + 1;
        else
            r = m;
    }

    return l;
}

void swap(char *el1, char *el2, size_t size)
{
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

void insert_el(void *base, void *end, size_t size)
{
    char *char_base = base;
    char *char_end = end;

    while (char_base != char_end)
    {
        swap(char_base, char_base - size, size);
        char_base -= size;
    }
}

// insert sort with binary search
void mysort(void *base, size_t num, size_t size, compare_t compare)
{
    if (base == NULL || compare == NULL)
        return;
    if (num <= 1 || size == 0)
        return;

    char *arr = base;
    char *end = arr + size * num;

    for (char *cur = arr + size; cur < end; cur += size)
    {
        size_t index = binary_search(arr, cur, cur, size, compare);

        if (cur > arr + index * size)
            insert_el(cur, arr + index * size, size);
    }
}
