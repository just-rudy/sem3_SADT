#include "consts.h"
#include "input.h"
#include "commands.h"
#include "key_and_sort.h"

int error_handler(int status);
int proccess(abonent_t_book book, int n);

int main()
{
    int status = SUCCESS;
    int n = abonent_t_CNT;
    abonent_t_book book;
    status = make_table(book, n);
    status = proccess(book, n);
    return error_handler(status);
}

int proccess(abonent_t_book book, int n)
{
    int status = SUCCESS;
    int code = START;
    int rc = 0;
    int if_key_exist = 0;
    key_table_arr key_tbl;
    print_tutorial();
    while (code != EXIT)
    {
        printf(": ");
        char c;
        if (scanf("%d%c", &code, &c) == 2 && c == '\n')
            switch (code)
            {
            case TUTORIAL:
                print_tutorial();
                break;
            case PRINT_TBL:
                print_book(book, n);
                break;
            case ADD:
                add_line(book, n);
                n++;
                break;
            case DELETE:
                delete_line(book, n);
                n--;
                break;
            case MAKE_KEY:
                use_key(book, key_tbl, n);
                if_key_exist = 1;
                break;
            case SORT_KEY_BBL:
                if (if_key_exist)
                    bubble_sort_k(key_tbl, n);
                else
                    printf("Make a key table (5) first!\n");
                break;
            case SORT_KEY_CHS:
                if (if_key_exist)
                    choice_sort_k(key_tbl, n);
                else
                    printf("Make a key table (5) first!\n");
                break;
            case PRINT_KEY:
                if (if_key_exist)
                    print_key_table(key_tbl, n);
                else
                    printf("Make a key table (5) first!\n");
                break;
            default:
                printf("Unknown command\n");
                break;
            }
        else
            printf("Unknown command\n");
    }
    return status;
}

int error_handler(int status)
{
    switch (status)
    {
    case SUCCESS:
        printf("Done!");
        break;
    case MALLOC_ERR:
        printf("Malloc error");
        break;
    default:
        break;
    }
}