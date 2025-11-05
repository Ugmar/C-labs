#include <stdio.h>

#define N 10
#define ERROR_COUNT_EL 1
#define ERROR_INVALID_N 2
#define ERROR_INVALID_EL 3
#define ERROR_EMPTY_ARR 4

int func(const int *l, const int *r)
{
    int a = 1;
    int res = 0;

    for (const int *lcur = l; lcur < r; lcur++)
    {
        a *= *lcur;
        res += a;

        if (*lcur < 0)
        {
            return res;
        }
    }

    return res;
}

int main(void)
{
    int n;

    if (scanf("%d", &n) != 1)
    {
        return ERROR_COUNT_EL;
    }

    if (n > N || n <= 0)
    {
        return ERROR_INVALID_N;
    }

    int arr[N];
    int el;
    int *p = arr;

    for (size_t i = 0; i < n; i++)
    {
        if (scanf("%d", &el) != 1)
        {
            return ERROR_INVALID_EL;
        }

        *p = el;
        p++;
    }
    
    int res = func(arr, arr + n);
    
    if (arr == arr + n)
    {
        return ERROR_EMPTY_ARR;
    }
    
    printf("%d", res);

    return 0;
}
