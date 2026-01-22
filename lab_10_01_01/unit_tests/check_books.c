#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book.h"
#include "list.h"

static node_t *unit_create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

static book_t *unit_create_book(const char *name, const char *author, int year)
{
    book_t *book = malloc(sizeof(book_t));

    if (!book)
        return NULL;

    book->name = strdup(name);
    book->author = strdup(author);
    book->year = year;
    book->cap_name = 0;
    book->cap_author = 0;

    return book;
}

static void unit_free_book(void *b)
{
    book_t *book = b;

    if (!book)
        return;
        
    free(book->name);
    free(book->author);
    free(book);
    
}

START_TEST(test_free_book_ok)
{
    book_t *book = unit_create_book("book", "author", 23);
    free_book(book);
}
END_TEST

START_TEST(test_free_book_partial_data)
{
    book_t *book = malloc(sizeof(book_t));
    book->name = strdup("book");
    book->author = NULL;
    book->year = 2023;

    free_book(book);
}
END_TEST

START_TEST(test_compare_book_sort_equal)
{
    book_t book1 = {.name = "eq", .author = "1", .year = 20};
    book_t book2 = {.name = "eq", .author = "2", .year = 21};

    int rc = compare_book_sort(&book1, &book2);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_compare_book_sort_gt)
{
    book_t book1 = {.name = "2", .author = "author", .year = 20};
    book_t book2 = {.name = "1", .author = "author", .year = 20};

    int rc = compare_book_sort(&book1, &book2);
    ck_assert_int_gt(rc, 0);
}
END_TEST

START_TEST(test_compare_book_sort_lt)
{
    book_t book1 = {.name = "1", .author = "author", .year = 20};
    book_t book2 = {.name = "2", .author = "author", .year = 20};

    int rc = compare_book_sort(&book1, &book2);
    ck_assert_int_lt(rc, 0);
}
END_TEST

START_TEST(test_compare_book_find_eq)
{
    book_t book1 = {.name = "eq", .author = "same", .year = 20};
    book_t book2 = {.name = "eq", .author = "same", .year = 20};

    int rc = compare_book_find(&book1, &book2);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_compare_book_find_diff_name)
{
    book_t book1 = {.name = "1", .author = "same", .year = 20};
    book_t book2 = {.name = "2", .author = "same", .year = 20};

    int rc = compare_book_find(&book1, &book2);
    ck_assert_int_ne(rc, 0);
}
END_TEST

START_TEST(test_compare_book_find_diff_author)
{
    book_t book1 = {.name = "same", .author = "A", .year = 20};
    book_t book2 = {.name = "same", .author = "B", .year = 20};

    int rc = compare_book_find(&book1, &book2);
    ck_assert_int_ne(rc, 0);
}
END_TEST

START_TEST(test_compare_book_find_diff_year)
{
    book_t book1 = {.name = "same", .author = "same", .year = 20};
    book_t book2 = {.name = "same", .author = "same", .year = 21};

    int rc = compare_book_find(&book1, &book2);
    ck_assert_int_ne(rc, 0);
}
END_TEST

START_TEST(test_input_book_valid)
{
    FILE *f = tmpfile();
    fprintf(f, "book\nauthor\n20\n");
    rewind(f);

    book_t *book = input_book(f);

    ck_assert_ptr_nonnull(book);
    ck_assert_str_eq(book->name, "book");
    ck_assert_str_eq(book->author, "author");
    ck_assert_int_eq(book->year, 20);

    unit_free_book(book);
}
END_TEST

START_TEST(test_input_book_empty_name)
{
    FILE *f = tmpfile();
    fprintf(f, "\nauthor\n20\n");
    rewind(f);

    book_t *book = input_book(f);

    ck_assert_ptr_nonnull(book);
    ck_assert_str_eq(book->name, "");
    ck_assert_str_eq(book->author, "author");
    ck_assert_int_eq(book->year, 20);

    unit_free_book(book);
}
END_TEST

START_TEST(test_input_book_missing_author)
{
    FILE *f = tmpfile();
    fprintf(f, "book\n");
    rewind(f);

    book_t *book = input_book(f);

    ck_assert_ptr_null(book);
}
END_TEST

START_TEST(test_input_book_invalid_year)
{
    FILE *f = tmpfile();
    fprintf(f, "book\nauthor\nqwewr\n");
    rewind(f);

    book_t *book = input_book(f);

    ck_assert_ptr_null(book);
}
END_TEST

