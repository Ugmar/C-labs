#include <stdio.h>
#include <stddef.h>

#define ERROR_NOT_DIGIT 1
#define ERROR_COUNT 2
#define ERROR_VALUE 3
#define OK 0
#define N 10

void shift_arr(int *arr, size_t n, size_t index)
{
    for (size_t i = n; i > index + 1; i--)
    {
        arr[i] = arr[i - 1];
    }
}

void print_arr(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int input_arr(int *arr, size_t n)
{
    int el;

    for (size_t i = 0; i < n; i++)
    {
        if (scanf("%d", &el) != 1)
        {
            return ERROR_VALUE;
        }

        arr[i] = el;
    }

    return OK;
}

void changing_arr(int *arr, size_t *n)
{
    int fib0 = 0, fib1 = 1, fib2;

    for (size_t i = 0; i < *n; i++)
    {
        if (arr[i] % 3 == 0)
        {
            shift_arr(arr, *n, i);
            arr[i + 1] = fib0;

            fib2 = fib1 + fib0;
            fib0 = fib1;
            fib1 = fib2;

            i++;
            (*n)++;
        }
    }
}

int main(void)
{
    size_t n;

    if (scanf("%zu", &n) != 1)
    {
        return ERROR_NOT_DIGIT;
    }

    if (n > N || n == 0)
    {
        return ERROR_COUNT;
    }

    int arr[N * 2];
    
    if (input_arr(arr, n) == ERROR_VALUE)
    {
        return ERROR_VALUE;
    }

    changing_arr(arr, &n);
    print_arr(arr, n);

    return OK;
}
