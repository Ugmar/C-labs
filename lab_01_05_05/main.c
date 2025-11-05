#include <stdio.h>
#include <math.h>

#define ERROR_UNCORRECT_VALUE 1
#define ERROR_NOT_NATURAL 2

int count_category(int n)
{
    int category = 0;

    while (n > 0)
    {
        n /= 10;
        category += 1;
    }
    return category;
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1) 
    {
        return ERROR_UNCORRECT_VALUE;
    }
    if (n <= 0)
    {
        return ERROR_NOT_NATURAL;
    }

    int category = count_category(n);
    int divider = pow(10, category - 1);
    
    for (int i = 0; i < category; i++)
    {
        printf("%d", n / divider);
        n %= divider;
        divider /= 10;
    }
    return 0;
}
