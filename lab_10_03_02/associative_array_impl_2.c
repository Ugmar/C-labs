#include <stdlib.h>
#include <string.h>

#include "assoc_node.h"
#include "associative_array.h"

struct assoc_array_type
{
    node_t *head;
    size_t size;
};

assoc_array_t assoc_array_create(void)
{
    struct assoc_array_type *arr = malloc(sizeof(struct assoc_array_type));

    if (!arr)
        return NULL;

    arr->head = NULL;
    arr->size = 0;

    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !*arr)
        return;

    node_t *current = (*arr)->head;

    while (current)
    {
        node_t *next = current->next;
        free_node(current);
        current = next;
    }

    free(*arr);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!key || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
            return ASSOC_ARRAY_KEY_EXISTS;

        current = current->next;
    }

    node_t *node = create_node(key, num);

    if (!node)
        return ASSOC_ARRAY_MEM;

    node->next = arr->head;
    arr->head = node;
    arr->size++;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!key || !num || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            *num = &current->value;

            return ASSOC_ARRAY_OK;
        }

        current = current->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!key || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;
    node_t *last = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (last)
                last->next = current->next;
            else
                arr->head = current->next;

            free_node(current);
            arr->size--;

            return ASSOC_ARRAY_OK;
        }

        last = current;
        current = current->next;
    }

    return ASSOC_ARRAY_NOT_FOUND;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;

    while (current)
    {
        node_t *next = current->next;
        free_node(current);
        current = next;
    }

    arr->head = NULL;
    arr->size = 0;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    node_t *current = arr->head;

    while (current)
    {
        action(current->key, &current->value, param);
        current = current->next;
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *current = arr->head;
    node_t *min_node = current;

    while (current)
    {
        if (strcmp(current->key, min_node->key) < 0)
            min_node = current;

        current = current->next;
    }

    *num = &min_node->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->head)
        return ASSOC_ARRAY_NOT_FOUND;

    node_t *current = arr->head;
    node_t *max_node = current;

    while (current)
    {
        if (strcmp(current->key, max_node->key) > 0)
            max_node = current;

        current = current->next;
    }

    *num = &max_node->value;

    return ASSOC_ARRAY_OK;
}
