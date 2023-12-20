#include "queue.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int is_long(q_state_t *state);
void add_to_list_queue(list_que_t *q_list, int el, int with_info);
void add_to_array_queue(arr_que_t *q_arr, int element);
void process_list_element(list_que_t *q_list, int *el, int *exited, int with_info, int *loaded, int *in_queue);
void process_array_element(arr_que_t *q_arr, int *element, int *exited, int *loaded, int *in_queue);
int get_element_from_array_queue(arr_que_t *q_arr);
int get_el_from_list_queue(list_que_t *q_list, int with_info);
double get_processing_time(q_state_t *state);
double get_random_interval(q_state_t *state);
void print_result(q_state_t *state, double time, int loaded, int exited, int done, double procor_waited);
void print_cur(q_state_t *state, double time, double avg, int loaded, int exited, int done, double procor_waited);

void process_array(q_state_t *state)
{
    if (state->q_arr == NULL || state->q_arr->p_in == NULL || state->q_arr->p_start == NULL || state->q_arr->p_start >= state->q_arr->p_end || state->q_arr->p_out == NULL || state->q_arr->p_end == NULL)
        return;

    int done = 0;
    int loaded = 0;
    int exited = 0;
    int el = 0;
    double avg = 0;
    int sum_for_average_queue_length = 0;
    int iterator = 0;
    char is_processor_free = 1;
    int elements_in_queue = 0;
    double time = 0;
    double procor_waited = 0;
    double queue_waited = 0;
    double procor_worked = 0;
    double remained_time = 0;
    double working_time = 0;
    double interval = 0;
    double process_iteration = 0;
    do
    {   
        if (is_long(state) && done > Q_LEN * LOOP_CNT - INFO_CNT)
            break;
        interval = get_random_interval(state);
        time += interval;
        sum_for_average_queue_length += elements_in_queue;
        iterator++;
        
        if (elements_in_queue < Q_LEN - 1)
        {
            if (loaded < Q_LEN * LOOP_CNT)
            {
                loaded++;
            }
            elements_in_queue++;
            add_to_array_queue(state->q_arr, el);
        }
        if (!is_processor_free && interval >= remained_time)
        {
            is_processor_free = 1;
            remained_time = 0;
            done++;
            interval -= remained_time;
            if (done % INFO_CNT == 0 && done < Q_LEN * LOOP_CNT)
            {
                avg = ((double)sum_for_average_queue_length) / iterator;   
                printf("\n");
                printf("done at the time: %d\n", done);
                printf("cur queue len: %d\n", elements_in_queue);
                printf("out req cnt: %d\n", is_long(state) ? (done - elements_in_queue) / LOOP_CNT : exited);
                printf("avg gue len: %lf\n", avg);
                printf("\n");
            }
            elements_in_queue--;
        }
        else if (!is_processor_free)
        {
            remained_time -= interval;
        }
        process_iteration = 0;
        while (is_processor_free && elements_in_queue != 0 && process_iteration < interval)
        {
            if (is_long(state) && done > Q_LEN * LOOP_CNT - INFO_CNT)
                break;
            working_time = get_processing_time(state);
            process_array_element(state->q_arr, &el, &exited, &loaded, &elements_in_queue);
            process_iteration += working_time;
            procor_worked += working_time;
            if (done < Q_LEN * LOOP_CNT)
            {
                if (working_time < interval)
                {
                    done++;
                    if (done % INFO_CNT == 0 && done < Q_LEN * LOOP_CNT)
                    {
                        avg = ((double)sum_for_average_queue_length) / iterator;
                        printf("\n");
                        printf("done at the time: %d\n", done);
                        printf("cur que len: %d\n", elements_in_queue);
                        printf("out req cnt: %d\n", is_long(state) ? (done - elements_in_queue) / LOOP_CNT : exited);
                        printf("avg que len: %lf\n", avg);
                        printf("\n");
                    }
                    procor_waited += (interval - working_time);
                    is_processor_free = 1;
                    elements_in_queue--;
                }
                else
                {
                    queue_waited += (working_time - interval);
                    remained_time += (working_time - interval);
                    is_processor_free = 0;
                }
            }
        }
    }
    while (loaded < Q_LEN * LOOP_CNT || done < Q_LEN * LOOP_CNT || exited < Q_LEN);
    for (int *p = state->q_arr->p_start; p < state->q_arr->p_end; p++)
        *p = 0;
    state->q_arr->p_in = state->q_arr->p_start;
    state->q_arr->p_out = state->q_arr->p_start;
    print_cur(state, time, avg, loaded, exited, done, procor_waited);
}

