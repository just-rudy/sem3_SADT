#include "time_measure.h"
#include <time.h>
#include <stdlib.h>

long long int time_now(void);

long long int time_now(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    long long int res = t.tv_sec * 1000000 + t.tv_usec;
    return res;
}

void time_measure(void)
{
    long long int time_cur = 0;
    long long int time_add_a = 0, time_pop_a = 0;
    long long int time_add_s = 0, time_pop_s = 0;

    char c;
    // замерить добавление 1000 элементов
    for (int j = 0; j < 100; j++)
    {
        char arr_s[1000];
        char *arr_c = arr_s - 1;
        struct node_s *list = NULL;
        for (int i = 0; i < 1000; i++)
        {
            c = 'A' + rand() % 26; // случайный символ от А до Z
            
            time_cur = time_now();
            list = push_stack(list, c);
            time_cur = time_now() - time_cur;
            time_add_s += time_cur;

            time_cur = time_now();
            push_array(&arr_c, arr_s + 1000 - 1, c);
            time_cur = time_now() - time_cur;
            time_add_a += time_cur;
        }

        for (int i = 0; i < 1000; i ++)
        {
            char tmp;
            time_cur = time_now();
            list = pop_stack(list, &tmp, NULL, NULL);
            time_cur = time_now() - time_cur;
            time_pop_s += time_cur;

            time_cur = time_now();
            int rc = pop_array(&arr_c, arr_s, &c);
            time_cur = time_now() - time_cur;
            time_pop_a += time_cur;
        }

    }
    
    printf("Время добавления 1000 элементов\n\tна стеке: %lf мс\n\tна массиве: %lf мс\n", (double)time_add_s/100, (double)time_add_a/100);
    printf("Время удаления 1000 элементов\n\tна стеке: %lf мс\n\tна массиве: %lf мс\n", (double)time_pop_s/100, (double)time_pop_a/100);
    printf("Память в б:\n|   N| массив| список|\n");
    int size[5] = {10, 50, 100, 500, 1000};
    for (int i = 0; i < 5; i++)
    {
        int mem_a = sizeof(int) * size[i];
        int mem_s = sizeof(struct node_s) * size[i];
        printf("|%4d|%7d|%7d|\n", size[i], mem_a, mem_s);
    }
    // замерить удаление 1000 элементов


}