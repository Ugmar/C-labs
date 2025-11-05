#include <stdio.h>
#include <stddef.h>

#define OVERFLOW 100
#define ERROR_EMPTY_ARR 101
#define N 10

void selection_sort(int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        size_t min_index = i;
        
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }

        int tmp = arr[i];
        arr[i] = arr[min_index];
        arr[min_index] = tmp;
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

int input_arr(int *arr)
{
    int el;
    size_t count = 0;

    while (scanf("%d", &el) == 1 && count < N + 1)
    {
        if (count == N)
        {
            return OVERFLOW;
        }

        arr[count] = el;
        count++;
    }

    if (count == 0)
    {
        return ERROR_EMPTY_ARR;
    }

    return count;
}

int main(void)
{
    int arr[N];
    int n = input_arr(arr);
    
    if (n == OVERFLOW)
    {
        selection_sort(arr, N);
        print_arr(arr, N);

        return OVERFLOW;
    }
    else if (n == ERROR_EMPTY_ARR)
    {
        return ERROR_EMPTY_ARR;
    }

    selection_sort(arr, n);
    print_arr(arr, n);

    return 0;
}
