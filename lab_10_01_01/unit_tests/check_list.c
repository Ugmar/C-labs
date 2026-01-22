#include <check.h>
#include <stdlib.h>

#include "list.h"

static node_t *unit_create_node(void *data)
{
    node_t *node = malloc(sizeof(node_t));
    if (node)
    {
        node->data = data;
        node->next = NULL;
    }

    return node;
}

static void unit_free_node(node_t *node)
{
    free(node);
}

static void unit_free_list(node_t *head)
{
    if (!head)
        return;

    node_t *next;

    while (head)
    {
        next = head->next;
        free(head);
        head = next;
    }
}

static int compare_int(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

START_TEST(test_create_node_ok)
{
    int data = 52;
    int *ptr = &data;

    node_t *node = create_node(ptr);

    ck_assert_ptr_nonnull(node);
    ck_assert_ptr_eq(node->data, ptr);
    ck_assert_ptr_null(node->next);

    free(node);
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

START_TEST(test_find_null_parameters)
{
    node_t *res = find(NULL, NULL, NULL);
    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_find_empty_list)
{
    int target = 42;
    node_t *res = find(NULL, &target, compare_int);
    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(test_find_existing_element)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);
    head->next->next = unit_create_node(&data3);

    int data_search = 2;
    node_t *res = find(head, &data_search, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 2);
    ck_assert_ptr_eq(res, head->next);

    unit_free_list(head);
}
END_TEST

START_TEST(test_find_first_element)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);
    head->next->next = unit_create_node(&data3);

    int data_search = 1;
    node_t *res = find(head, &data_search, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 1);
    ck_assert_ptr_eq(res, head);

    unit_free_list(head);
}
END_TEST

START_TEST(test_find_last_element)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);
    head->next->next = unit_create_node(&data3);

    int data_search = 3;
    node_t *res = find(head, &data_search, compare_int);

    ck_assert_ptr_nonnull(res);
    ck_assert_int_eq(*(int *)res->data, 3);
    ck_assert_ptr_eq(res, head->next->next);

    unit_free_list(head);
}
END_TEST

START_TEST(test_find_non_existing_element)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);
    head->next->next = unit_create_node(&data3);

    int data_search = 42;
    node_t *res = find(head, &data_search, compare_int);

    ck_assert_ptr_null(res);

    unit_free_list(head);
}
END_TEST

START_TEST(test_find_with_null_comparator)
{
    int data1 = 1;
    node_t *head = unit_create_node(&data1);

    int data_search = 1;
    node_t *res = find(head, &data_search, NULL);

    ck_assert_ptr_null(res);

    unit_free_list(head);
}
END_TEST

START_TEST(test_find_with_null_data)
{
    int data1 = 1;
    node_t *head = unit_create_node(&data1);

    node_t *res = find(head, NULL, compare_int);

    ck_assert_ptr_null(res);

    unit_free_list(head);
}
END_TEST

START_TEST(test_insert_in_beginning)
{
    int data1 = 1;
    int data2 = 2;
    int new_data = 0;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);

    node_t *new_node = unit_create_node(&new_data);

    insert(&head, new_node, head);

    ck_assert_ptr_eq(head, new_node);
    ck_assert_ptr_eq(new_node->next, head->next);
    ck_assert_int_eq(*(int *)head->data, 0);
    ck_assert_int_eq(*(int *)head->next->data, 1);
    ck_assert_int_eq(*(int *)head->next->next->data, 2);

    unit_free_list(head);
}
END_TEST

START_TEST(test_insert_in_middle)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int new_data = 100;

    node_t *head = unit_create_node(&data1);
    node_t *second = unit_create_node(&data2);
    node_t *third = unit_create_node(&data3);

    head->next = second;
    second->next = third;

    node_t *new_node = unit_create_node(&new_data);

    insert(&head, new_node, second);

    ck_assert_ptr_eq(head->next, new_node);
    ck_assert_ptr_eq(new_node->next, second);
    ck_assert_int_eq(*(int *)head->data, 1);
    ck_assert_int_eq(*(int *)new_node->data, 100);
    ck_assert_int_eq(*(int *)second->data, 2);
    ck_assert_int_eq(*(int *)third->data, 3);

    unit_free_list(head);
}
END_TEST

