#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define TOO_MUCH 1
#define EMPTY 2

struct node_s
{
    char value;
    struct node_s *prev;
};

#endif