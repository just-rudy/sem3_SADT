#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

#define EXIT 0
#define REG 1
#define TUT 2
#define PR_TR_PST 3
#define PR_TR_REG 4

void print_tutorial(void);
int read_int(char *msg, int mn, int mx);

int main()
{
    char str[100];
    node_t *root = NULL;
    node_t *balanced_root = NULL;

    print_tutorial();
    int command = read_int(": ", 1, 9);
    while (command != EXIT)
    {
        switch (command)
        {
        case REG:
            printf("input you string: ");
            scanf("%s", &str);
            root = str_to_tree(str);
            print_tree(root, 0);
            printf("\n");
            print_tree_post(root);
            printf("\n");
            balanced_root = balance_tree(root);
            print_tree(balanced_root, 0);
            break;
        // case PUSH:
        //     char ch = ' ';
        //     printf("input char: ");
        //     while (ch == '\n' || ch == ' ')
        //         scanf("%c", &ch);
        //     node_t *new_node = create_node(ch);
        //     root = push_tree(root, new_node);
        //     break;
        // case TIME:
        //     time_analis();
        //     break;
        case PR_TR_PST:
            print_tree_post(root);
            printf("\n");
            break;
        case PR_TR_REG:
            print_tree(root, 0);
            printf("\n");
            break;
        case TUT:
            print_tutorial();
            break;
        case EXIT:
            break;
        default:
            printf("wrong command\n");
            break;
        }
        command = read_int(": ", 1, 9);
    }
}

void print_tutorial(void)
{
    printf("regular     - 1\n");
    printf("del by key  - 2\n");
    printf("push new    - 3\n");
    printf("post print  - 4\n");
    printf("tree print  - 5\n");
    printf("time-mem    - 6\n");
    printf("tutorial    - 7\n");
    printf("string      - 9\n");
    printf("to look for - 8\n\n");
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