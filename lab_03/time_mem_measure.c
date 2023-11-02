#include "consts.h"
#include "time_mem_measure.h"
#include "matrix_operations.h"
#include "in_out_put.h"

long long int time_now(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
    long long int res = t.tv_sec * 1000000 + t.tv_usec;
    return res;
}

void measure_time_experiment(void)
{
    printf("if you need only time, input 1\nif you need only mem - 2\nfor both input 0\n");
    int c_num = read_int(": ", 0, 2);
    char *command = "time/mem";
    if (c_num == 1)
        command = "time";
    else if (c_num == 2)
        command = "mem";

    mat_t arr = {};
    vec_t vec = {};
    col_t col = {}, res1 = {}, res2 = {};
    col_v col_vec = {};
    int size[6] = {5, 10, 15, 25, 50, 100};
    int mem_reg[6] = {0, 0, 0, 0, 0, 0};
    int mem_irr[6] = {0, 0, 0, 0, 0, 0};
    int time_reg_a[6] = {0, 0, 0, 0, 0, 0};
    int time_irr_a[6] = {0, 0, 0, 0, 0, 0};

    printf(
        "'--------------------------------------------------------------------------------------------------------------'\n");
    printf(
        "|    fill||       size 5x5||     size 10x10||     size 15x15||     size 25x25||     size 50x50||   size 100x100|\n");
    printf("|%8s||    irr|    reg||    irr|    reg||    irr|    reg||    irr|    reg||    irr|    reg||    irr|    reg|\n",
           command);
    printf(
        "'--------''-------'-------''-------'-------''-------'-------''-------'-------''-------'-------''-------'-------'\n");

    for (int fill = 0; fill <= 100; fill += 10)
    {
        for (int i = 0; (i < 6) && (c_num < 2); i++)
        {
            for (int tick = 0; tick < 100; tick++)
            {
                // matrix generation
                int time_reg = 0, time_irr = 0;
                long long int time_beg = 0, time_end = 0;

                arr.row_c = size[i];
                arr.col_c = size[i];
                col.n = size[i];

                generate_matrix(&arr, fill);
                generate_col(&col, fill);
                translate_col_to_vector(col, &col_vec);

                mem_reg[i] = size[i] * size[i] * sizeof(int);

                // measure reg
                time_beg = time_now();
                multiply_arrays_regular(arr, col, &res1);
                time_end = time_now();
                time_reg = time_end - time_beg;

                // measure irreg
                translate_to_vector(arr, &vec);
                mem_irr[i] = (2 * vec.n + vec.n_ia) * sizeof(int);

                time_beg = time_now();
                multiply_arrays_irregular(vec, col_vec, &res2);
                time_end = time_now();
                time_irr = time_end - time_beg;

                //            printf("\n\n%lld\n", time_reg);
                time_reg_a[i] += time_reg;
                time_irr_a[i] += time_irr;
            }
        }

        // printing
        if (c_num < 2)
        {
            printf("|t %6d|", fill);
            for (int i = 0; i < 6; i++)
            {
                printf("|%7.2lf|%7.2lf|", (double) time_irr_a[i] / 100, (double) time_reg_a[i] / 100);
            }
            printf("\n");
        }

        if (c_num != 1)
        {
            printf("|m %6d|", fill);
            for (int i = 0; i < 6; i++)
            {
                printf("|%7d|%7d|", mem_irr[i], mem_reg[i]);
            }
            printf("\n");
        }
//         time eff
        printf("|tef ir/r|");
        for (int i = 0; i < 6; i++)
        {
            printf("|%15lf|", (double) (time_reg_a[i] - time_irr_a[i]) / (time_reg_a[i]));
        }
        printf("\n");

//         mem eff
        printf("|mef ir/r|");
        for (int i = 0; i < 6; i++)
        {
            printf("|%15lf|", (double) (mem_reg[i] - mem_irr[i]) / (mem_reg[i]));
        }
        printf("\n");

        printf(
            "'--------''-------'-------''-------'-------''-------'-------''-------'-------''-------'-------''-------'-------'\n");

    }
}