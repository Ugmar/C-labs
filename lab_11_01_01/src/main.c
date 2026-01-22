#include <stdio.h>

#include "my_snprintf.h"

int main(void)
{
    char buffer[100];

    my_snprintf(buffer, sizeof(buffer), "char: %c", 'A');
    printf("1. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "string: %s", "Hello, World!");
    printf("2. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "int: %d", 12345);
    printf("3. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "hex: %d", 0xABCD);
    printf("4. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "oct: %d", 0777);
    printf("5. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "long: %ld short: %hd", 1234567890L, (short)123);
    printf("6. %s\n", buffer);

    my_snprintf(buffer, sizeof(buffer), "%c %s %ld %lx %lo", 'z', "word", -123, 123, 123);
    printf("7. %s\n", buffer);

    return 0;
}
