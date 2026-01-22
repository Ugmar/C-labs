#include <stdlib.h>
#include <string.h>

#include "assoc_node.h"
#include "associative_array.h"

#define INIT_SIZE 16
#define STEP_EXPAND 2

struct assoc_array_type
{
    node_t **data;
    size_t len;
    size_t cap;
};

typedef int (*compare_t)(const void *, const void *);

size_t binary_search(void *base, const void *cur, void *end, size_t size, compare_t compare)
{
    char *arr = base;

    if (base == end)
        return 0;

    size_t l = 0;
    size_t r = ((char *)end - arr) / size;
    size_t m = 0;

    while (l < r)
    {
        m = l + (r - l) / 2;

        if (compare(cur, arr + m * size) > 0)
            l = m + 1;
        else if (compare(cur, arr + m * size) < 0)
            r = m;
        else
            return m;
    }

    return l;
}

assoc_array_t assoc_array_create(void)
{
    struct assoc_array_type *arr = malloc(sizeof(struct assoc_array_type));

    if (!arr)
        return NULL;

    arr->data = malloc(INIT_SIZE * sizeof(node_t *));

    if (!arr->data)
    {
        free(arr);
        return NULL;
    }

    arr->cap = INIT_SIZE;
    arr->len = 0;

    return arr;
}

void assoc_array_destroy(assoc_array_t *arr)
{
    if (!arr || !*arr)
        return;

    struct assoc_array_type *info = *arr;

    for (size_t i = 0; i < info->len; i++)
        if (info->data[i])
            free_node(info->data[i]);

    free(info->data);
    free(info);
    *arr = NULL;
}

assoc_array_error_t assoc_array_insert(assoc_array_t arr, const char *key, int num)
{
    if (!key || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    size_t index = binary_search(arr->data, key, arr->data + arr->len, sizeof(node_t *), compare_node);

    if (arr->len && index < arr->len && arr->data[index] && strcmp(arr->data[index]->key, key) == 0)
        return ASSOC_ARRAY_KEY_EXISTS;

    if (arr->len + 1 > arr->cap)
    {
        node_t **tmp = arr->data;
        tmp = realloc(arr->data, sizeof(node_t *) * arr->cap * STEP_EXPAND);

        if (!tmp)
            return ASSOC_ARRAY_MEM;

        arr->data = tmp;
        arr->cap *= STEP_EXPAND;
    }

    node_t *node = create_node(key, num);

    if (!node)
        return ASSOC_ARRAY_MEM;

    if (index < arr->len)
        memmove(&arr->data[index + 1], &arr->data[index], sizeof(node_t *) * (arr->len - index));

    arr->data[index] = node;
    arr->len++;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_find(const assoc_array_t arr, const char *key, int **num)
{
    if (!key || !num || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->len)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t index = binary_search(arr->data, key, arr->data + arr->len, sizeof(node_t *), compare_node);

    if (index >= arr->len || strcmp(arr->data[index]->key, key) != 0)
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->data[index]->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_remove(assoc_array_t arr, const char *key)
{
    if (!key || !arr || !strlen(key))
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->len)
        return ASSOC_ARRAY_NOT_FOUND;

    size_t index = binary_search(arr->data, key, arr->data + arr->len, sizeof(node_t *), compare_node);

    if (index >= arr->len || strcmp(arr->data[index]->key, key) != 0)
        return ASSOC_ARRAY_NOT_FOUND;

    free_node(arr->data[index]);

    if (arr->len - 1 > index)
        memmove(&arr->data[index], &arr->data[index + 1], sizeof(node_t *) * (arr->len - index - 1));

    arr->len--;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_clear(assoc_array_t arr)
{
    if (!arr)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
    {
        if (arr->data[i])
        {
            free_node(arr->data[i]);
            arr->data[i] = NULL;
        }
    }

    arr->len = 0;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_each(const assoc_array_t arr, void (*action)(const char *key, int *num, void *param), void *param)
{
    if (!arr || !action)
        return ASSOC_ARRAY_INVALID_PARAM;

    for (size_t i = 0; i < arr->len; i++)
    {
        if (arr->data[i])
            action(arr->data[i]->key, &arr->data[i]->value, param);
    }

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_min(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->len || !arr->data[0])
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->data[0]->value;

    return ASSOC_ARRAY_OK;
}

assoc_array_error_t assoc_array_max(const assoc_array_t arr, int **num)
{
    if (!arr || !num)
        return ASSOC_ARRAY_INVALID_PARAM;

    if (!arr->len || !arr->data[arr->len - 1])
        return ASSOC_ARRAY_NOT_FOUND;

    *num = &arr->data[arr->len - 1]->value;

    return ASSOC_ARRAY_OK;
}
