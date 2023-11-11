#include <stdio.h>
#include "array.h"
#include "stack.h"

#define EXIT 100
#define INPUT 0
#define PUSH_ARR 2
#define POP_ARR 3
#define PRINT_ARR 4
#define CHECK_ARR 5
#define PUSH_STACK 6
#define POP_STACK 7
#define PRINT_STACK 8
#define CHECK_STACK 9
#define PRINT_TUTORIAL 10

#define OK 0

void print_menu(void);
void error_handler(int err);
int read_int(char *msg, int mn, int mx);

int main()
{
    struct node_s *last;
    char arr_s[N];
    char *arr_c = arr_s - 1;
    char c;

    int command = 0;
    int rc = OK;
    int result = 0;

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
            break;
        case POP_ARR:
            rc = pop_array(&arr_c, arr_s, &c);
            if (!rc)
                printf("ARR: popped value: %c\n", c);
            break;
        case PRINT_ARR:
            print_array(arr_s, arr_c);
            break;
            //            case PUSH_STACK:
            //                push_stack();
            //                break;
            //            case POP_STACK:
            //                pop_stack();
            //                break;
            //            case PRINT_STACK:
            //                print_stack();
            //                break;
            //            case CHECK_ARR:
            //                result = check_array();
            //                break;
            //            case CHECK_STACK:
            //                result = check_stack();
            //                break;
        default:
            printf("Input error");
            break;
        }
        if (rc)
        {
            error_handler(rc);
            break;
        }
        command = read_int(": ", 0, 0);
    }
}

void print_menu(void)
{
    printf("100 to EXIT\n");
    printf("0 to CHECK EXPRESSION\n");
    //    printf("1 for TIME MEASURE EXPERIMENT\n");
    printf("for REG array:\n");
    printf("\t2 to PUSH\n");
    printf("\t3 to POP\n");
    printf("\t4 to PRINT\n");
    printf("for STACK array:\n");
    printf("\t5 to PUSH\n");
    printf("\t6 to POP\n");
    printf("\t7 to PRINT\n");
    printf("8 to print tutorial again\n");
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
