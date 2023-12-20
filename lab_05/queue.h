#ifndef QUE_H
#define QUE_H

#define Q_LEN 1000
#define LOOP_CNT 5
#define INFO_CNT 100
#define PRINT_CNT 5

// один узел
typedef struct node node_t;
struct node
{
    int data;
    node_t *next;
};

// очередь на списке
typedef struct list_que list_que_t;
struct list_que
{
    node_t *p_in;
    node_t *p_out;
};

// очередь на массиве
typedef struct arr_que arr_que_t;
struct arr_que
{
    int *p_in;
    int *p_out;
    int *p_start;
    int *p_end;
};

// состояние очереди
typedef struct q_state q_state_t;
struct q_state
{
    arr_que_t *q_arr;
    list_que_t *q_list;
    int int_min;
    int int_max;
    int process_min;
    int process_max;
};

void process_array(q_state_t *state);
void process_list(q_state_t *state);

void free_list_queue(list_que_t *q_list);

void study_time_list(list_que_t *q_list);
void study_time_array(arr_que_t *q_arr);
void study_avg_time(q_state_t *state);

#endif