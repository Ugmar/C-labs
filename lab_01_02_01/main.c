#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ONE_DEGREE (acos(-1) / 180)
#define ERROR_UNCORRECT_VALUE 1

int main(void)
{
    double a, b, q; 
    if (scanf("%lf %lf %lf", &a, &b, &q) != 3)
    {
        return ERROR_UNCORRECT_VALUE;
    }
    
    double h, s;
    h = fabs(a - b) / 2.0 * tan(q * ONE_DEGREE);
    s = (a + b) / 2 * h;
    printf("Square = %f\n", s);
    return 0;
}
