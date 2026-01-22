#include <check.h>

#include "list.h"
#include "matrix.h"

static elem_t *unit_create_elem(size_t i, size_t j, int value)
{
    elem_t *elem = malloc(sizeof(elem_t));

    if (!elem)
        return NULL;

    elem->i = i;
    elem->j = j;
    elem->value = value;

    return elem;
}

static node_t *unit_create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

static void unit_free_node(node_t *node)
{
    free(node);
}

static void unit_free_list(node_t *head)
{
    while (head)
    {
        node_t *next = head->next;
        free(head->data);
        unit_free_node(head);
        head = next;
    }
}     

START_TEST(test_compare_elem_diff_rows)
{
    elem_t elem1 = {1, 0, 10};
    elem_t elem2 = {2, 0, 20};

    int is_eq = compare_elem(&elem1, &elem2);
    ck_assert_int_eq(is_eq, -1);
}
END_TEST

START_TEST(test_compare_elem_same_row_diff_cols)
{
    elem_t elem1 = {1, 1, 10};
    elem_t elem2 = {1, 2, 20};

    int is_eq = compare_elem(&elem1, &elem2);
    ck_assert_int_eq(is_eq, -1);
}
END_TEST

START_TEST(test_compare_elem_equal)
{
    elem_t elem1 = {1, 1, 10};
    elem_t elem2 = {1, 1, 20};

    int is_eq = compare_elem(&elem1, &elem2);
    ck_assert_int_eq(is_eq, 0);
}
END_TEST

START_TEST(test_add_matrix_both_empty)
{
    node_t *result = add_matrix(NULL, NULL);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_add_matrix_first_empty)
{
    node_t *matrix = unit_create_node(unit_create_elem(0, 0, 5));
    matrix->next = unit_create_node(unit_create_elem(0, 0, 6));

    node_t *result = add_matrix(NULL, matrix);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(((elem_t *)result->data)->value, 5);
    ck_assert_int_eq(((elem_t *)result->next->data)->value, 6);

    unit_free_list(matrix);
    unit_free_list(result);
}
END_TEST

START_TEST(test_add_matrix_diff_index)
{
    node_t *matrix1 = unit_create_node(unit_create_elem(0, 0, 1));
    node_t *matrix2 = unit_create_node(unit_create_elem(0, 1, 2));

    node_t *result = add_matrix(matrix1, matrix2);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(get_value(result->data), 1);
    ck_assert_int_eq(get_value(result->next->data), 2);

    unit_free_list(result);
    unit_free_list(matrix1);
    unit_free_list(matrix2);
}
END_TEST

START_TEST(test_add_matrix_same_index)
{
    node_t *matrix1 = unit_create_node(unit_create_elem(0, 0, 1));
    node_t *matrix2 = unit_create_node(unit_create_elem(0, 0, 2));

    node_t *result = add_matrix(matrix1, matrix2);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(get_value(result->data), 3);

    unit_free_list(result);
    unit_free_list(matrix1);
    unit_free_list(matrix2);
}
END_TEST

START_TEST(test_add_matrix_zero_elements)
{
    node_t *matrix1 = unit_create_node(unit_create_elem(0, 0, 1));
    node_t *matrix2 = unit_create_node(unit_create_elem(0, 0, -1));

    node_t *result = add_matrix(matrix1, matrix2);

    ck_assert_ptr_null(result);

    unit_free_list(matrix1);
    unit_free_list(matrix2);
}
END_TEST

START_TEST(test_transpose_matrix_empty)
{
    node_t *result = transpose_matrix(NULL);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_transpose_matrix_single_element)
{
    node_t *matrix = unit_create_node(unit_create_elem(0, 1, 5));

    node_t *result = transpose_matrix(matrix);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(get_i(result->data), 1);
    ck_assert_int_eq(get_j(result->data), 0);
    ck_assert_int_eq(get_value(result->data), 5);

    unit_free_list(result);
    unit_free_list(matrix);
}
END_TEST

START_TEST(test_mul_matrix_both_empty)
{
    node_t *result = mul_matrix(NULL, NULL);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_mul_matrix_simple)
{
    node_t *matrix1 = unit_create_node(unit_create_elem(0, 0, 1));
    matrix1->next = unit_create_node(unit_create_elem(0, 1, 2));

    node_t *matrix2 = unit_create_node(unit_create_elem(0, 0, 2));
    matrix2->next = unit_create_node(unit_create_elem(1, 0, 3));

    node_t *result = mul_matrix(matrix1, matrix2);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(get_value(result->data), 8);

    unit_free_list(result);
    unit_free_list(matrix1);
    unit_free_list(matrix2);
}
END_TEST

