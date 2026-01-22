#include <string.h>
#include <dlfcn.h>

#include "io.h"
#include "errors.h"
#include "filter.h"
#include "sort.h"

#define COUNT_ARG 4

int compare_int(const void *first, const void *second)
{
    return *(int *)first - *(int *)second;
}

int main(int argc, char **argv)
{
    if (argc > COUNT_ARG || argc < COUNT_ARG - 1)
        return ERROR_COUNT_ARGC;

    if (argc == COUNT_ARG && strncmp(argv[3], "f", 1) != 0)
        return ERROR_INVALID_PARAM;

    FILE *input_file = NULL;
    int *start_arr = NULL, *end_arr = NULL;

    void *hlib = dlopen("./out/libsort.so", RTLD_NOW);

    if (!hlib)
    {
        dlclose(hlib);
        return ERROR_PTR_FUNC;
    }

    void (*mysort)(void *, size_t, size_t, compare_t) = dlsym(hlib, "mysort");

    if (!mysort)
    {
        dlclose(hlib);
        return ERROR_PTR_FUNC;
    }

    input_file = fopen(argv[1], "r");

    int rc = create_arr(input_file, &start_arr, &end_arr);

    if (input_file != NULL)
        fclose(input_file);

    if (rc)
    {
        free(start_arr);
        dlclose(hlib);
        return rc;
    }

    if (argc == COUNT_ARG)
    {
        int *start_filter_arr = NULL, *end_filter_arr = NULL;

        size_t len = end_arr - start_arr;

        int rc = count_filter_elems(start_arr, end_arr, &len);

        if (!len)
        {
            free(start_arr);
            dlclose(hlib);
            return ERROR_EMPTY_ARR;
        }

        if (rc)
        {
            free(start_arr);
            dlclose(hlib);
            return rc;
        }

        start_filter_arr = malloc(len * sizeof(int));

        if (!start_filter_arr)
        {
            free(start_arr);
            dlclose(hlib);
            return rc;
        }

        end_filter_arr = start_filter_arr + len;

        rc = key(start_arr, end_arr, &start_filter_arr, &end_filter_arr);
        free(start_arr);

        if (rc)
        {
            free(start_filter_arr);
            dlclose(hlib);
            return rc;
        }

        start_arr = start_filter_arr;
        end_arr = end_filter_arr;
    }

    mysort(start_arr, end_arr - start_arr, sizeof(int), compare_int);

    FILE *output_file = NULL;
    output_file = fopen(argv[2], "w");

    rc = fprint_arr(output_file, start_arr, end_arr);

    if (output_file != NULL)
        fclose(output_file);

    free(start_arr);
    start_arr = NULL;

    dlclose(hlib);

    if (rc)
        return rc;

    return OK;
}
