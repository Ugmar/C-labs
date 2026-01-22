#include <stdlib.h>

#include "arr_lib.h"

int is_prime(int n)
{
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return 0;

    return 1;
}

int fill_arr_primary(int *arr, size_t size, size_t n)
{
    if (!arr)
        return ERROR_INVALID_ARR;

    if (size < n)
        return ERROR_ARR_SIZE;

    int count = 0;
    int num = 2;

    while (count < n)
    {
        if (is_prime(num))
        {
            arr[count] = num;
            count++;
        }

        num++;
    }

    return OK;
}

int add_number_after_even(int *src, size_t size1, int *dst, size_t size2, int digit)
{
    if (!src)
        return ERROR_INVALID_ARR;

    size_t count = 0;

    for (size_t i = 0; i < size1; i++)
    {
        count++;

        if (abs(src[i]) % 2 == 0)
            count++;
    }

    if (!dst)
        return count;

    if (size2 < count)
        return ERROR_ARR_SIZE;

    count = 0;

    for (size_t i = 0; i < size1; i++)
    {
        dst[count] = src[i];
        count++;

        if (abs(src[i]) % 2 == 0)
        {
            dst[count] = digit;
            count++;
        }
    }

    return count;
}
