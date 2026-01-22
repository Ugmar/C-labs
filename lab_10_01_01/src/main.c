#include <stdio.h>
#include <string.h>

#include "book.h"
#include "errors.h"
#include "list.h"

#define INSERT "insert"
#define LEN_INSERT 6
#define REVERSE "reverse"
#define LEN_REVERSE 7
#define SORT "sort"
#define LEN_SORT 4

#define COUNT_ARG 4

int main(int argc, char **argv)
{
    if (argc != COUNT_ARG)
        return ERROR_COUNT_ARG;

    char *input = argv[1];
    char *output = argv[2];
    char *action = argv[3];
    int rc = OK;

    FILE *file_read = fopen(input, "r");

    if (!file_read)
        return ERROR_IO_FILE;

    FILE *file_write = fopen(output, "w");

    if (!file_write)
    {
        fclose(file_read);

        return ERROR_IO_FILE;
    }

    node_t *list_books = input_books(file_read);

    if (!list_books)
        rc = ERROR_INPUT;
    else if (strncmp(action, INSERT, LEN_INSERT) == 0)
        rc = insert_book(&list_books, file_write);
    else if (strncmp(action, REVERSE, LEN_REVERSE) == 0)
        rc = reverse_books(&list_books, file_write);
    else if (strncmp(action, SORT, LEN_SORT) == 0)
        rc = sort_books(&list_books, file_write);
    else
        rc = ERROR_UNDEFINE_ACTION;

    free_books(list_books);
    fclose(file_read);
    fclose(file_write);

    return rc;
}
