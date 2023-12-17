#include "consts.h"
#include "input.h"
#include "commands.h"
#include "key_and_sort.h"

int error_handler(int status);
int proccess(abonent_t_book book, key_table_arr key_tbl, int n);

int main()
{
    int status = SUCCESS;
    int n = abonent_t_CNT;
    abonent_t_book book;
    key_table_arr key_tbl;
    status = make_table(book, n);
    use_key(book, key_tbl, n);
    status = proccess(book, key_tbl, n);
    return error_handler(status);
}

int proccess(abonent_t_book book, key_table_arr key_tbl, int n)
{
    int status = SUCCESS;
    int code = START;
    int rc = 0;
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
                if (n == 0)
                    printf("empty\n");
                else
                    print_book(book, n);
                break;
            case ADD:
                add_line(book, key_tbl, n);
                n++;
                break;
            case DELETE:
                delete_line(book, key_tbl, &n);
                break;
            case SORT_KEY_BBL:
                bubble_sort_k(key_tbl, n);
                break;
            case SORT_KEY_CHS:
                choice_sort_k(key_tbl, n);
                break;
            case PRINT_KEY:
                print_key_table(key_tbl, n);
                break;
            case EXIT:
                break;
            default:
                printf("Unknown command\n");
                break;
            }
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