#ifndef __CONST_H__
#define __CONST_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// error_codes
#define SUCCESS         0
#define MALLOC_ERR      1
#define REALLOC_ERROR   2
#define LONG_STR        3

// code commands
#define START           0
#define EXIT            1
#define TUTORIAL        2
#define ADD             3
#define DELETE          4
#define SORT_KEY_CHS    5
#define SORT_KEY_BBL    6
#define PRINT_TBL     100
#define PRINT_KEY     500

// consts
#define MAX_STR_LEN        14
#define abonent_t_CNT       5//40
#define MAX_abonent_t_CNT 100

struct addres_s
{
    char street[MAX_STR_LEN];
    char house[MAX_STR_LEN];
};

union status_u
{
    struct
    {
        int day;
        int month;
        int year;
    } personal;

    struct
    {
        char position[MAX_STR_LEN];
        char organisation[MAX_STR_LEN];
    } working;
};

struct abonent_t
{
    int idx;
    char surname[MAX_STR_LEN];
    char name[MAX_STR_LEN];
    struct addres_s addres;
    enum{PERSONAL, WORKING} status_t;
    union status_u stat;
};

struct key_s
{
    int idx;
    char name[MAX_STR_LEN];
};

typedef char string[MAX_STR_LEN+1];
typedef struct abonent_t abonent_t_book[1000];
typedef struct key_s key_table_arr[1000];
#endif