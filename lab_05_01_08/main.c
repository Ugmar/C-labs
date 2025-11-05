#include "utils.h"

int main(void)
{
    int distance = 0;
    int rc = search_min_distance(stdin, &distance);

    switch (rc)
    {
        case ERROR_INVALID_EL:
            return ERROR_INVALID_EL;
        case ERROR_NOT_MAX:
            return ERROR_NOT_MAX;
            break;
        case OK:
            printf("%d\n", distance);
            return OK;
    }
}
