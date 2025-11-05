#include <math.h>

#include "utils.h"

double calc_avg(FILE *f, int *n)
{
    *n = 0;
    double sum = 0;
    double el;
    
    while (fscanf(f, "%lf", &el) == 1)
    {
        sum += el;
        (*n)++;
    }

    if (*n == 0)
    {
        return ERROR_NO_DATA;
    }

    return sum / *n;
}

double calc_variance(FILE *f, double avg)
{
    double variance = 0;
    int n = 0;
    double el;

    while (fscanf(f, "%lf", &el) == 1)
    {
        variance += (avg - el) * (avg - el);
        n++;
    }

    variance /= n;

    return variance;
}
