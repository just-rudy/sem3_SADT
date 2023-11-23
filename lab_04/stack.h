#ifndef __STACK_H__
#define __STACK_H__

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define N 1000
#define N_FREE 2000

struct node_s
{
    char value;
    struct node_s *prev;
};

struct node_s *push_stack(struct node_s *last, char c);
struct node_s *pop_stack(struct node_s *last, char *c, struct node_s **free_spaces, int *cnt);
void print_stack(struct node_s *last, struct node_s **free_spaces, int cnt);
int check_stack(struct node_s *last, int cnt);
void free_list(struct node_s *node);
// struct node_s *str_to_stack(char str[N], int cnt);

#endif