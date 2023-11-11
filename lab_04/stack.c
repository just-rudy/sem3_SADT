#include "stack.h"

struct node_s *push_stack(struct node_s *last, char c)
{
    struct node_s *tmp = malloc(sizeof(struct node_s));
    tmp->value = c;
    tmp->prev = last;

    return tmp;
}

struct node_s *pop_stack(char **cur, char *beg, char *value)
{
    if (*cur < beg)
        return EMPTY;

    (*value) = (**cur);
    (*cur)--;
    return OK;
}

struct node_s *print_stack(char *beg, char *cur)
{
    if (beg > cur)
        return EMPTY;

    if (beg == cur)
        printf("empty\n");

    for (; beg <= cur; beg++)
        printf("%c", (*beg));

    printf("\n");
    return OK;
}