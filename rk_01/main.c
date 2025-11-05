#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERROR_INVALID_EL 101
#define ERROR_NEGATIVE_EL 102
#define ERROR_EMPTY_ARR 103
#define N 100


int input_arr(double *arr)
{
    double el;

    for (size_t i = 0; i < N; i++)
    {
        if (scanf("%lf", &el) != 1)
        {
            return ERROR_INVALID_EL;
        }

        if (el == -1)
        {
            return i;
        }

        if (el < 0)
        {
            return ERROR_NEGATIVE_EL;
        }

        arr[i] = el;
    }

    return N;
}

int count_odd(double *arr, size_t n)
{
    int count = 0;

    for (size_t i = 0; i < n; i++)
    {
        if ((int)arr[i] % 2 != 0)
        {
            count++;
        }
    }

    return count;
}

double search_avg(const double *l, const double *r)
{
    double summ = 0;
    int count = 0;

    for (const double *lcur = l; lcur < r; lcur++)
    {
        if ((int)*lcur % 3 == 0)
        {
            summ += *lcur;
            count++;
        }
    }

    if (count == 0)
    {
        return 0;
    }

    return summ / count;
}


int main(void)
{
    double arr[N];
    size_t n = input_arr(arr);

    if (n == ERROR_INVALID_EL)
    {
        return ERROR_INVALID_EL;
    }

    else if (n == ERROR_NEGATIVE_EL)
    {
        return ERROR_NEGATIVE_EL;
    }
    else if (n == 0)
    {
        return ERROR_EMPTY_ARR;
    }

    int count = count_odd(arr, n);
    printf("Количество нечетных элементов в массиве: %d\n", count);

    double avg = search_avg(arr, arr + n);
    printf("Среднее арифметическое чисел кратных 3: %lf\n", avg);

    return OK;
}
