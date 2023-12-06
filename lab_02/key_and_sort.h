
#ifndef __KEYSORT_H__
#define __KEYSORT_H__

#include "consts.h"

void print_key_table(struct key_s *table, int n);
void choice_sort_k(key_table_arr key_table, int n);
void use_key(abonent_t_book book, key_table_arr key_tbl, int n);
void bubble_sort_k(key_table_arr key_table, int n);

#endif