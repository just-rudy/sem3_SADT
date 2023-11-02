#include "../inc/commands.h"

int read_string(string str)
{
    int status = SUCCESS;
    int ch = 0, i = 0;
    // ch=getchar();
    // printf("char is %c %d\n", ch, ch);
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

void print_tutorial()
{
    printf("Command:\n");
    printf("1 to exit\n");
    printf("2 to read tutorial again\n");
    printf("3 for adding new abonent\n");
    printf("4 for deleting abonent\n");
    printf("5 for creating key table\n");
    printf("6 for sorting key by bubble\n");
//    printf("7 for sorting key by choice\n");
    printf("100 to print abonenet book\n");
    printf("500 to print key_table\n");
}

void print_one_abonent(struct abonent person)
{
    printf("name:    %s\n", person.name);
    printf("surname: %s\n", person.surname);
    printf("address:\n  {\n");
    printf("   street: %s\n", person.addres.street);
    printf("   house:  %s\n", person.addres.house);
    printf("  }\n");
    if (person.status_t == PERSONAL)
        printf("BDay: %d.%d.%d\n", person.stat.personal.day, person.stat.personal.month, person.stat.personal.year);
    else
    {
        printf("Work status:\n  {\n");
        printf("   organisation: %s\n", person.stat.working.organisation);
        printf("   role:         %s\n", person.stat.working.position);
        printf("  }\n");
    }
    printf("}\n");
    printf("\n");
}

void print_book(abonent_book book, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("(%d):\n{\n", i);
        print_one_abonent(book[i]);
    }
}

void add_line(abonent_book book, int n)
{
    int status = SUCCESS;
    string tmp_str;
    char c;
    
    // name
    printf("input name: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than 25 simbols, it was cut");
        status = SUCCESS;
    }
    strcpy(book[n].name, tmp_str);

    // surname
    printf("input surname: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than 25 simbols, it was cut");
        status = SUCCESS;
    }
    strcpy(book[n].surname, tmp_str);

    // address
    // street
    printf("input you home addres\nstart with your street: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than 25 simbols, it was cut");
        status = SUCCESS;
    }
    strcpy(book[n].addres.street, tmp_str);

    // house
    printf("and your house: ");
    status = read_string(tmp_str);
    if (status == LONG_STR)
    {
        printf("your input string was longer than 25 simbols, it was cut");
        status = SUCCESS;
    }
    strcpy(book[n].addres.house, tmp_str);

    // status
    printf("for personal input 0 else input 1: ");
    int tmp_int = 0; 
    while (scanf("%d%c", &tmp_int, &c) != 2  && c == '\n' || (tmp_int != 0 && tmp_int != 1))
        printf("try again: ");
    // printf("name: %d\n", tmp_int);

    if (tmp_int == 1)
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
            printf("your input string was longer than 25 simbols, it was cut");
            status = SUCCESS;
        }
        strcmp(book[n].stat.working.organisation, tmp_str);

        printf("input your position: ");
        status = read_string(tmp_str);

        if (status == LONG_STR)
        {
            printf("your input string was longer than 25 simbols, it was cut");
            status = SUCCESS;
        }
        strcmp(book[n].stat.working.position, tmp_str);
    }

    printf("\nyour input: \n");
    print_one_abonent(book[n]);
}

int delete_line(abonent_book book, int n)
{
    int status = SUCCESS;
    printf("input line index: ");
    int idx = 0;
    while (scanf("%d\n", &idx) != 1 || idx > (n) || idx < 0)
        printf("try again. input line index less than %d, grater than 0: ", (n));
    return status;
}