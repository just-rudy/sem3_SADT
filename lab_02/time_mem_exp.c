#include "time_mem_exp.h"

long long int time_now(void);

long long int time_now(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    long long int res = t.tv_sec * 1000000 + t.tv_usec;
    return res;
}

void time_measure_exp()
{
    abonent_t_book b1, b2, b3, b4, b5, b6, b7, b8, b9, b0;
    key_table_arr k1, k2, k3, k4, k5, k6, k7, k8, k9, k0; 
    int status = 0;
    
    long long int time_key_bbl = 0, time_key_chs = 0, time_db_bbl = 0, time_db_chs = 0;

    printf("|  n | t_bbl | k_bbl | t_chs | k_chs |\n");
    for (int n = 10; n <= 100; n += 10)
    {
        // пузырек
        status = make_table(b1, n);
        status = make_table(b2, n);
        status = make_table(b3, n);
        status = make_table(b4, n);
        status = make_table(b5, n);
        status = make_table(b6, n);
        status = make_table(b7, n);
        status = make_table(b8, n);
        status = make_table(b9, n);
        status = make_table(b0, n);

        use_key(b0, k0, n);
        use_key(b1, k1, n);
        use_key(b2, k2, n);
        use_key(b3, k3, n);
        use_key(b4, k4, n);
        use_key(b5, k5, n);
        use_key(b6, k6, n);
        use_key(b7, k7, n);
        use_key(b8, k8, n);
        use_key(b9, k9, n);

        // ---------------------------------------
       
        long long int time_c = time_now();

        bubble_sort_db(b1, n);
        bubble_sort_db(b2, n);
        bubble_sort_db(b3, n);
        bubble_sort_db(b4, n);
        bubble_sort_db(b5, n);
        bubble_sort_db(b6, n);
        bubble_sort_db(b7, n);
        bubble_sort_db(b8, n);
        bubble_sort_db(b9, n);
        bubble_sort_db(b0, n);

        time_c = time_now() - time_c;
        time_db_bbl += time_c;

        // -----------------------------------------------------
        time_c = time_now();

        bubble_sort_k(k1, n);
        bubble_sort_k(k2, n);
        bubble_sort_k(k3, n);
        bubble_sort_k(k4, n);
        bubble_sort_k(k5, n);
        bubble_sort_k(k6, n);
        bubble_sort_k(k7, n);
        bubble_sort_k(k8, n);
        bubble_sort_k(k9, n);
        bubble_sort_k(k0, n);

        time_c = time_now() - time_c;
        time_key_bbl += time_c;

        // --------------------------------------------------------------------------------
        // выбор
        status = make_table(b1, n);
        status = make_table(b2, n);
        status = make_table(b3, n);
        status = make_table(b4, n);
        status = make_table(b5, n);
        status = make_table(b6, n);
        status = make_table(b7, n);
        status = make_table(b8, n);
        status = make_table(b9, n);
        status = make_table(b0, n);

        use_key(b0, k0, n);
        use_key(b1, k1, n);
        use_key(b2, k2, n);
        use_key(b3, k3, n);
        use_key(b4, k4, n);
        use_key(b5, k5, n);
        use_key(b6, k6, n);
        use_key(b7, k7, n);
        use_key(b8, k8, n);
        use_key(b9, k9, n);
        // -----------------------------------------------------------

        time_c = time_now();

        choice_sort_db(b1, n);
        choice_sort_db(b2, n);
        choice_sort_db(b3, n);
        choice_sort_db(b4, n);
        choice_sort_db(b5, n);
        choice_sort_db(b6, n);
        choice_sort_db(b7, n);
        choice_sort_db(b8, n);
        choice_sort_db(b9, n);
        choice_sort_db(b0, n);

        time_c = time_now() - time_c;
        time_db_chs += time_c;

        // ----------------------------------

        time_c = time_now();

        choice_sort_k(k1, n);
        choice_sort_k(k2, n);
        choice_sort_k(k3, n);
        choice_sort_k(k4, n);
        choice_sort_k(k5, n);
        choice_sort_k(k6, n);
        choice_sort_k(k7, n);
        choice_sort_k(k8, n);
        choice_sort_k(k9, n);
        choice_sort_k(k0, n);

        time_c = time_now() - time_c;
        time_key_chs += time_c;

        printf("|%4d|%7lld|%7lld|%7lld|%7lld|\n", n, time_db_bbl/10, time_key_bbl/10, time_db_chs/10, time_key_chs/10);
    }
    
    printf("\n\n\n|  n | table |  keys |\n");
    int size[5] = {1, 50, 100, 500, 1000};
    for (int i = 0; i < 5; i++)
    {
        printf("|%4d|%7d|%7d|\n", size[i], (int) sizeof(struct abonent_t) * size[i], (int) sizeof(struct key_s) * size[i]);
    }
}