void add_to_array_queue(arr_que_t *q_arr, int element)
{
    if (q_arr == NULL || q_arr->p_in == NULL || \
    q_arr->p_start == NULL || q_arr->p_start >= q_arr->p_end || \
    q_arr->p_out == NULL || q_arr->p_end == NULL)
        return;
    if (q_arr->p_in >= q_arr->p_end)
    {
        return;
    }
    *(q_arr->p_in) = element;
    if (q_arr->p_in + 1 != q_arr->p_out)
    {
        q_arr->p_in += 1;
        if (q_arr->p_in >= q_arr->p_end && q_arr->p_out != q_arr->p_start)
            q_arr->p_in = q_arr->p_start;
    }
    else
    {
        //printf("Очередь заполнена!\n");
    }
}

void process_array_element(arr_que_t *q_arr, int *element, int *exited, int *loaded, int *in_queue)
{
    if (q_arr == NULL || q_arr->p_in == NULL || \
    q_arr->p_out == NULL || q_arr->p_end == NULL || \
    q_arr->p_start == NULL || q_arr->p_start >= q_arr->p_end || \
    element == NULL || exited == NULL)
        return;
    int processing_element = get_element_from_array_queue(q_arr);
    if (processing_element < 0)
        return;
    processing_element++;
    if (processing_element == 5)
    {
        if (*exited < Q_LEN)
            *exited += 1;
        *element = 0;

    }
    else
    {
        if (*in_queue < Q_LEN)
        {
            *loaded += 1;
            *in_queue += 1;
            add_to_array_queue(q_arr, processing_element);
        }
        else
            *element = processing_element;
    }
}

int get_element_from_array_queue(arr_que_t *q_arr)
{
    if (q_arr == NULL || q_arr->p_in == NULL || \
    q_arr->p_start == NULL || q_arr->p_start >= q_arr->p_end || \
    q_arr->p_out == NULL || q_arr->p_end == NULL || \
    q_arr->p_out == q_arr->p_in)
        return -1;
    
    int element = *(q_arr->p_out);
    q_arr->p_out += 1;
    if (q_arr->p_out >= q_arr->p_end)
    {
        q_arr->p_out = q_arr->p_start;
    }
    return element;
}

void study_time_array(arr_que_t *q_arr)
{
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < Q_LEN; i++)
        add_to_array_queue(q_arr, i);
    gettimeofday(&tv_stop, NULL);
    double array_push_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На запись одного элемента в очередь-массив ушло %ld нс и %ld байт памяти\n", \
    (long) (array_push_time * 1000) / Q_LEN, sizeof(int));

    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < Q_LEN; i++)
        q_arr->p_out++;//get_element_from_array_queue(q_arr);
    gettimeofday(&tv_stop, NULL);
    double array_pop_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("На чтение одного элемента в очередь-массив ушло %ld нс и %ld байт памяти\n", \
    (long) (array_pop_time * 1000) / Q_LEN, sizeof(int));
}

