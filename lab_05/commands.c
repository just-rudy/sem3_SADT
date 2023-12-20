#include <stdio.h>
#include <time.h>

#include "commands.h"
#include "queue.h"

void clean_que(q_state_t *state);

void do_array(q_state_t *state)
{
    if (state == NULL || state->q_arr == NULL || state->q_arr->p_end == NULL || state->q_arr->p_in == NULL || state->q_arr->p_out < state->q_arr->p_in)
        printf("array is NULL");
    else
    {
        clean_que(state);
        process_array(state);
    }
}

void do_list(q_state_t *state)
{
    char answer = 0;
    if (state == NULL || state->q_list == NULL)
        return;
    clean_que(state);
    process_list(state);
}

void change_intervals(q_state_t *state)
{
    int interval_min, interval_max, process_min, process_max, check;
    char ch;
    // интервалы прихода заявки
    printf("Input intervals of arriving req: ");
    check = scanf("%d%d%c", &interval_min, &interval_max, &ch);
    if (check == 3 && interval_max >= 0 && interval_min >= 0 && interval_max > interval_min)
    {
        // интервалы обработки заявки
        printf("input intervals of processing req: ");
        check = scanf("%d%d%c", &process_min, &process_max, &ch);
        if (check == 3 && process_min >= 0 && process_max >= 0 && process_max > process_min)
        {
            // успех по смене интервалов
            printf("Success!\n");
            state->int_max = interval_max;
            state->int_min = interval_min;
            state->process_max = process_max;
            state->process_min = process_min;
        }
        else
            printf("input error!\n");
    }
    else
        printf("input error!\n");
    while (ch != '\n' && ch != EOF)
    {
        scanf("%c", &ch);
    }
}

void study_time(q_state_t *state)
{
    study_time_array(state->q_arr);
    study_time_list(state->q_list);
    study_avg_time(state);
}

void clean_que(q_state_t *state)
{
    for (int i = 0; i < Q_LEN; i++)
    {
        *(state->q_arr->p_start + i) = 0;
    }
    state->q_arr->p_in = state->q_arr->p_start;
    state->q_arr->p_out = state->q_arr->p_start;
    free_list_queue(state->q_list);
}

// void free_list_que(list_que_t *q_list)
// {
//     node_t *cur = q_list->p_in;
//     while (cur && cur != cur->next)
//     {
//         q_list->p_in = cur->next;
//         free(cur);
//         cur = q_list->p_in;
//     }
//     q_list->p_in = NULL;
//     q_list->p_out = NULL;
// }