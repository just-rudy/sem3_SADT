#include "input.h"
#include "commands.h"


int make_table(abonent_t_book book, int n)
{
    char *names[20] = {"Rudy", "Ross", "Lily", "Robin", "Marshall", "Barney", "Ted", "Loki", "Austin", "Ally", "Dez", "Monica", "John", "Jack", "James", "Dean", "Sam", "Jensen", "Peter", "Teo"};
    char *surns[20] = {"Moon", "Geller", "Mosby", "Stinson", "Bing", "Cooper", "Parker", "Verona", "Sherbatsky", "Erickson", "Stark", "Stratford", "Aldrin", "Tribbiany", "Winchester", "Morningstar", "Decker", "Lynch", "Garfield", "Goldfinch"};
    int date[20][3] = {{27, 12, 1955}, {26, 7, 1950}, {3, 4, 1999}, {17, 8, 1973}, {6, 11, 2003}, {3, 2, 2014}, {20, 11, 1950}, {12, 6, 2001}, {9, 1, 1996}, {2, 11, 1981}, {28, 4, 1990}, {27, 9, 1992}, {27, 11, 2010}, {24, 11, 1990}, {15, 12, 2018}, {6, 8, 2001}, {11, 7, 1993}, {26, 10, 1950}, {25, 10, 1977}, {27, 7, 2014}};
    char *organisations[11] = {"vk", "mail", "bmstu", "stud", "metro", "sonic boom", "black books", "central perk", "maclarens pub", "Lux", "Moon Band"};
    char *positions[10] = {"lead", "vice pres", "president", "host", "owner", "worker", "back vocal", "dancer", "car driver", "assistant"};
    char *streets[7] = {"Kansas", "Butovo", "Miamy", "Somethere", "Hell", "Purgatory", "LUX"};
    char *houses[7] = {"1", "2", "3B", "7", "10", "no house", "5/3"};
    int status = EXIT_SUCCESS;

    srand(time(NULL)); // Инициализация генератора случайных чисел

    for (int i = 0; i < n; i++)
    {
        // name
        book[i].idx = i;
        strcpy(book[i].name, names[rand() % 20]);
        // surname
        strcpy(book[i].surname, surns[rand() % 20]);
        // address
        strcpy(book[i].addres.street, streets[rand() % 7]);
        strcpy(book[i].addres.house, houses[rand() % 7]);
        // status (B-day or Poit)
        if (rand() % 3 != 0)
        {
            book[i].status_t = PERSONAL;
            book[i].stat.personal.day = date[i % 20][0];
            book[i].stat.personal.month = date[i % 20][1];
            book[i].stat.personal.year = date[i % 20][2];
        }
        else
        {
            book[i].status_t = WORKING;
            strcpy(book[i].stat.working.organisation, organisations[rand() % 11]);
            strcpy(book[i].stat.working.position, positions[rand() % 10]);
        }
    }
    return status;
}


/*int make_table(abonent_t_book book, int n)
{
    char *names[20] = {"Rudy", "Ross", "Lily", "Robin", "Marshall", "Barney", "Ted", "Loki", "Austin", "Ally", "Dez", "Monica", "John", "Jack", "James", "Dean", "Sam", "Jensen", "Peter", "Teo"};
    char *surns[20] = {"Moon", "Geller", "Mosby", "Stinson", "Bing", "Cooper", "Parker", "Verona", "Sherbatsky", "Erickson", "Stark", "Stratford", "Aldrin", "Tribbiany", "Winchester", "Morningstar", "Decker", "Lynch", "Garfield", "Goldfinch"};
    int date[20][3] = {{27, 12, 1955}, {26, 7, 1950}, {3, 4, 1999}, {17, 8, 1973}, {6, 11, 2003}, {3, 2, 2014}, {20, 11, 1950}, {12, 6, 2001}, {9, 1, 1996}, {2, 11, 1981}, {28, 4, 1990}, {27, 9, 1992}, {27, 11, 2010}, {24, 11, 1990}, {15, 12, 2018}, {6, 8, 2001}, {11, 7, 1993}, {26, 10, 1950}, {25, 10, 1977}, {27, 7, 2014}};
    char *organisations[11] = {"vk", "mail", "bmstu", "stud", "metro", "sonic boom", "black books", "central perk", "maclarens pub", "Lux", "Moon Band"};
    char *positions[10] = {"lead", "vice pres", "president", "host", "owner", "worker", "back vocal", "dancer", "car driver", "assistant"};
    char *streets[7] = {"Kansas", "Butovo", "Miamy", "Somethere else", "Hell", "Purgatory", "LUX"};
    char *houses[7] = {"1", "2", "3B", "7", "10", "no house", "5/3"};
    int status = SUCCESS;

    for (int i = 0; i < n; i++)
    {
        // name
        book[i].idx = i;
        strcpy(book[i].name, names[i % 20]);
        // surname
        strcpy(book[i].surname, surns[i % 20]);
        // address
        strcpy(book[i].addres.street, streets[i % 7]);
        strcpy(book[i].addres.house, houses[i % 7]);
        // status (B-day or Poit)
        if (i % 3 != 0)
        {
            book[i].status_t = PERSONAL;
            book[i].stat.personal.day = date[i%20][0];
            book[i].stat.personal.month = date[i%20][1];
            book[i].stat.personal.year = date[i%20][2];
        }
        else
        {
            book[i].status_t = WORKING;
            strcpy(book[i].stat.working.organisation, organisations[i % 11]);
            strcpy(book[i].stat.working.position, positions[i % 10]);
        }
    }
    return status;
}*/