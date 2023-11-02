#ifndef __CONSTS_H__
#define __CONSTS_H__

#include <stdio.h>
#include <string.h>
#define MAX_MANT_LEN   40  // 40
#define MAX_RESM_LEN   30  // 30
#define MAX_INT_LEN    30  // 30
#define MAX_EXP_LEN     5  // 5
#define MAX_K_NUM   99999  // 99999
#define SUCCESS         0
#define ERR_INPUT_DIG   1 // введен неверный символ
#define ERR_INPUT_LEN   2 // слишком длинное число
#define ERR_EMPTY_INPUT 3 // ничего не введено (мб это 1)
#define ERR_EXP         4
#define INT_INPUT       1
#define FLOAT_INP       0

typedef int dig_arr[MAX_MANT_LEN]; // тип массива, в котором поциферно содержатся числа

struct ffloat
{
    int sign_m;     // знак мантиссы
    dig_arr mant;  // мантисса
    int l_m;        // длина мантиссы
    int sign_k;     // знак порядка
    int k;          // порядок
};

struct iint
{
    int sign;       // знак числа
    dig_arr num;    // само число
    int l;          // длина числа
};

#endif