#ifndef __COM_H__
#define __COM_H__

#include "consts.h"
#include <string.h>

void print_tutorial();
void print_book(abonent_t_book book, int n);
void print_one_abonent_t(struct abonent_t person);
void add_line(abonent_t_book book, int n);
int delete_line(abonent_t_book book, int n);


#endif
