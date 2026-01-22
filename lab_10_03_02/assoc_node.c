#include <stdlib.h>
#include <string.h>

#include "assoc_node.h"

node_t *create_node(const char *key, int value)
{
    if (!key)
        return NULL;

    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;

    node->key = malloc(strlen(key) + 1);

    if (!node->key)
    {
        free(node);
        return NULL;
    }

    strcpy(node->key, key);
    node->value = value;
    node->next = NULL;

    return node;
}

void free_node(node_t *node)
{
    if (node)
    {
        if (node->key)
            free(node->key);
        free(node);
    }
}
