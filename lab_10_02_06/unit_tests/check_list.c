#include "list.h"
#include <check.h>

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
        unit_free_node(head);
        head = next;
    }
}  

START_TEST(test_create_node_ok)
{
    int data = 52;
    int *ptr = &data;

    node_t *node = create_node(ptr);

    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(node->data, ptr);
    ck_assert_ptr_null(node->next);

    unit_free_node(node);
}
END_TEST

START_TEST(test_create_node_null_data)
{
    node_t *node = create_node(NULL);

    ck_assert_ptr_null(node);
}
END_TEST

START_TEST(test_free_list_null)
{
    free_list(NULL);
}
END_TEST

START_TEST(test_free_list_single_node)
{
    int data = 52;
    int *ptr = &data;

    node_t *node = unit_create_node(ptr);
    free_list(node);
}
END_TEST

START_TEST(test_free_list_multiple_nodes)
{
    int data1 = 52;
    int *ptr1 = &data1;

    int data2 = 24;
    int *ptr2 = &data2;

    int data3 = 40;
    int *ptr3 = &data3;

    node_t *head = unit_create_node(ptr1);
    head->next = unit_create_node(ptr2);
    head->next->next = unit_create_node(ptr3);

    free_list(head);
}
END_TEST

START_TEST(test_reverse_empty_list)
{
    node_t *res = reverse(NULL);

    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_reverse_single_node)
{
    int data1 = 52;
    int *ptr1 = &data1;

    node_t *node = unit_create_node(ptr1);
    node_t *res = reverse(node);

    ck_assert_ptr_eq(res, node);
    ck_assert_ptr_null(res->next);

    unit_free_list(res);
}
END_TEST

START_TEST(test_reverse_multiple_nodes)
{
    int data1 = 1;
    int *ptr1 = &data1;

    int data2 = 2;
    int *ptr2 = &data2;

    int data3 = 3;
    int *ptr3 = &data3;

    node_t *node1 = unit_create_node(ptr1);
    node_t *node2 = unit_create_node(ptr2);
    node_t *node3 = unit_create_node(ptr3);

    node1->next = node2;
    node2->next = node3;

    node_t *res = reverse(node1);

    ck_assert_ptr_eq(res, node3);
    ck_assert_ptr_eq(res->next, node2);
    ck_assert_ptr_eq(res->next->next, node1);
    ck_assert_ptr_null(res->next->next->next);

    unit_free_list(res);
}
END_TEST

START_TEST(test_front_back_split_empty)
{
    node_t *back = NULL;
    front_back_split(NULL, &back);

    ck_assert_ptr_null(back);
}
END_TEST

START_TEST(test_front_back_split_single_node)
{
    int data1 = 3;
    int *ptr1 = &data1;

    node_t *head = unit_create_node(ptr1);
    node_t *back = NULL;

    front_back_split(head, &back);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_null(back);
    ck_assert_ptr_null(head->next);

    unit_free_list(head);
}
END_TEST

START_TEST(test_front_back_split_two_nodes)
{
    int data1 = 3;
    int *ptr1 = &data1;

    int data2 = 5;
    int *ptr2 = &data2;

    node_t *head = unit_create_node(ptr1);
    head->next = unit_create_node(ptr2);
    node_t *back = NULL;

    front_back_split(head, &back);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_nonnull(back);
    ck_assert_ptr_null(head->next);
    ck_assert_ptr_null(back->next);

    unit_free_list(head);
    unit_free_list(back);
}
END_TEST

START_TEST(test_front_back_split_three_nodes)
{
    int data1 = 3;
    int *ptr1 = &data1;

    int data2 = 5;
    int *ptr2 = &data2;

    int data3 = 7;
    int *ptr3 = &data3;

    node_t *head = unit_create_node(ptr1);
    head->next = unit_create_node(ptr2);
    head->next->next = unit_create_node(ptr3);
    node_t *back = NULL;

    front_back_split(head, &back);

    ck_assert_ptr_nonnull(head);
    ck_assert_ptr_nonnull(head->next);
    ck_assert_ptr_null(head->next->next);

    ck_assert_ptr_nonnull(back);
    ck_assert_ptr_null(back->next);

    unit_free_list(head);
    unit_free_list(back);
}
END_TEST

static int compare_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

