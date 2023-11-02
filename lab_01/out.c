#include "out.h"

/*
void print_int_arr(dig_arr arr, int n)
{
    printf("\n~\n");
    for (int i = 0; i < n; i++)
        printf("{%d} - %d\n", i, arr[i]);
}

void print_float(struct ffloat *fnum)
{
    printf("mant: ");
    for (int i = 0; i < fnum->l_m; i++)
        printf("%d", fnum->mant[i]);
    printf("\n exp %d", fnum->k);
}
*/

void print_res(struct ffloat res)
{
    printf("Result: ");
    // вывод знака
    if (res.sign_m == 1)
        printf("+");
    else
        printf("-");
    
    // вывод числа
    printf("0.");

    for (int i = 0; i < res.l_m; i++)
        printf("%d", res.mant[i]);
    
    // вывод порядка
    printf(" E ");

    // знак порядка
    if (res.sign_k == 1)
        printf("+");
    else
        printf("-");
    
    // сам порядок
    printf("%d", res.k);
}                                                      