#include <stdlib.h>

int sum_digit(int el)
{
    el = abs(el);
    int s = 0;

    while (el > 0)
    {
        s += el % 10;
        el /= 10;
    }

    return s;
}