void process_list(q_state_t *state)
{
    if (state->q_list == NULL)
        return;

    int done = 0;
    int loaded = 0;
    int exited = 0;
    int el = 0;
    int sum = 0;
    int i = 0;
    char is_processor_free = 1;
    int que_els = 0;
    double time = 0;
    double procor_waited = 0;
    double queue_waited = 0;
    double procor_worked = 0;
    double remained_time = 0;
    double working_time = 0;
    double interval = 0;
    double process_iteration = 0;
    double avg;
    int with_info = 1;

    do
    { 
        if (is_long(state) && done >= Q_LEN * LOOP_CNT - INFO_CNT)
            break;

        interval = get_random_interval(state);
        time += interval;
        sum += que_els;
        i++;

        if (que_els < Q_LEN - 1)
        {
            if (loaded < Q_LEN * LOOP_CNT)
                loaded++;

            add_to_list_queue(state->q_list, el, (with_info && done > Q_LEN * LOOP_CNT - INFO_CNT - PRINT_CNT));
            que_els++;
        }
        if (!is_processor_free && interval >= remained_time)
        {
            is_processor_free = 1;
            remained_time = 0;
            done++;
            if (done % INFO_CNT == 0 && done < Q_LEN * LOOP_CNT)
            {
                avg = ((double)sum) / i;
                printf("\n");
                printf("already done: %d\n", done);
                printf("current length: %d\n", que_els);
                printf("gone requests cnt: %d\n", is_long(state) ? (done - que_els) / LOOP_CNT : exited);
                printf("avg que len: %lf\n", avg);
                printf("\n");
            }
            que_els--;
        }
        else if (!is_processor_free)
        {
            remained_time -= interval;
        }
        process_iteration = 0;
        while (is_processor_free && que_els != 0 && process_iteration < interval)
        {
            if (is_long(state) && done >= Q_LEN * LOOP_CNT - INFO_CNT)
                break;
            working_time = get_processing_time(state);
            process_list_element(state->q_list, &el, &exited, \
            (with_info && done > Q_LEN * LOOP_CNT - PRINT_CNT), &loaded, &que_els);
            process_iteration += working_time;
            procor_worked += working_time;
            if (done < Q_LEN * LOOP_CNT)
            {
                if (working_time < interval)
                {
                    done++;
                    if (done % INFO_CNT == 0 && done < Q_LEN * LOOP_CNT)
                    {
                        avg = ((double)sum) / i;
                        printf("\n");
                        printf("Сейчас обслужено: %d\n", done);
                        printf("Текущая длина очереди: %d\n", que_els);
                        printf("Количество вышедших заявок: %d\n", is_long(state) ? (done - que_els) / LOOP_CNT : exited);
                        printf("Средняя длина очереди: %lf\n", avg);
                        printf("\n");
                    }
                    procor_waited += (interval - working_time);
                    is_processor_free = 1;
                    que_els--;
                }
                else
                {
                    queue_waited += (working_time - interval);
                    remained_time += (working_time - interval);
                    is_processor_free = 0;
                }
            }
        }
    }
    while (loaded < Q_LEN * LOOP_CNT || done < Q_LEN * LOOP_CNT || exited < Q_LEN);
    free_list_queue(state->q_list);
    print_cur(state, time, avg, loaded, exited, done, procor_waited);
}

void free_list_queue(list_que_t *q_list)
{
    node_t *t = q_list->p_in;
    while (t && t != t->next)
    {
        q_list->p_in = t->next;
        free(t);
        t = q_list->p_in;
    }
    q_list->p_in = NULL;
    q_list->p_out = NULL;
}

double get_random_interval(q_state_t *state)
{
    double interval = ((double) rand() / RAND_MAX) * (state->int_max - state->int_min) + state->int_min;
    return interval;
}

double get_processing_time(q_state_t *state)
{
    double processing_time = ((double) rand() / RAND_MAX) * (state->process_max - state->process_min) + state->process_min;
    return processing_time;
}

void process_list_element(list_que_t *q_list, int *el, int *exited, int with_info, int *loaded, int *in_queue)
{
    if (q_list == NULL || q_list->p_in == NULL || q_list->p_out == NULL || el == NULL || exited == NULL)
        return;

    int process_el = get_el_from_list_queue(q_list, with_info);

    if (process_el < 0)
        return;

    process_el++;
    if (process_el == 5)
    {
        if (*exited != Q_LEN)
            *exited += 1;
        *el = 0;
    }
    else
    {
        if (*in_queue < Q_LEN)
        {
            *loaded += 1;
            *in_queue += 1;
            add_to_list_queue(q_list, process_el, with_info);
        }
        else
            *el = process_el;
    }
}

int get_el_from_list_queue(list_que_t *q_list, int with_info)
{
    if (q_list == NULL || q_list->p_in == NULL || \
    q_list->p_out == NULL)
        return -1;
    node_t *t = q_list->p_in;
    int element = 0;
    if (q_list->p_in == q_list->p_out)
    {
        element = q_list->p_out->data;
        if (with_info)
            printf("DELETED: %ld\n", (long int) q_list->p_out);
        free(q_list->p_out);
        q_list->p_out = NULL;
        q_list->p_in = NULL;
    }
    else
    {
        while (t->next != q_list->p_out && t != t->next)
        {
            t = t->next;
        }
        t->next = NULL;
        element = q_list->p_out->data;
        if (with_info)
            printf("DELETED: %ld\n", (long int) q_list->p_out);
        free(q_list->p_out);
        q_list->p_out = t;
    }
    return element;
}

