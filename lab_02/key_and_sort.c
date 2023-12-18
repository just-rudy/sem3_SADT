#include "key_and_sort.h"
void swap_key(struct key_s *p1, struct key_s *p2);
void swap_db(struct abonent_t *p1, struct abonent_t *p2);

// меняем запись
void swap_key(struct key_s *p1, struct key_s *p2)
{
    struct key_s tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

void swap_db(struct abonent_t *p1, struct abonent_t *p2)
{
    struct abonent_t tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

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

// сортируем ключи
void bubble_sort_k(key_table_arr key_table, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (strcmp(key_table[i].name, key_table[j].name) > 0)
                swap_key(&key_table[i], &key_table[j]);
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
        swap_key(&key_table[min_idx], &key_table[i]);
    }
}

// для самой типа бд
void bubble_sort_db(abonent_t_book book, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (strcmp(book[i].name, book[j].name) > 0)
                swap_db(&book[i], &book[j]);
        }
    }
}

void choice_sort_db(abonent_t_book book, int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(book[j].name, book[min_idx].name) < 0)
                min_idx = j;
        }
        swap_db(&book[min_idx], &book[i]);
    }
}
