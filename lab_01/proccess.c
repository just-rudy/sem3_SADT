#include "consts.h"
#include "proccess.h"
#include "out.h"

void reverse_del_zero(dig_arr arr, int *n);
void swap(int *, int *);
void mult_by_digit(dig_arr tmp, dig_arr fnum, int n, int num, int shift);
void initiallize_arr_with_0(dig_arr arr, int n);
void normalize_summs(dig_arr tmp, int *len);
int get_norm_res(struct ffloat *res, dig_arr tmp, int len, struct ffloat fnum, int sign_int);
void rnd(dig_arr arr, int n);
void shift(dig_arr arr, int n);

int multiply(struct ffloat fnum, struct iint inum, struct ffloat *res)
{
    int status = SUCCESS;
    int tmp[MAX_MANT_LEN * 2]; // массив для хранения произведения
    
    reverse_del_zero(fnum.mant, &fnum.l_m);        // перевернутая мантисса для удобства вынесения новых разрядов в начало числа
    reverse_del_zero(inum.num, &inum.l);           // перевернутое число нужно из тех же соображений
    initiallize_arr_with_0(tmp, MAX_MANT_LEN * 2); // массив, в котором будут суммы произведений, надо обнулить

    int len = fnum.l_m + inum.l - 1;

    // последовательное умножение действительного числа на каждую цифру целого
    for (int i = 0; i < inum.l; i++)
    {
        mult_by_digit(tmp, fnum.mant, fnum.l_m, inum.num[i], i);
        // print_int_arr(tmp, MAX_MANT_LEN * 2);
    }

    normalize_summs(tmp, &len);
    // print_int_arr(tmp, len);

    status = get_norm_res(res, tmp, len, fnum, inum.sign);
    return status;
}

void reverse_del_zero(dig_arr arr, int *n)
{
    int cnt_zero = 0;
    int i = 0;
    while (arr[i] == 0 && i < (*n))
    {
        cnt_zero++;
        i++;
    }
    // printf("zero: %d\ni: %d\nlen: %d\n", cnt_zero, i, (*n));

    for (i = 0; i < (*n) / 2; i++)
        swap(&arr[i], &arr[(*n) - i - 1]);

    if (cnt_zero == (*n))
        (*n) = 1;
    else
        (*n) -= cnt_zero;
}

void swap(int *n1, int *n2)
{
    int n3 = *n1;
    *n1 = *n2;
    *n2 = n3;
}

void mult_by_digit(dig_arr tmp, dig_arr fnum, int n, int num, int shift)
{
    for (int i = 0; i < n; i++)
        tmp[i + shift] += fnum[i] * num;
}

void initiallize_arr_with_0(dig_arr arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = 0;
}

void normalize_summs(dig_arr arr, int *len)
{
    int i = 0;
    while (i < *len - 1)
    {
        if (arr[i] >= 10)
        {
            arr[i + 1] += arr[i] / 10;
            arr[i] = arr[i] % 10;
        }
        i++;
    }
    if (arr[(*len) - 1] >= 10)
    {
        arr[i + 1] += arr[i] / 10;
        arr[i] = arr[i] % 10;
        (*len)++;
    }
}

void shift(dig_arr arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
        // print_int_arr(arr, n);
    }

    arr[n - 1] = 0;
}

void rnd(dig_arr arr, int n)
{
    int ten = 0;

    if (arr[0] >= 5)
    {
        ten = 1;
        for (int i = 1; i < n && ten == 1; i++)
        {
            arr[i] += ten;
            if (arr[i] >= 10)
                ten = 1;
            else
                ten = 0;
        }
    }
    shift(arr, n);
}

int get_norm_res(struct ffloat *res, dig_arr tmp, int len, struct ffloat fnum, int sign_int)
{
    int status = SUCCESS;
    (*res) = fnum;
    res->sign_m = fnum.sign_m * sign_int;

    // если есть переход в целую часть типа 0.1 * 200 = 20.0 -> 0.2e+2
    if (len > fnum.l_m)
        res->k += (len - fnum.l_m);

    // если мантисса слишком длинная
    while (len > MAX_RESM_LEN)
    {
        rnd(tmp, len);
        len--;
    }

    // если порядок стал слишком длинным
    if (res->k > MAX_K_NUM)
        status = ERR_EXP;

    // print_int_arr(tmp, len);
    res->l_m = len;

    for (int i = 0; i < len; i++)
        res->mant[i] = tmp[len - i - 1];

    return status;
}