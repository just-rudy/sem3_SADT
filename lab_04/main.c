#include <stdio.h>
#include "array.h"
#include "time_measure.h"
#include "stack.h"

#define EXIT 0
#define CHECK_ALL 1
#define PUSH_ARR 2
#define POP_ARR 3
#define PRINT_ARR 4
#define PUSH_STACK 5
#define POP_STACK 6
#define PRINT_STACK 7
#define PRINT_TUTORIAL 8
#define INPUT 9
#define TIME 10

#define OK 0
#define N 1000

void print_menu(void);
void error_handler(int err);
int read_int(char *msg, int mn, int mx);

void main(void)
{
    struct node_s *last;
    struct node_s *free_spaces[N_FREE];
    last = NULL;

    char arr_s[N];
    char *arr_c = arr_s - 1;
    char c;

    int free_spaces_cnt = 0;
    int command = 0;
    int rc = OK;
    int result = 0;

    int cnt_s = 0;
    int cnt_a = 0;

    print_menu();

    command = read_int(": ", 0, 0);
    while (command != 0)
    {
        switch (command)
        {
        case EXIT:
            break;

        case PUSH_ARR:
            printf("Input letter: ");
            c = getchar();
            push_array(&arr_c, arr_s + N - 1, c);
            cnt_a++;
            break;

        case POP_ARR:
            rc = pop_array(&arr_c, arr_s, &c);
            cnt_a--;
            cnt_a = (cnt_a < 0) ? 0 : cnt_a;
            if (!rc)
                printf("ARR: popped value: %c\n", c);
            break;

        case PRINT_ARR:
            print_array(arr_s, arr_c);
            break;

        case PUSH_STACK:
            printf("Input letter: ");
            c = getchar();
            last = push_stack(last, c);
            cnt_s++;
            break;

        case POP_STACK:
            if (!last)
                printf("list stack is empty\n");
            else
            {
                char popped;
                last = pop_stack(last, &popped, free_spaces, &free_spaces_cnt);
                printf("popped el: %c\n", popped);
                if (!last)
                    printf("list stack is now empty\n");
            }
            cnt_s--;
            cnt_s = (cnt_s < 0) ? 0 : cnt_s;
            break;

        case PRINT_STACK:
            print_stack(last, free_spaces, free_spaces_cnt);
            break;

        case CHECK_ALL:
            int res_a = check_array(arr_s, arr_c, cnt_a);
            int res_s = check_stack(last, cnt_s);

            printf("\narray:\n");
            print_array(arr_s, arr_c);
            if (res_a)
                printf("array is a palindrome\n");
            else
                printf("array isn't a palindrome\n\n");

            print_stack(last, free_spaces, free_spaces_cnt);
            if (res_s)
                printf("list stack is a palindrome\n");
            else
                printf("list stack isn't a palindrome\n");

            break;

        case PRINT_TUTORIAL:
            print_menu();
            break;

        case INPUT:
            printf("input string: ");
            cnt_a = 0;
            cnt_s = 0;
            char c;
            
            arr_c = arr_s - 1;
            free_spaces_cnt = 0;
            free_list(last);

            while ((c = getchar()) != '\n' && c != ' ' && c != '\t' && cnt_a < N)
            {
                last = push_stack(last, c);
                push_array(&arr_c, arr_s + N - 1, c);
                cnt_a++;
                cnt_s++;

            }
            break;

        case TIME:
            time_measure();
            break;

        default:
            printf("Input error");
            break;
        }
        if (rc)
        {
            error_handler(rc);
            break;
        }
        if (command)
            command = read_int(": ", 0, 0);
    }
    printf("bye");
}

void print_menu(void)
{
    printf("100 to EXIT\n");
    printf("1 to CHECK EXPRESSION\n");
    printf("for REG array:\n");
    printf("\t2 to PUSH\n");
    printf("\t3 to POP\n");
    printf("\t4 to PRINT\n");
    printf("for STACK array:\n");
    printf("\t5 to PUSH\n");
    printf("\t6 to POP\n");
    printf("\t7 to PRINT\n");
    printf("8 to print tutorial again\n");
    printf("9 to INPUT string\n");
    printf("10 for TIME-MEM measure experiment\n");
}

void error_handler(int err)
{
    if (err == TOO_MUCH)
        printf("overfill. current max len = %d\n", N);
    else if (err == EMPTY)
        printf("attempt to pop from empty\n");
}

int read_int(char *msg, int mn, int mx)
{
    int num = 0;
    if (mx)
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