START_TEST(test_insert_before_last)
{
    int data1 = 1;
    int data2 = 2;
    int data3 = 3;
    int new_data = 52;

    node_t *head = unit_create_node(&data1);
    node_t *second = unit_create_node(&data2);
    node_t *third = unit_create_node(&data3);

    head->next = second;
    second->next = third;

    node_t *new_node = unit_create_node(&new_data);

    insert(&head, new_node, third);

    ck_assert_ptr_eq(second->next, new_node);
    ck_assert_ptr_eq(new_node->next, third);
    ck_assert_int_eq(*(int *)head->data, 1);
    ck_assert_int_eq(*(int *)second->data, 2);
    ck_assert_int_eq(*(int *)new_node->data, 52);
    ck_assert_int_eq(*(int *)third->data, 3);

    unit_free_list(head);
}
END_TEST

START_TEST(test_insert_into_empty_list)
{
    int new_data = 1;
    node_t *head = NULL;
    node_t *new_node = unit_create_node(&new_data);

    insert(&head, new_node, NULL);

    ck_assert_ptr_null(head);

    unit_free_node(new_node);
}
END_TEST

START_TEST(test_insert_with_null_head)
{
    int new_data = 1;
    node_t *new_node = unit_create_node(&new_data);
    node_t *before = unit_create_node(&new_data);

    insert(NULL, new_node, before);

    ck_assert_ptr_nonnull(new_node);
    ck_assert_ptr_nonnull(before);

    unit_free_node(new_node);
    unit_free_node(before);
}
END_TEST

START_TEST(test_insert_with_null_element)
{
    int data1 = 1;
    node_t *head = unit_create_node(&data1);

    insert(&head, NULL, head);

    ck_assert_ptr_nonnull(head);

    unit_free_list(head);
}
END_TEST

START_TEST(test_insert_before_non_existing)
{
    int data1 = 1;
    int data2 = 2;
    int new_data = 52;

    node_t *head = unit_create_node(&data1);
    head->next = unit_create_node(&data2);

    node_t *new_node = unit_create_node(&new_data);
    node_t *non_existing = unit_create_node(&new_data);

    insert(&head, new_node, non_existing);

    ck_assert_int_eq(*(int *)head->data, 1);
    ck_assert_int_eq(*(int *)head->next->data, 2);
    ck_assert_ptr_null(head->next->next);

    unit_free_list(head);
    unit_free_node(new_node);
    unit_free_node(non_existing);
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

    node_t *head = unit_create_node(ptr1);
    node_t *res = reverse(head);

    ck_assert_ptr_eq(res, head);
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

    tcase_add_test(tc_pos, test_insert_before_non_existing);
    tcase_add_test(tc_pos, test_insert_before_last);
    tcase_add_test(tc_pos, test_insert_in_middle);
    tcase_add_test(tc_pos, test_insert_in_beginning);
    tcase_add_test(tc_pos, test_find_last_element);
    tcase_add_test(tc_pos, test_find_first_element);
    tcase_add_test(tc_pos, test_find_existing_element);
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

    tcase_add_test(tc_neg, test_insert_with_null_element);
    tcase_add_test(tc_neg, test_insert_with_null_head);
    tcase_add_test(tc_neg, test_insert_into_empty_list);
    tcase_add_test(tc_neg, test_find_with_null_data);
    tcase_add_test(tc_neg, test_find_with_null_comparator);
    tcase_add_test(tc_neg, test_find_non_existing_element);
    tcase_add_test(tc_neg, test_find_null_parameters);
    tcase_add_test(tc_neg, test_find_empty_list);
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
