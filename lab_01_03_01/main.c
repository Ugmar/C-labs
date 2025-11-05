#include <stdio.h>

#define ERROR_UNCORRECT_VALUE 1

int main(void)
{
    double v1, v2, t1, t2;
    if (scanf("%lf %lf %lf %lf", &v1, &t1, &v2, &t2) != 4)
    {
        return ERROR_UNCORRECT_VALUE;
    }
    
    double v = v1 + v2;
    double t = (v1 * t1 + v2 * t2) / v;
    printf("V = %lf\nT = %lf\n", v, t);
    return 0;
}
