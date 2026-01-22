#include "product.h"

#define ERROR_COUNT_ARG 1
#define ERROR_PRICE 2

#define COUNT_ARG 3

int main(int argc, char **argv)
{
    if (argc != COUNT_ARG)
        return ERROR_COUNT_ARG;
    
    char *err_ptr;
    double price = strtod(argv[COUNT_ARG - 1], &err_ptr);

    if (*err_ptr != '\0' || price < 0)
        return ERROR_PRICE;

    FILE *f = fopen(argv[1], "r");

    if (!f)
        return ERROR_IO_FILE;
    
    struct product *products = NULL;
    int count_product = read_count_product(f);

    if (count_product <= 0)
        return ERROR_COUNT_PRODUCT;

    products = malloc(count_product * sizeof(struct product));

    if (!products)
        return ERROR_MEMORY;

    int rc = read_product(f, products, &count_product);
    fclose(f);

    if (rc)
    {
        free_products(products, count_product);
        return rc;
    }

    print_products_less_price(products, count_product, price, stdout);
    free_products(products, count_product);

    return OK;
}
