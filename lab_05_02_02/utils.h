#ifndef UTILS_H__
#define UTILS_H__

#include <stdio.h>

#define ERROR_INVALID_PARAM 1
#define ERROR_IO_FILE 2
#define ERROR_NO_DATA -3
#define OK 0

double calc_avg(FILE *f, int *n);
double calc_variance(FILE *f, double avg);

#endif