START_TEST(test_sorted_merge_both_empty)
{
    node_t *a = NULL;
    node_t *b = NULL;

    node_t *res = sorted_merge(&a, &b, compare_int);

    ck_assert_ptr_null(res);
    ck_assert_ptr_null(a);
    ck_assert_ptr_null(b);
}
END_TEST

START_TEST(test_sorted_merge_first_empty)
{
    int data3 = 1;
    int *ptr3 = &data3;

    node_t *a = NULL;
    node_t *b = unit_create_node(ptr3);

    node_t *res = sorted_merge(&a, &b, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 1);
    ck_assert_ptr_null(a);
    ck_assert_ptr_null(b);

    unit_free_list(res);
}
END_TEST

START_TEST(test_sorted_merge_second_empty)
{
    int data3 = 1;
    int *ptr3 = &data3;

    node_t *a = unit_create_node(ptr3);
    node_t *b = NULL;

    node_t *res = sorted_merge(&a, &b, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 1);
    ck_assert_ptr_null(a);
    ck_assert_ptr_null(b);

    unit_free_list(res);
}
END_TEST

START_TEST(test_sorted_merge_sorted_lists)
{
    int data1 = 1;
    int *ptr1 = &data1;

    int data2 = 2;
    int *ptr2 = &data2;

    int data3 = 3;
    int *ptr3 = &data3;

    int data4 = 4;
    int *ptr4 = &data4;

    node_t *a = unit_create_node(ptr1);
    a->next = unit_create_node(ptr2);

    node_t *b = unit_create_node(ptr3);
    b->next = unit_create_node(ptr4);

    node_t *res = sorted_merge(&a, &b, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 1);
    ck_assert_int_eq(*(int *)res->next->data, 2);
    ck_assert_int_eq(*(int *)res->next->next->data, 3);
    ck_assert_int_eq(*(int *)res->next->next->next->data, 4);
    ck_assert_ptr_null(a);
    ck_assert_ptr_null(b);

    unit_free_list(res);
}
END_TEST

START_TEST(test_sort_empty_list)
{
    node_t *res = sort(NULL, compare_int);

    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_sort_single_node)
{
    int data4 = 4;
    int *ptr4 = &data4;

    node_t *head = unit_create_node(ptr4);
    node_t *res = sort(head, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 4);
    ck_assert_ptr_null(res->next);

    unit_free_list(res);
}
END_TEST

START_TEST(test_sort_unsorted_list)
{
    int data1 = 1;
    int *ptr1 = &data1;

    int data2 = 2;
    int *ptr2 = &data2;

    int data3 = 3;
    int *ptr3 = &data3;

    node_t *head = unit_create_node(ptr1);
    head->next = unit_create_node(ptr2);
    head->next->next = unit_create_node(ptr3);

    node_t *res = sort(head, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 1);
    ck_assert_int_eq(*(int *)res->next->data, 2);
    ck_assert_int_eq(*(int *)res->next->next->data, 3);

    unit_free_list(res);
}
END_TEST

Suite *list_suite(void)
{
    Suite *s;
    TCase *tc_pos, *tc_neg;

    s = suite_create("list");
    tc_pos = tcase_create("positive");

    tcase_add_test(tc_pos, test_create_node_ok);
    tcase_add_test(tc_pos, test_free_list_single_node);
    tcase_add_test(tc_pos, test_free_list_multiple_nodes);
    tcase_add_test(tc_pos, test_reverse_single_node);
    tcase_add_test(tc_pos, test_reverse_multiple_nodes);
    tcase_add_test(tc_pos, test_front_back_split_single_node);
    tcase_add_test(tc_pos, test_front_back_split_two_nodes);
    tcase_add_test(tc_pos, test_front_back_split_three_nodes);
    tcase_add_test(tc_pos, test_sorted_merge_sorted_lists);
    tcase_add_test(tc_pos, test_sort_single_node);
    tcase_add_test(tc_pos, test_sort_unsorted_list);
    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negative");

    tcase_add_test(tc_neg, test_free_list_null);
    tcase_add_test(tc_neg, test_reverse_empty_list);
    tcase_add_test(tc_neg, test_front_back_split_empty);
    tcase_add_test(tc_neg, test_sorted_merge_both_empty);
    tcase_add_test(tc_neg, test_sorted_merge_first_empty);
    tcase_add_test(tc_neg, test_sorted_merge_second_empty);
    tcase_add_test(tc_neg, test_sort_empty_list);
    tcase_add_test(tc_neg, test_create_node_null_data);
    suite_add_tcase(s, tc_neg);

    return s;
}