START_TEST(test_input_books_valid)
{
    FILE *f = tmpfile();
    fprintf(f, "book 1\nauthor 1\n21\nbook 2\nauthor 2\n22\n");
    rewind(f);

    node_t *books = input_books(f);

    ck_assert_ptr_nonnull(books);

    ck_assert_str_eq(((book_t *)books->data)->name, "book 2");
    ck_assert_str_eq(((book_t *)books->data)->author, "author 2");
    ck_assert_int_eq(((book_t *)books->data)->year, 22);

    ck_assert_str_eq(((book_t *)books->next->data)->name, "book 1");
    ck_assert_str_eq(((book_t *)books->next->data)->author, "author 1");
    ck_assert_int_eq(((book_t *)books->next->data)->year, 21);

    unit_free_book(books->next->data);
    unit_free_book(books->data);
    free(books->next);
    free(books);
}
END_TEST

START_TEST(test_input_books_empty_file)
{
    FILE *f = tmpfile();
    node_t *books = input_books(f);

    ck_assert_ptr_null(books);
}
END_TEST

START_TEST(test_input_books_missing_data)
{
    FILE *f = tmpfile();
    fprintf(f, "book 1\nauthor 1\n21\nbook 2\n");
    rewind(f);

    node_t *books = input_books(f);

    ck_assert_ptr_null(books);
}
END_TEST

START_TEST(test_print_book_valid)
{
    book_t *book = unit_create_book("book", "author", 23);
    node_t node = {.data = book, .next = NULL};

    FILE *f = tmpfile();
    print_book(&node, f);
    rewind(f);

    char buffer[100];

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "23\n");

    unit_free_book(book);
}
END_TEST

START_TEST(test_print_books_empty_list)
{
    FILE *f = tmpfile();
    print_books(NULL, f);
    rewind(f);

    char buffer[100];

    ck_assert_ptr_null(fgets(buffer, sizeof(buffer), f));
}
END_TEST

START_TEST(test_print_books_multiple_books)
{
    node_t *book1 = unit_create_node(unit_create_book("book 1", "author 1", 21));
    node_t *book2 = unit_create_node(unit_create_book("book 2", "author 2", 22));
    book1->next = book2;

    FILE *f = tmpfile();
    print_books(book1, f);
    rewind(f);

    char buffer[100];

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "21\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "22\n");

    unit_free_book(book1->data);
    unit_free_book(book2->data);
    free(book1);
    free(book2);
}
END_TEST

START_TEST(test_insert_book_insert_in_middle)
{
    node_t* book1 = unit_create_node(unit_create_book("book 1", "author 1", 20));
    node_t* book2 = unit_create_node(unit_create_book("book 2", "author 2", 21));
    node_t* book3 = unit_create_node(unit_create_book("book 3", "author 3", 22));
    book1->next = book2;
    book2->next = book3;
    
    FILE* my_stdin = tmpfile();
    FILE* my_stdout = tmpfile();
 
    fprintf(my_stdin, "book 2\nauthor 2\n21\n");
    fprintf(my_stdin, "book\nauthor\n23\n");
    rewind(my_stdin);
    
    FILE* orig_stdin = stdin;
    FILE* orig_stdout = stdout;
    stdin = my_stdin;
    stdout = my_stdout;
    
    int rc = insert_book(&book1, stdout);
    
    stdin = orig_stdin;
    stdout = orig_stdout;
    
    ck_assert_int_eq(rc, 0);
    
    rewind(my_stdout);
    char buffer[100];

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "book 1\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "author 1\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "20\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "book\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "author\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "23\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "book 2\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "author 2\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "21\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "book 3\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "author 3\n");

    fgets(buffer, sizeof(buffer), my_stdout);
    ck_assert_str_eq(buffer, "22\n");

    unit_free_book(book1->next->next->next->data);
    unit_free_book(book1->next->next->data);
    unit_free_book(book1->next->data);
    unit_free_book(book1->data);

    free(book1->next->next->next);
    free(book1->next->next);
    free(book1->next);
    free(book1);
}
END_TEST

START_TEST(test_insert_book_not_found)
{
    node_t *head = unit_create_node(unit_create_book("exist book", "exist author", 20));

    FILE *stdin_my = tmpfile();
    fprintf(stdin_my, "not exist book\nnot exist author\n23\n");
    rewind(stdin_my);

    FILE *stdout_my = tmpfile();

    FILE *orig_stdin = stdin;
    FILE *orig_stdout = stdout;

    stdin = stdin_my;
    stdout = stdout_my;

    int rc = insert_book(&head, stdout);

    stdin = orig_stdin;
    stdout = orig_stdout;

    ck_assert_int_eq(rc, 0);

    rewind(stdout_my);

    char buffer[256];
    fgets(buffer, sizeof(buffer), stdout_my);

    ck_assert_str_eq(buffer, "Книга не найдена\n");

   unit_free_book(head->data);
   free(head);
}
END_TEST