START_TEST(test_lin_matrix_empty)
{
    node_t *result = lin_matrix(NULL);
    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_lin_matrix_single_element)
{
    node_t *matrix = unit_create_node(unit_create_elem(0, 0, 5));

    node_t *result = lin_matrix(matrix);

    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_lin_matrix_multiple_rows)
{
    node_t *matrix = unit_create_node(unit_create_elem(1, 0, 10));
    matrix->next = unit_create_node(unit_create_elem(0, 0, 5));
    matrix->next->next = unit_create_node(unit_create_elem(1, 1, 8));

    node_t *result = lin_matrix(matrix);

    ck_assert_ptr_nonnull(result);
    ck_assert_int_eq(get_i(result->data), 0);
    ck_assert_int_eq(get_value(result->data), 5);
    ck_assert_ptr_null(result->next);

    unit_free_list(result);
}
END_TEST

Suite *matrix_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("matrix");

    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_compare_elem_diff_rows);
    tcase_add_test(tc_pos, test_compare_elem_same_row_diff_cols);
    tcase_add_test(tc_pos, test_compare_elem_equal);
    tcase_add_test(tc_pos, test_add_matrix_diff_index);
    tcase_add_test(tc_pos, test_add_matrix_same_index);
    tcase_add_test(tc_pos, test_transpose_matrix_single_element);
    tcase_add_test(tc_pos, test_mul_matrix_simple);
    tcase_add_test(tc_pos, test_lin_matrix_single_element);
    tcase_add_test(tc_pos, test_lin_matrix_multiple_rows);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, test_add_matrix_both_empty);
    tcase_add_test(tc_neg, test_add_matrix_first_empty);
    tcase_add_test(tc_neg, test_add_matrix_zero_elements);
    tcase_add_test(tc_neg, test_transpose_matrix_empty);
    tcase_add_test(tc_neg, test_mul_matrix_both_empty);
    tcase_add_test(tc_neg, test_lin_matrix_empty);
    suite_add_tcase(s, tc_neg);

    return s;
}

START_TEST(test_input_matrix_valid_data)
{
    char *input_data = "2 2\n1 0\n0 2\n";
    FILE *f = tmpfile();
    fprintf(f, "%s", input_data);
    rewind(f);

    node_t *result = input_matrix(f);

    ck_assert_ptr_nonnull(result);

    ck_assert_ptr_nonnull(result->data);
    ck_assert_int_eq(((elem_t *)result->data)->i, 0);
    ck_assert_int_eq(((elem_t *)result->data)->j, 0);
    ck_assert_int_eq(((elem_t *)result->data)->value, 1);

    ck_assert_ptr_nonnull(result->next);
    ck_assert_ptr_nonnull(result->next->data);
    ck_assert_int_eq(((elem_t *)result->next->data)->i, 1);
    ck_assert_int_eq(((elem_t *)result->next->data)->j, 1);
    ck_assert_int_eq(((elem_t *)result->next->data)->value, 2);

    ck_assert_ptr_null(result->next->next);

    unit_free_list(result);
}
END_TEST

START_TEST(test_input_matrix_invalid_size)
{
    char *input_data = "adfsg";
    FILE *f = tmpfile();
    fprintf(f, "%s", input_data);
    rewind(f);

    node_t *result = input_matrix(f);

    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_input_matrix_negative_size)
{
    char *input_data = "-2 3";
    FILE *f = tmpfile();
    fprintf(f, "%s", input_data);
    rewind(f);

    node_t *result = input_matrix(f);

    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_input_matrix_invalid_data)
{
    char *input_data = "2 2\n 1 2\n fsdgf 4";
    FILE *f = tmpfile();
    fprintf(f, "%s", input_data);
    rewind(f);

    node_t *result = input_matrix(f);

    ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_print_elem_valid)
{
    elem_t *elem = unit_create_elem(1, 2, 52);

    char buffer[120];
    FILE *f = tmpfile();

    print_elem(elem, f);
    rewind(f);

    fgets(buffer, sizeof(buffer), f);

    ck_assert_str_eq(buffer, "1 2 52 ");

    free(elem);
}
END_TEST

START_TEST(test_print_matrix_valid)
{
    elem_t *elem1 = unit_create_elem(1, 2, 52);
    elem_t *elem2 = unit_create_elem(2, 5, 37);

    node_t *matrix = unit_create_node(elem1);
    matrix->next = unit_create_node(elem2);

    char buffer[120];
    FILE *f = tmpfile();

    print_matrix(matrix, f);
    rewind(f);

    fgets(buffer, sizeof(buffer), f);

    ck_assert_str_eq(buffer, "1 2 52 2 5 37 ");

    unit_free_list(matrix);
}
END_TEST

Suite *io_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("io");

    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_input_matrix_valid_data);
    tcase_add_test(tc_pos, test_print_elem_valid);
    tcase_add_test(tc_pos, test_print_matrix_valid);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");
    tcase_add_test(tc_neg, test_input_matrix_invalid_data);
    tcase_add_test(tc_neg, test_input_matrix_negative_size);
    tcase_add_test(tc_neg, test_input_matrix_invalid_size);
    suite_add_tcase(s, tc_neg);

    return s;
}
