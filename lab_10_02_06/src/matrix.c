#include "matrix.h"

int get_value(void *data)
{
    return ((elem_t *)data)->value;
}

size_t get_i(void *data)
{
    return ((elem_t *)data)->i;
}

size_t get_j(void *data)
{
    return ((elem_t *)data)->j;
}

void free_matrix(node_t *matrix)
{
    if (!matrix)
        return;

    node_t *next;

    while (matrix)
    {
        next = matrix->next;
        free(matrix->data);
        matrix = next;
    }
}

node_t *input_matrix(FILE *f)
{
    int row, col;

    if (fscanf(f, "%d%d", &row, &col) != 2)
        return NULL;

    if (row <= 0 || col <= 0)
        return NULL;

    int value = 0;
    node_t *head = NULL;

    for (size_t i = 0; i < row; i++)
        for (size_t j = 0; j < col; j++)
        {
            if (fscanf(f, "%d", &value) != 1)
            {
                free_matrix(head);
                free_list(head);
                return NULL;
            }

            if (value)
            {
                elem_t *elem = malloc(sizeof(elem_t));

                if (!elem)
                {
                    free_matrix(head);
                    free_list(head);
                    return NULL;
                }

                elem->i = i;
                elem->j = j;
                elem->value = value;

                node_t *node = create_node(elem);

                if (!node)
                {
                    free_matrix(head);
                    free_list(head);
                    return NULL;
                }

                node->next = head;
                head = node;
            }
        }

    return reverse(head);
}

void print_elem(elem_t *elem, FILE *f)
{
    fprintf(f, "%zu %zu %d ", elem->i, elem->j, elem->value);
}

void print_matrix(node_t *head, FILE *f)
{
    for (; head; head = head->next)
        print_elem(head->data, f);
    printf("\n");
}

node_t *add_matrix(node_t *head1, node_t *head2)
{
    if (!head1 && !head2)
        return NULL;

    node_t *head_res = NULL;
    node_t *cur1 = head1;
    node_t *cur2 = head2;

    elem_t *data1 = NULL;
    elem_t *data2 = NULL;

    while (cur1 || cur2)
    {
        data1 = cur1 ? cur1->data : NULL;
        data2 = cur2 ? cur2->data : NULL;

        elem_t *node_data = malloc(sizeof(elem_t));

        if (!node_data)
        {
            free_matrix(head_res);
            free_list(head_res);
            return NULL;
        }

        if (!data2 || (data1 && (data1->i < data2->i || (data1->i == data2->i && data1->j < data2->j))))
        {
            node_data->i = data1->i;
            node_data->j = data1->j;
            node_data->value = data1->value;

            cur1 = cur1->next;
        }
        else if (!data1 || (data2 && (data1->i > data2->i || (data1->i == data2->i && data1->j > data2->j))))
        {
            node_data->i = data2->i;
            node_data->j = data2->j;
            node_data->value = data2->value;

            cur2 = cur2->next;
        }
        else
        {
            node_data->i = data1->i;
            node_data->j = data1->j;
            node_data->value = data1->value + data2->value;

            cur1 = cur1->next;
            cur2 = cur2->next;

            if (!node_data->value)
            {
                free(node_data);
                continue;
            }
        }

        node_t *node = create_node(node_data);

        if (!node)
        {
            free_matrix(head_res);
            free_list(head_res);
            return NULL;
        }

        node->next = head_res;
        head_res = node;
    }

    return reverse(head_res);
}

int compare_elem(const void *a, const void *b)
{
    const elem_t *elem1 = a;
    const elem_t *elem2 = b;

    if (elem1->i > elem2->i || (elem1->i == elem2->i && elem1->j > elem2->j))
        return 1;
    else if (elem1->i < elem2->i || (elem1->i == elem2->i && elem1->j < elem2->j))
        return -1;
    else
        return 0;
}

