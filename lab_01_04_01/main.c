#include <stdio.h>

#define FLAT_IN_ENTRANCE 36
#define FLAT_IN_FLOOR 4
#define ERROR_UNCORRECT_VALUE 1

int main(void)
{
    int flat;
    if (scanf("%d", &flat) != 1)
    {
        return ERROR_UNCORRECT_VALUE;
    }
    
    int entrance = (flat - 1) / FLAT_IN_ENTRANCE;
    int floor = ((flat - entrance * FLAT_IN_ENTRANCE) - 1) / FLAT_IN_FLOOR + 1;
    printf("Entrance = %d\nFloor = %d\n", entrance + 1, floor);
    return 0;
}
