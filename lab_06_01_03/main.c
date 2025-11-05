#include "product.h"

#define ERROR_COUNT_ARG 1
#define ERROR_PRICE 2
#define ERROR_INPUT_PRODUCT 3
#define OK 0

#define COUNT_ARG 3
#define BASE 10

int main(int argc, char **argv)
{
    if (argc != COUNT_ARG)
        return ERROR_COUNT_ARG;
    
    char *err_ptr;
    double price = strtod(argv[COUNT_ARG - 1], &err_ptr);

    if (*err_ptr != '\0' || price < 0)
        return ERROR_PRICE;

    struct product arr_product[COUNT_PRODUCT];

    int size_arr = input_product(argv[1], arr_product);

    if (size_arr <= 0)
        return ERROR_INPUT_PRODUCT;

    print_products_less_price(arr_product, size_arr, price);

    return OK;
}
