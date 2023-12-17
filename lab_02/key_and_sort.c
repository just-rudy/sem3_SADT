#include "key_and_sort.h"
void use_key(abonent_t_book book, key_table_arr key_tbl, int n);
void swap_key(struct key_s *a, struct key_s *b);
void swap(struct key_s *xp, struct key_s *yp);

// создает таблицу ключей
void use_key(abonent_t_book book, key_table_arr key_tbl, int n)
{
    for (int i = 0; i < n; i++)
    {
        key_tbl[i].idx = i;
        strcpy(key_tbl[i].name, book[i].name);
    }
}

// вывод таблицы ключей

void print_key_table(key_table_arr tbl, int n)
{
    for (int i = 0; i < n; i++)
        printf("{%d} - %s\n", tbl[i].idx, tbl[i].name);
}

// сортирует таблицу ключей по имени
// пузырек

void swap_key(struct key_s *a, struct key_s *b)
{
    struct key_s tmp;
    tmp.idx = a->idx;
    strcpy(tmp.name, a->name);

    a->idx = b->idx;
    strcpy(a->name, b->name);

    b->idx = tmp.idx;
    strcpy(b->name, tmp.name);
}

// выбор
void swap(struct key_s *xp, struct key_s *yp)
{
    struct key_s temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort_k(key_table_arr key_table, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (strcmp(key_table[i].name, key_table[j].name) > 0)
                swap(&key_table[i], &key_table[j]);
        }
    }
}

void choice_sort_k(key_table_arr key_table, int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(key_table[j].name, key_table[min_idx].name) < 0)
                min_idx = j;
        }
        swap(&key_table[min_idx], &key_table[i]);
    }
}
