#include <stdio.h>
#include <stddef.h>

#define ERROR_NOT_DIGIT 1
#define ERROR_COUNT 2
#define ERROR_VALUE 3
#define NOT_VALUE 0
#define ERROR_NOT_VALUE 4
#define N 10

int product_odd(int *arr, size_t n)
{
    int count = 0;
    int result = 1;

    for (size_t i = 0; i < n; i++)
    {
        if (arr[i] % 2 != 0)
        {
            count += 1;
            result *= arr[i];
        }
    }

    if (count > 0)
    {
        return result;
    }

    return NOT_VALUE;
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        return ERROR_NOT_DIGIT;
    }
    
    if (n > N || n <= 0)
    {
        return ERROR_COUNT;
    }

    int arr[N];
    int el;
    
    for (size_t i = 0; i < n; i++)
    {
        if (scanf("%d", &el) != 1)
        {
            return ERROR_VALUE;
        }

        arr[i] = el;
    }

    int result = product_odd(arr, n);
    
    if (result == NOT_VALUE)
    {
        return ERROR_NOT_VALUE;
    }

    printf("%d\n", result);

    return 0;
}
