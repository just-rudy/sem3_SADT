#include "array.h"

#define TRUE 1
#define FALSE 0

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

int check_array(char *beg, char *cur, int cnt)
{
    int res = TRUE;
    int i = 0;

    char *tmp = malloc(cnt / 2 * sizeof(char));

    for (; beg <= cur && i < cnt / 2; beg++)
        tmp[i++] = (*beg);

    if (cnt % 2 != 0)
        beg++;

    for (; beg <= cur && res; beg++)
        if (tmp[--i] != (*beg))
            res = FALSE;

    free(tmp);
    return res;
}