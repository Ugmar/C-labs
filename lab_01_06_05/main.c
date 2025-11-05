#include <stdio.h>
#include <math.h>

#define EPS 1e-9
#define ERROR_UNCORRECT_VALUE 1
#define ERROR_NOT_SECTION 2

int point_side(double x0_line, double y0_line, double x1_line, double y1_line, double x1, double y1, double x2, double y2) 
{
    double side_1_point = (x1_line - x0_line) * (y1 - y0_line) - (y1_line - y0_line) * (x1 - x0_line);
    double side_2_point = (x1_line - x0_line) * (y2 - y0_line) - (y1_line - y0_line) * (x2 - x0_line);
    return (side_1_point * side_2_point < 0);
}

int main(void)  
{
    double xp, yp, xq, yq;
    double xr, yr, xs, ys;
    if (scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &xp, &yp, &xq, &yq, &xr, &yr, &xs, &ys) != 8) 
    {
        return ERROR_UNCORRECT_VALUE;
    }
    if ((fabs(xp - xq) < EPS && fabs(yp - yq) < EPS) || (fabs(xr - xs) < EPS && fabs(yr - ys) < EPS))
    {
        return ERROR_NOT_SECTION;
    }

    if (point_side(xr, yr, xs, ys, xp, yp, xq, yq) && point_side(xp, yp, xq, yq, xr, yr, xs, ys)) 
    {
        printf("%d\n", 1);
    } 
    else 
    {
        printf("%d\n", 0);
    }
    return 0;
}
