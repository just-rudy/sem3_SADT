#include "stack.h"

#define TRUE 1
#define FALSE 0

struct node_s *str_to_stack(char str[N], int cnt)
{
    struct node_s *tmp = NULL;
    for (int i = 0; i < cnt; i++)
        push_stack(tmp, str[i]);
    return tmp;
}

struct node_s *push_stack(struct node_s *last, char c)
{
    struct node_s *tmp = malloc(sizeof(struct node_s));
    tmp->value = c;
    tmp->prev = last;

    return tmp;
}


struct node_s *pop_stack(struct node_s *last, char *c, struct node_s **free_spaces, int *cnt)
{
    if (last == NULL)
        return NULL;

    struct node_s *tmp = last->prev;
    *c = last->value;

    if (free_spaces != NULL)
        if (*cnt < N_FREE)
            free_spaces[(*cnt)++] = last;
        else
            printf("free_arr is full\n");

    free(last);
    return tmp;
}

void print_stack(struct node_s *last, struct node_s **free_spaces, int cnt)
{
    if (!last)
        printf("empty\n");

    printf("stack:\n");
    for (; last != NULL;)
    {
        printf("{%p} %c\n", last, last->value);
        last = last->prev;
    }

    printf("\nfree spaces:\n");
    if (cnt == 0)
        printf("no freed spaces yet\n");
    for (int i = 0; i < cnt; i++)
        printf("%p\n", free_spaces[i]);
    printf("\n");
}

int check_stack(struct node_s *last, int cnt)
{
    int res = TRUE;
    // if (!last)
    //     printf("empty\n");

    char *tmp = malloc(cnt / 2 * sizeof(char));
    int i = 0;
    for (; last != NULL && i < cnt / 2;)
    {
        tmp[i++] = last->value;
        last = last->prev;
    }
    if (cnt % 2 != 0)
        last = last->prev;

    for (; last != NULL && res;)
    {
        if (tmp[--i] != last->value)
            res = FALSE;
        last = last->prev;
    }
    free(tmp);
    return res;
}