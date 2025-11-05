#include <stdio.h>
#include <math.h>

#define UNCORRECT_VALUE 1
#define NOT_SECTION 3

int g(void)
{
    int i = 1;
    double s = 0, x;

    while (1)
    {
        if (scanf("%lf", &x) != 1) 
        {
            return UNCORRECT_VALUE;
        }

        if (x < 0)
        {
            if (i == 1) 
            {
                return NOT_SECTION;
            }
            printf("%lf", sin(s));
            return 0;
        }

        s += sqrt(x / i);
        i += 1;
    }
}

int main(void)
{   
    return g();
}
