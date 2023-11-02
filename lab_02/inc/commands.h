#ifndef __COM_H__
#define __COM_H__

#include "../inc/consts.h"
#include <string.h>

void print_tutorial();
void print_book(abonent_book book, int n);
void print_one_abonent(struct abonent person);
void add_line(abonent_book book, int n);
int delete_line(abonent_book book, int n);


#endif
