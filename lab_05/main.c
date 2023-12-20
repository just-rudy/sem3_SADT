#include <stdio.h>
#include <stdlib.h>

#include "queue.h"
#include "commands.h"

#define EXIT  0
#define TUTOR 1
#define ARR_Q 2
#define LST_Q 3
#define TIME  4
#define CHANGE_T 5

// #define Q_LEN 1000

int read_int(char *msg, int mn, int mx);
void print_tutorial();

int main()
{
    int array[Q_LEN] = { 0 };
    arr_que_t q_arr = { array, array, array, array + Q_LEN};
    list_que_t q_list = {NULL, NULL};
    q_state_t state = {&q_arr, &q_list, 0, 6, 0, 1};

    print_tutorial();
    int command = read_int("command: ", 0, 6);
    while (command != EXIT)
    {
        switch (command)
        {
        case EXIT:
            break;
        case TUTOR:
            print_tutorial();
            break;
        case ARR_Q:
            do_array(&state);
            break;
        case LST_Q:
            do_list(&state);
            break;
        case TIME:
            study_time(&state);
            break;
        case CHANGE_T:
            change_intervals(&state);
            break;
        default:
            printf("неизвестная команда");
            break;
        }
        command = read_int("command: ", 0, 6);
    }
}

void print_tutorial()
{
    printf("0 to EXIT\n");
    printf("1 to print TUTORIAL\n");
    printf("2 to start array queue\n");
    printf("3 to start list queue\n");
    printf("4 to compare time\n");
    // printf("5 to choose time intervals\n");
}

int read_int(char *msg, int mn, int mx)
{
    int num = 0;
    if (mx >= mn)
    {
        do
        {
            printf("%s", msg);
            if (scanf("%d", &num) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("Ooops, try again\n");
            }
            else if (num < mn || num > mx)
            {
                printf("Ooops, try again\n");
            }
        } while (num < mn || num > mx);
    }
    else
    {
        do
        {
            printf("%s", msg);
            if (scanf("%d", &num) != 1)
            {
                while (getchar() != '\n')
                    ;
                printf("Ooops, try again\n");
            }
            else
            {
                getchar();
                break;
            }
        } while (1);
    }

    return num;
}