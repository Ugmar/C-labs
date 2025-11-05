#include <stdlib.h>

#include "book.h"

int main(void)
{
    struct book books[COUNT_BOOK];

    size_t len;
    int rc = input_books(books, &len);

    if (rc != OK)
    {
        return rc;
    }

    len = books_delete_max_id(books, len);

    len = books_leave_only_may(books, len);

    len = books_unique_name(books, len);
    
    rc = print_book(books, len);

    if (rc != OK)
    {
        return rc;
    }

    return OK;
}
