#include "key_and_sort.h"

// ключ - фамилия

// создает таблицу ключей
void use_key(abonent_t_book book, key_table_arr key_tbl, int n)
{
    for (int i = 0; i < n; i++)
    {
        key_tbl[i].idx = i;
        strcpy(book[i].name, key_tbl[i].name);
        printf("key: %d - %s\n", key_tbl[i].idx, key_tbl[i].name);
        printf("key: %d - %s\n", i, book[i].name);
    }
}

// вывод таблицы ключей

void print_key_table(key_table_arr tbl, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("{%d} - %s\n", tbl[i].idx, tbl[i].name);
    }
}

// сортирует таблицу ключей  по фамилии
// пузырек

void swap(struct key_s *a, struct key_s *b)
{
    struct key_s *tmp = a;
    a = b;
    b = tmp;
}

void bubble_sort_k(key_table_arr key_table, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            if (strcmp(key_table[i].name, key_table[j].name) < 0)
                swap(&key_table[i], &key_table[j]);
        }
    }
}


//выбор

void choice_sort_k(key_table_arr key_table, int n)
{
    int i = 0;
    while (i < n)
    {
        struct key_s mx;
        mx.idx = key_table[0].idx;
        strcpy(mx.name, key_table[0].name);

        for (int j = 0; j < n-i; j++)
            if (strcmp(mx.name, key_table[i].name) > 0)
                swap(&mx, &key_table[i]);
        i++;
    }
}


//void choice_sort_k(struct key_s *key_table, int n)
//{
//    struct key_s *arr_b = key_table;
//    struct key_s *arr_end = arr_b + n * sizeof(struct key_s);
//
//    for (size_t i = 0; i < n; i++)
//    {
//        struct key_s *mx = arr_b;
//        for (struct key_s *cur = arr_b; cur != arr_end; cur++)
//            if (strcmp(cur->name, mx->name) < 0)
//                swap(&cur, &mx);
//        arr_end--;
//        swap(&mx, &arr_end);
//    }
//}
