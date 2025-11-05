#include <stdio.h>
#include <math.h>

#define ERROR_UNCORRECT_VALUE 1
#define ERROR_INVALID_E 2
#define ERROR_INVALID_X 3

double absolute(double f, double s)
{
    return fabs(f - s);
}

double relative(double f, double s)
{
    return absolute(f, s) / fabs(f);
}

double calc_func_s(double x, double e)
{
    double s = 1;
    double xi = 1;
    int even = 2, odd = 1;

    while (fabs(xi) > e)
    {
        xi *= pow(x, 2) * odd / even; 
        s += xi;

        odd += 2;
        even += 2;
    }
    return s;
}

int main(void)
{
    double x, e;
    if (scanf("%lf %lf", &x, &e) != 2)
    {
        return ERROR_UNCORRECT_VALUE;
    }
    if (e > 1 || e <= 0)
    {   
        return ERROR_INVALID_E;
    }
    if (fabs(x) >= 1)
    {
        return ERROR_INVALID_X;
    }

    double f = 1 / sqrt(1 - pow(x, 2));
    double s = calc_func_s(x, e);
    
    printf("%lf %lf\n%lf %lf\n", s, f, absolute(f, s), relative(f, s));
    return 0;
}