node_t *transpose_matrix(node_t *head)
{
    if (!head)
        return NULL;

    node_t *new_head = NULL;

    while (head)
    {
        elem_t *elem = malloc(sizeof(elem_t));

        if (!elem)
        {
            free_matrix(new_head);
            free_list(new_head);
            return NULL;
        }

        elem->i = get_j(head->data);
        elem->j = get_i(head->data);
        elem->value = get_value(head->data);

        node_t *node = create_node(elem);

        if (!node)
        {
            free(elem);
            free_matrix(new_head);
            free_list(new_head);

            return NULL;
        }

        node->next = new_head;
        new_head = node;

        head = head->next;
    }

    return sort(new_head, compare_elem);
}

node_t *mul_matrix(node_t *head1, node_t *head2)
{
    if (!head1 || !head2)
        return NULL;

    node_t *head2_transpose = transpose_matrix(head2);

    if (!head2_transpose)
        return NULL;

    node_t *cur1 = head1;
    node_t *cur2 = head2_transpose;

    node_t *res_head = NULL;
    node_t *cur_res = NULL;

    elem_t *data_res = NULL;
    elem_t *data1 = NULL;
    elem_t *data2 = NULL;

    while (cur1)
    {
        data1 = cur1->data;
        cur2 = head2_transpose;

        while (cur2)
        {
            data2 = cur2->data;

            if (data1->j == data2->j)
            {
                cur_res = res_head;

                while (cur_res)
                {
                    data_res = cur_res->data;

                    if (data_res->i == data1->i && data_res->j == data2->i)
                    {
                        data_res->value += data1->value * data2->value;
                        break;
                    }

                    cur_res = cur_res->next;
                }

                if (!cur_res)
                {
                    elem_t *elem = malloc(sizeof(elem_t));

                    if (!elem)
                    {
                        free_matrix(res_head);
                        free_list(res_head);
                        free_matrix(head2_transpose);
                        free_list(head2_transpose);
                        return NULL;
                    }

                    elem->i = data1->i;
                    elem->j = data2->i;
                    elem->value = data1->value * data2->value;

                    node_t *node = create_node(elem);

                    if (!node)
                    {
                        free(elem);
                        free_matrix(res_head);
                        free_list(res_head);
                        free_matrix(head2_transpose);
                        free_list(head2_transpose);
                        return NULL;
                    }

                    node->next = res_head;
                    res_head = node;
                }
            }

            cur2 = cur2->next;
        }

        cur1 = cur1->next;
    }

    free_matrix(head2_transpose);
    free_list(head2_transpose);
    res_head = sort(res_head, compare_elem);

    cur_res = res_head;
    node_t *last = NULL;

    while (cur_res)
    {
        data_res = cur_res->data;

        if (!data_res->value)
        {
            node_t *node = cur_res;

            if (last)
            {
                last->next = cur_res->next;
                cur_res = cur_res->next;
            }
            else
            {
                res_head = cur_res->next;
                cur_res = res_head;
            }

            free(node);
        }
        else
        {
            last = cur_res;
            cur_res = cur_res->next;
        }
    }

    return res_head;
}

node_t *lin_matrix(node_t *head)
{
    if (!head)
        return NULL;

    node_t *head_cur = head;
    int max_el = get_value(head->data);
    size_t row_max_el = get_i(head->data);

    while (head_cur)
    {
        if (get_value(head_cur->data) > max_el)
        {
            max_el = get_value(head_cur->data);
            row_max_el = get_i(head_cur->data);
        }

        head_cur = head_cur->next;
    }

    head_cur = head;
    node_t *last = NULL;
    node_t *tmp = NULL;

    while (head_cur)
    {
        if (get_i(head_cur->data) == row_max_el)
        {
            tmp = head_cur;

            if (last)
            {
                last->next = head_cur->next;
                head_cur = head_cur->next;
            }
            else
            {
                head = head_cur->next;
                head_cur = head;
            }

            free(tmp->data);
            free(tmp);
        }
        else
        {
            last = head_cur;
            head_cur = head_cur->next;
        }
    }

    return head;
}
