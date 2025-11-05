#include <limits.h>

#include "utils.h"

int search_min_distance(FILE *f, int *min_distance)
{
    *min_distance = 0;

    int number = 2;
    int index_max = 0;
    int last_el, el, next_el;

    if (fscanf(f, "%d %d", &last_el, &el) != 2)
    {
        return ERROR_INVALID_EL;
    }

    while (fscanf(f, "%d", &next_el) == 1)
    {
        if (el > last_el && el > next_el)
        {
            if (number - index_max < *min_distance)
            {
                *min_distance = number - index_max;
            }
            else if (index_max > 0 && *min_distance == 0)
            {
                *min_distance = number - index_max;
            }

            index_max = number;
        }

        last_el = el;
        el = next_el;
        number++;
    }

    if (*min_distance == 0)
    {
        return ERROR_NOT_MAX;
    }

    return OK;
}
