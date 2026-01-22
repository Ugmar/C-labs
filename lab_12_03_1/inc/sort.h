#ifndef SORT_H__
#define SORT_H__

#include <stdlib.h>

typedef int (*compare_t)(const void *, const void *);

void mysort(void *base, size_t num, size_t size, compare_t compare);

#endif
