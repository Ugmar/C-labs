#include <stdlib.h>

int max_el(int *arr, size_t len)
{
    int mx = arr[0];

    for (size_t i = 1; i < len; i++)
    {
        if (arr[i] > mx)
        {
            mx = arr[i];
        }
    }

    return mx;
}
