#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#include "book.h"
#include "errors.h"

void free_book(void *b)
{
    book_t *book = b;

    if (book)
    {
        free(book->name);
        free(book->author);
        free(book);
    }
}

int compare_book_sort(const void *book1, const void *book2)
{
    const book_t *b1 = book1;
    const book_t *b2 = book2;
    return strncmp(b1->name, b2->name, strlen(b1->name));
}

int compare_book_find(const void *book1, const void *book2)
{
    const book_t *b1 = book1;
    const book_t *b2 = book2;
    return strncmp(b1->name, b2->name, strlen(b1->name)) || strncmp(b1->author, b2->author, strlen(b1->author)) || !(b1->year == b2->year);
}

void free_books(node_t *books)
{
    if (!books)
        return;

    node_t *next;

    while (books)
    {
        next = books->next;
        free_book(books->data);
        books = next;
    }
}

book_t *input_book(FILE *file_read)
{
    book_t *book = malloc(sizeof(book_t));

    if (!book)
        return NULL;

    book->cap_author = 0;
    book->cap_name = 0;
    book->author = NULL;
    book->name = NULL;
    book->year = 0;

    ssize_t len_name = getline(&book->name, &book->cap_name, file_read);

    if (len_name == -1)
    {
        free(book->name);
        free(book);

        return NULL;
    }

    if (book->name[strlen(book->name) - 1] == '\n')
        book->name[strlen(book->name) - 1] = '\0';

    ssize_t len_author = getline(&book->author, &book->cap_author, file_read);

    if (len_author == -1)
    {
        free(book->name);
        free(book->author);
        free(book);

        return NULL;
    }

    if (book->author[strlen(book->author) - 1] == '\n')
        book->author[strlen(book->author) - 1] = '\0';

    if (fscanf(file_read, "%d", &book->year) != 1)
    {
        free(book->name);
        free(book->author);
        free(book);

        return NULL;
    }

    fgetc(file_read);

    return book;
}

node_t *input_books(FILE *file_read)
{
    node_t *node = NULL;
    node_t *head = NULL;
    char c;

    while (!feof(file_read))
    {
        book_t *book = input_book(file_read);

        if (!book)
        {
            free_books(head);
            free_list(head);

            return NULL;
        }

        node = create_node(book);

        if (!node)
        {
            free_books(head);
            free_list(head);
            
            free(book->name);
            free(book->author);
            free(book);

            return NULL;
        }

        node->next = head;
        head = node;

        c = fgetc(file_read);

        if (c != EOF)
            ungetc(c, file_read);
    }

    return head;
}

void print_book(node_t *node, FILE *file)
{
    book_t *book = node->data;

    fprintf(file, "%s\n", book->name);
    fprintf(file, "%s\n", book->author);
    fprintf(file, "%d\n", book->year);
}

void print_books(node_t *head, FILE *file)
{
    for (; head; head = head->next)
    {
        print_book(head, file);
    }
}

int insert_book(node_t **head, FILE *file_write)
{
    book_t *book = input_book(stdin);

    if (!book)
        return ERROR_INPUT;

    node_t *node = find(*head, book, compare_book_find);

    if (node)
    {
        book_t *inserting_book = input_book(stdin);

        if (!inserting_book)
        {
            free_book(book);
            return ERROR_INPUT;
        }

        node_t *inseting_node = create_node(inserting_book);

        if (!inseting_node)
        {
            free_book(book);
            free_book(inserting_book);
            return ERROR_MEMMORY;
        }

        insert(head, inseting_node, node);
        print_books(*head, file_write);
        free_book(book);
    }
    else
    {
        fprintf(file_write, "Книга не найдена\n");
        free_book(book);
    }

    return OK;
}

int reverse_books(node_t **head, FILE *file_write)
{
    *head = reverse(*head);
    print_books(*head, file_write);
    return OK;
}

int sort_books(node_t **head, FILE *file_write)
{
    *head = sort(*head, compare_book_sort);
    print_books(*head, file_write);
    return OK;
}
