#include <stdlib.h>

#include "errors.h"
#include "list.h"

node_t *create_node(void *data)
{
    if (!data)
        return NULL;

    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

void free_list(node_t *head)
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

node_t *reverse(node_t *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *new_head = reverse(head->next);
    head->next->next = head;
    head->next = NULL;

    return new_head;
}

void front_back_split(node_t *head, node_t **back)
{
    if (head == NULL || head->next == NULL)
    {
        *back = NULL;
        return;
    }

    size_t count = 0;

    for (node_t *cur = head; cur; count++, cur = cur->next);

    node_t *cur = head;
    for (int i = 0; i < (count - 1) / 2; i++)
        cur = cur->next;

    *back = cur->next;
    cur->next = NULL;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*comparator)(const void *, const void *))
{
    node_t head = { .data = NULL, .next = NULL };

    node_t *cur_res = &head;

    node_t *cur_a = *head_a;
    node_t *cur_b = *head_b;

    while (cur_a && cur_b)
    {
        if (comparator(cur_a->data, cur_b->data) <= 0)
        {
            cur_res->next = cur_a;
            cur_a = cur_a->next;
        }
        else
        {
            cur_res->next = cur_b;
            cur_b = cur_b->next;
        }

        cur_res = cur_res->next;
    }

    if (cur_a)
        cur_res->next = cur_a;
    else
        cur_res->next = cur_b;

    *head_a = NULL;
    *head_b = NULL;

    return head.next;
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    if (head == NULL || head->next == NULL)
        return head;

    node_t *back = NULL;

    front_back_split(head, &back);
    head = sort(head, comparator);
    back = sort(back, comparator);

    head = sorted_merge(&head, &back, comparator);
    return head;
}
