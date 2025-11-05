#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <stdbool.h>

#define ERROR_NOT_DIGIT 1
#define ERROR_COUNT 2
#define ERROR_VALUE 3
#define ERROR_NOT_VALUE 4
#define N 10

bool check_simple(int a)
{
    if (a < 2)
    {
        return false;
    }

    for (int i = 2; i <= sqrt(a); i++)
    {
        if (a % i == 0)
        {
            return false;
        }
    }

    return true;
}

void print_arr(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
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

    int arr_new[N];
    size_t j = 0;

    for (size_t i = 0; i < n; i++)
    {
        if (check_simple(arr[i]))
        {
            arr_new[j] = arr[i];
            j++;
        }
    }
    
    if (j == 0)
    {
        return ERROR_NOT_VALUE;
    }
    
    print_arr(arr_new, j);

    return 0;
}