START_TEST(test_insert_book_empty_search_el)
{
    node_t* head = unit_create_node(unit_create_book("exist book", "exist author", 20));
    
    FILE* my_stdin = tmpfile();
    FILE* my_stdout = tmpfile();
    
    FILE* orig_stdin = stdin;
    FILE* orig_stdout = stdout;

    stdin = my_stdin;
    stdout = my_stdout;
    
    int rc = insert_book(&head, stdout);
    
    stdin = orig_stdin;
    stdout = orig_stdout;
    
    ck_assert_int_eq(rc, 4);
    
    unit_free_book(head->data);
    free(head);
}
END_TEST

START_TEST(test_insert_book_invalid_inserting_book)
{
    node_t* head = unit_create_node(unit_create_book("exist book", "exist author", 20));
    
    FILE* my_stdin = tmpfile();
    FILE* my_stdout = tmpfile();
    
    fprintf(my_stdin, "exist book\nexist author\n20\n");
    fprintf(my_stdin, "book\n");
    rewind(my_stdin);
    
    FILE* orig_stdin = stdin;
    FILE* orig_stdout = stdout;

    stdin = my_stdin;
    stdout = my_stdout;
    
    int rc = insert_book(&head, stdout);
    
    stdin = orig_stdin;
    stdout = orig_stdout;
    
    ck_assert_int_eq(rc, 4);

    unit_free_book(head->data);
    free(head);
}
END_TEST

START_TEST(test_reverse_books_valid)
{
    node_t *book1 = unit_create_node(unit_create_book("book 1", "author 1", 21));
    node_t *book2 = unit_create_node(unit_create_book("book 2", "author 2", 22));
    book1->next = book2;

    FILE *f = tmpfile();
    int rc = reverse_books(&book1, f);

    ck_assert_int_eq(rc, 0);

    rewind(f);

    char buffer[100];

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "22\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "21\n");

    unit_free_book(book1->next->data);
    unit_free_book(book1->data);
    free(book1->next);
    free(book1);
}
END_TEST

START_TEST(test_sort_books_valid)
{
    node_t *book2 = unit_create_node(unit_create_book("book 2", "author 2", 22));
    node_t *book1 = unit_create_node(unit_create_book("book 1", "author 1", 21));
    book2->next = book1;

    FILE *f = tmpfile();
    int rc = sort_books(&book2, f);

    ck_assert_int_eq(rc, 0);

    rewind(f);

    char buffer[100];

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 1\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "21\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "book 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "author 2\n");

    fgets(buffer, sizeof(buffer), f);
    ck_assert_str_eq(buffer, "22\n");

    unit_free_book(book2->next->data);
    unit_free_book(book2->data);
    free(book2->next);
    free(book2);
}
END_TEST

START_TEST(test_sort_books_empty_list)
{
    node_t *head = NULL;

    FILE *f = tmpfile();
    int rc = sort_books(&head, f);

    ck_assert_int_eq(rc, 0);

    rewind(f);
    char buffer[100];
    ck_assert_ptr_null(fgets(buffer, sizeof(buffer), f));
}
END_TEST

Suite *book_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("book");

    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_free_book_ok);
    tcase_add_test(tc_pos, test_free_book_partial_data);
    tcase_add_test(tc_pos, test_compare_book_sort_equal);
    tcase_add_test(tc_pos, test_compare_book_sort_gt);
    tcase_add_test(tc_pos, test_compare_book_sort_lt);
    tcase_add_test(tc_pos, test_compare_book_find_eq);
    tcase_add_test(tc_pos, test_compare_book_find_diff_name);
    tcase_add_test(tc_pos, test_compare_book_find_diff_author);
    tcase_add_test(tc_pos, test_compare_book_find_diff_year);
    tcase_add_test(tc_pos, test_input_book_valid);
    tcase_add_test(tc_pos, test_input_books_valid);
    tcase_add_test(tc_pos, test_print_book_valid);
    tcase_add_test(tc_pos, test_print_books_multiple_books);
    tcase_add_test(tc_pos, test_insert_book_not_found);
    tcase_add_test(tc_pos, test_insert_book_insert_in_middle);
    tcase_add_test(tc_pos, test_reverse_books_valid);
    tcase_add_test(tc_pos, test_sort_books_valid);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");

    tcase_add_test(tc_neg, test_input_book_empty_name);
    tcase_add_test(tc_neg, test_input_book_missing_author);
    tcase_add_test(tc_neg, test_input_book_invalid_year);
    tcase_add_test(tc_neg, test_input_books_empty_file);
    tcase_add_test(tc_neg, test_input_books_missing_data);
    tcase_add_test(tc_neg, test_print_books_empty_list);
    tcase_add_test(tc_neg, test_sort_books_empty_list);
    tcase_add_test(tc_neg, test_insert_book_empty_search_el);
    tcase_add_test(tc_neg, test_insert_book_invalid_inserting_book);

    suite_add_tcase(s, tc_neg);
    return s;
}
