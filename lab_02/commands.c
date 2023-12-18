#include "commands.h"

int read_int(char *msg, int mn, int mx);
void shift(abonent_t_book book, int idx, int n);
// void shift_key(key_table_arr tbl, int idx, int n);
void print_one_abonent_t(struct abonent_t person);

int read_string(string str)
{
    int status = SUCCESS;
    int ch = 0, i = 0;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if (i < MAX_STR_LEN - 1)
            str[i++] = ch;
        else
            status = LONG_STR;
    }
    str[i] = '\0';
    return status;
}

int if_leap(int year)
{
    if (year % 400 == 0)
        return 1;
    if (year % 100 == 0)
        return 0;
    if (year % 4 == 0)
        return 1;
    return 0;
}

void check_for_bday(abonent_t_book book, int n)
{
    // ввести дату
    int d, m, cur_y;
    printf("input current date\n");
    cur_y = read_int("year: ", 0, -1);
    m = read_int("month(num): ", 1, 12);
    int max_day;
    if (m == 4 || m == 6 || m == 9 || m == 11)
        max_day = 30;
    else if (m != 2)
        max_day = 31;
    else if (if_leap(cur_y))
        max_day = 29;
    else
        max_day = 28;
    d = read_int("day: ", 1, max_day);

    for (int i = 0; i < n; i++)
    {
        if (book[i].status_t == PERSONAL)
        {
            int p_d = book[i].stat.personal.day;
            int p_m = book[i].stat.personal.month;

            if (p_m == m && p_d - d <= 6)
                print_one_abonent_t(book[i]);
            else if (p_m - m == 1 || (m == 12 && p_m == 1))
            {
                if (m == 4 || m == 6 || m == 9 || m == 11)
                    p_d += 30;
                else if (m == 2)
                    if (if_leap(cur_y))
                        p_d += 29;
                    else
                        p_d += 28;
                else
                    p_d += 31;
                
                if (p_d - d <= 6)
                    print_one_abonent_t(book[i]);
            }           
        }
    }
}

void print_tutorial()
{
    printf("Command:\n");
    printf("1 to exit\n");
    printf("2 to read tutorial again\n");
    printf("3 for adding new abonent_t\n");
    printf("4 for deleting abonent_t\n");
    printf("for sorting key table:\n");
    printf("\t5 by choice\n");
    printf("\t6 by bubble\n");
    printf("for just table:\n");
    printf("\t7 by choice\n");
    printf("\t8 by bubble\n");
    printf("9 for time measure\n");
    printf("10 for bday check\n");
    printf("100 to print abonenet book\n");
    printf("500 to print key_table\n");
}

void print_one_abonent_t(struct abonent_t person)
{
    printf("|%3d|%16s|%18s|%16s|%8s|%3d|", person.idx, person.name, person.surname, person.addres.street, person.addres.house, person.status_t);
    if (person.status_t == PERSONAL)
        printf("     bday: %12d.%2d.%4d|\n", person.stat.personal.day, person.stat.personal.month, person.stat.personal.year);
    else
        printf("%14s - %14s|\n", person.stat.working.organisation, person.stat.working.position);
}

void print_book(abonent_t_book book, int n)
{
    printf("| N |      name      |     surname      |          adress         |p-0|             status            |\n");
    printf("|   |                |                  |     street     |  home  |w-1|                               |\n");
    printf("|---|----------------|------------------|----------------|--------|---|-------------------------------|\n");

    for (int i = 0; i < n; i++)
    {
        print_one_abonent_t(book[i]);
        if ((i + 1) % 5 == 0)
            printf("|---|----------------|------------------|----------------|--------|---|-------------------------------|\n");
    }
}

void add_line(abonent_t_book book, key_table_arr key_tbl, int n)
{
    int status = SUCCESS;
    string tmp_str;
    char c;

    // idx
    book[n].idx = n;
    // name
    printf("input name: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
        status = SUCCESS;
    }
    strcpy(book[n].name, tmp_str);

    // surname
    printf("input surname: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
        status = SUCCESS;
    }
    strcpy(book[n].surname, tmp_str);

    // address
    // street
    printf("input you home addres\nstart with your street: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
        status = SUCCESS;
    }
    strcpy(book[n].addres.street, tmp_str);

    // house
    printf("and your house: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
        status = SUCCESS;
    }
    strcpy(book[n].addres.house, tmp_str);

    // status
    printf("for personal input 0 else input 1: ");
    int tmp_int = 0;
    while (scanf("%d%c", &tmp_int, &c) != 2 && c == '\n' || (tmp_int != 0 && tmp_int != 1))
        printf("try again: ");
    // printf("name: %d\n", tmp_int);

    if (tmp_int == 0)
    {
        book[n].status_t = PERSONAL;
        printf("personal input\n");
        printf("input your birthday (dd.mm.yyyy)!\n");
        while (
            scanf("%d.%d.%d", &(book[n].stat.personal.day), &(book[n].stat.personal.month), &(book[n].stat.personal.year)) != 3 ||
            book[n].stat.personal.day < 1 || book[n].stat.personal.day > 31 ||
            book[n].stat.personal.month < 1 || book[n].stat.personal.month > 12 ||
            book[n].stat.personal.year < 1000 || book[n].stat.personal.year > 9999)
        {
            printf("try again: ");
        }
    }
    else
    {
        book[n].status_t = WORKING;
        printf("working input\n");
        printf("input organisation: ");
        status = read_string(tmp_str);
        if (status == LONG_STR)
        {
            printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
            status = SUCCESS;
        }
        strcpy(book[n].stat.working.organisation, tmp_str);

        printf("input your position: ");
        status = read_string(tmp_str);

        if (status == LONG_STR)
        {
            printf("your input string was longer than %d simbols, it was cut", MAX_STR_LEN);
            status = SUCCESS;
        }
        strcpy(book[n].stat.working.position, tmp_str);
    }

    printf("\nyour input: \n");
    print_one_abonent_t(book[n]);
    key_tbl[n].idx = n;
    strcpy(key_tbl[n].name, book[n].name);
}

void delete_line(abonent_t_book book, key_table_arr tbl, int *n)
{
    int status = SUCCESS;

    if ((*n) == 0)
        printf("EMPTY\n");
    else
    {
        int idx = read_int("input line index: ", 0, (*n) - 1);
        if (idx != (*n))
            shift(book, idx, (*n));
        (*n)--;
    }
}

void shift(abonent_t_book book, int idx, int n)
{
    // book[idx] = book[idx + 1]

    for (int i = idx; i < n - 1; i++)
    {
        strcpy(book[i].name, book[i + 1].name);
        strcpy(book[i].surname, book[i + 1].surname);
        strcpy(book[i].addres.house, book[i + 1].addres.house);
        strcpy(book[i].addres.street, book[i + 1].addres.street);
        book[i].status_t = book[i + 1].status_t;
        if (book[i].status_t == PERSONAL)
        {
            book[i].stat.personal.day = book[i + 1].stat.personal.day;
            book[i].stat.personal.month = book[i + 1].stat.personal.month;
            book[i].stat.personal.year = book[i + 1].stat.personal.year;
        }
        else
        {
            strcpy(book[i].stat.working.organisation, book[i + 1].stat.working.organisation);
            strcpy(book[i].stat.working.position, book[i + 1].stat.working.position);
        }
    }
}

int read_int(char *msg, int mn, int mx)
{
    int num = 0;
    if (mx > -1)
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
                printf("Try again. inx = [%d, %d]\n", mn, mx);
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
                break;
        } while (1);
    }

    return num;
}