void add_to_list_queue(list_que_t *q_list, int el, int with_info)
{
    if (q_list == NULL)
        return;
    node_t *new_node = NULL;
    new_node = calloc(1, sizeof(node_t));
    if (new_node)
    {
        if (with_info)
            printf("ADDED  : %ld\n", (long int) new_node);
        new_node->data = el;
        q_list->p_in = new_node;
        if (q_list->p_in == NULL || q_list->p_out == NULL)
        {
            new_node->next = NULL;
            q_list->p_out = new_node;
        }
        else
            new_node->next = q_list->p_in;
    }
    else
        printf("MEM error\n");
}

int is_long(q_state_t *state)
{
    return ((state->int_max - state->int_min) <= (state->process_max - state->process_min));
}

void print_result(q_state_t *state, double time, int loaded, int exited, int done, double procor_waited)
{
    if (is_long(state))
        time = (((double)(state->process_max - state->process_min) / 2 * Q_LEN * LOOP_CNT) - get_processing_time(state));
    loaded = Q_LEN * LOOP_CNT;
    exited = Q_LEN;
    done = loaded;
    procor_waited /= Q_LEN;
    procor_waited *= LOOP_CNT;
    printf("time proccessing: %lf\n", time);
    printf("cnt in: %d\n", loaded);
    printf("cnt out: %d\n", exited);
    printf("cnt OA works: %d\n", done);
    printf("proc waires: %lf ед. вр.\n", procor_waited);
}

void print_cur(q_state_t *state, double time, double avg, int loaded, int exited, int done, double procor_waited)
{
    printf("\n");
    printf("Done at the moment: %d\n", Q_LEN * LOOP_CNT);
    printf("cur queue len: %d\n", 0);
    printf("cnt out reqs: %d\n", Q_LEN);
    printf("avg queue len: %lf\n", avg);
    printf("\n");
    print_result(state, time, loaded, exited, done, procor_waited);
}

void study_time_list(list_que_t *q_list)
{
    struct timeval tv_start, tv_stop;
    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < Q_LEN; i++)
        add_to_list_queue(q_list, i, 0);
    gettimeofday(&tv_stop, NULL);
    double node_push_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("to wrinte one node que el: %ld нс и %ld байт памяти\n", \
    (long) (node_push_time * 1000) / Q_LEN, sizeof(node_t));

    gettimeofday(&tv_start, NULL);
    for (int i = 0; i < Q_LEN; i++)
        get_el_from_list_queue(q_list, 0);
    gettimeofday(&tv_stop, NULL);
    double node_pop_time = (double) (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    printf("to read one node que el: %ld нс и %ld байт памяти\n", \
    (long) (node_pop_time * 1000) / Q_LEN, sizeof(node_t));
}

void study_avg_time(q_state_t *state)
{
    double time = 0;
    double waiting = 0;
    double interval = 0;
    double coming = 0;
    double proc = 0;
    double process_sum = 0;
    for (int i = 0; i < Q_LEN; i++)
    {
        for (int j = 0; j < Q_LEN * LOOP_CNT; j++)
        {
            interval = get_random_interval(state);
            time += interval;
            coming += interval;
            proc = get_processing_time(state);
            waiting += interval - proc;
            process_sum += proc;
        }
    }
    coming = coming / Q_LEN / LOOP_CNT;
    printf("Среднее время моделирования по входу: %lf ед. вр.\n", coming);
    double true_coming = ((double)(state->int_max + state->int_min)) / 2;
    true_coming *= Q_LEN;
    double percentage = 100 * (true_coming - coming) / true_coming;
    if (percentage < 0 )
        percentage *= (-1);
    printf("Погрешность для времени моделирования по входу: %lf %%\n", percentage);
    printf("Среднее время моделирования по выходу: %lf ед. вр.\n", process_sum / Q_LEN);
    double true_proc = ((double)(state->process_max - state->process_min)) / 2;
    true_proc *= Q_LEN;
    true_proc *= LOOP_CNT;
    percentage = 100 * (true_proc - process_sum / Q_LEN) / true_proc;
    if (percentage < 0 )
        percentage *= (-1);
    if (waiting < 0)
        waiting *= (-1);
    printf("Погрешность для времени моделирования по выходу: %lf %% \n", percentage);
    printf("Среднее время моделирования: %lf ед. вр. \n", time / (Q_LEN));
    printf("Среднее время простоя: %lf ед. вр. \n", waiting / (Q_LEN));
}
