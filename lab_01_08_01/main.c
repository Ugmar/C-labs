#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define ERROR_UNCORRECT_VALUE 1
#define ERROR_LARGE_BYTE 2
#define SIZE_UINT32 sizeof(uint32_t)

int write_bin_digit(uint32_t s)
{
    printf("Result: ");
    for (int i = (CHAR_BIT * SIZE_UINT32) - 1; i >= 0; i--)
    {
        printf("%d", (s >> i) & 1);
    }
    printf("\n");
    return 0;
}

uint32_t pack(uint32_t b1, uint32_t b2, uint32_t b3, uint32_t b4)
{
    return (b1 << CHAR_BIT * 3) | (b2 << CHAR_BIT * 2) | (b3 << CHAR_BIT) | b4;
}

int main(void)
{
    uint32_t b1, b2, b3, b4;
    if (scanf("%u %u %u %u", &b1, &b2, &b3, &b4) != 4)
    {
        printf("Error: Uncorrect value");
        return ERROR_UNCORRECT_VALUE;    
    }
    if (b1 > UCHAR_MAX || b2 > UCHAR_MAX || b3 > UCHAR_MAX || b4 > UCHAR_MAX)
    {
        printf("Error: Large byte value");
        return ERROR_LARGE_BYTE;
    }

    uint32_t s;
    s = pack(b1, b2, b3, b4);
    write_bin_digit(s);

    b1 = (s >> CHAR_BIT * 3) & 0xff;
    b2 = (s >> CHAR_BIT * 2) & 0xff;
    b3 = (s >> CHAR_BIT) & 0xff;
    b4 = s & 0xff;
    
    printf("%d %d %d %d\n", b1, b2, b3, b4); 
    return 0;
}
