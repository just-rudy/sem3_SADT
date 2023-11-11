#ifndef __ARR_H__
#define __ARR_H__

#define N 100
#define TOO_MUCH 1
#define EMPTY 2
#define OK 0

int push_array(char **p_cur, char *p_end, char c);
int pop_array(char **cur, char *beg, char *value);
int print_array(char *beg, char *cur);

#endif