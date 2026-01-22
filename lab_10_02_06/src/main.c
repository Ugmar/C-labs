#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "list.h"
#include "matrix.h"

#define LEN_ACTION 3

int main(void)
{
    char action[LEN_ACTION + 2];
    int rc = OK;

    if (!fgets(action, sizeof(action), stdin))
        return ERROR_EMPTY_ACTION;

    if (action[strlen(action) - 1] == '\n')
        action[strlen(action) - 1] = '\0';

    if (strlen(action) > LEN_ACTION)
        return ERROR_UNDEFINE_ACTION;

    node_t *head1 = NULL, *head2 = NULL, *head_res = NULL;
    if (strncmp(action, "out", LEN_ACTION) == 0)
    {
        head1 = input_matrix(stdin);
        if (head1)
            print_matrix(head1, stdout);
        else
            rc = ERROR_INPUT;
    }
    else if (strncmp(action, "add", LEN_ACTION) == 0)
    {
        head1 = input_matrix(stdin);
        if (head1)
        {
            head2 = input_matrix(stdin);

            if (head2)
            {
                head_res = add_matrix(head1, head2);

                if (!head_res)
                    rc = ERROR_MEMORY;
                else
                    print_matrix(head_res, stdout);
            }
            else
                rc = ERROR_INPUT;
        }
        else
            rc = ERROR_INPUT;
    }
    else if (strncmp(action, "mul", LEN_ACTION) == 0)
    {
        head1 = input_matrix(stdin);

        if (head1)
        {
            head2 = input_matrix(stdin);

            if (head2)
            {
                head_res = mul_matrix(head1, head2);

                if (!head_res)
                    rc = ERROR_MEMORY;
                else
                    print_matrix(head_res, stdout);
            }
            else
                rc = ERROR_INPUT;
        }
        else
            rc = ERROR_INPUT;
    }
    else if (strncmp(action, "lin", LEN_ACTION) == 0)
    {
        head1 = input_matrix(stdin);

        if (head1)
        {
            head1 = lin_matrix(head1);
            print_matrix(head1, stdout);
        }
        else
            rc = ERROR_INPUT;
    }
    else
        rc = ERROR_UNDEFINE_ACTION;


    free_matrix(head1);
    free_matrix(head2);
    free_matrix(head_res);

    free_list(head1);
    free_list(head2);
    free_list(head_res);

    return rc;
}
