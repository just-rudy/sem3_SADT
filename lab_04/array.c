#include <stdio.h>
#include "array.h"

int push_array(char **cur, char *end, char c)
{
    if (*cur > end)
        return TOO_MUCH;
    (*cur)++;
    **cur = c;
    return OK;
}

int pop_array(char **cur, char *beg, char *value)
{
    if (*cur < beg)
        return EMPTY;

    (*value) = (**cur);
    (*cur)--;
    return OK;
}

int print_array(char *beg, char *cur)
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