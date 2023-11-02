#include "in.h"

void print_invite(int type);
// void to_norm(struct ffloat *fnum);

int read_float(struct ffloat *fnum)
{
    int status = SUCCESS;
    int sgn_m = 1, sgn_k = 1;                           // знаки числа и порядка. по умолчанию положительные
    int if_dot = 0, if_e = 0, if_not_zero = 0;          // флаги наличия порядка и точки и ненулевых символов до точки
    int ln_m = 0, ln_dot = 0, ln_k = 0, len = 0;        // длина мантиссы, части числа после точки, порядка и числа в целом
    int k = 0;                                          // для умножения на 10 и счета порядка (из-за ограничения в 5 символов он хранится в инт)
    char dig;
    print_invite(FLOAT_INP);

    while (!status && scanf("%c", &dig) == 1 && dig != '\n' && dig != '\0' && ln_m <= MAX_MANT_LEN && ln_k <= MAX_EXP_LEN)
    {
        if (dig == '-' || dig == '+')
        {
            if (len == 0)
                if (dig == '-')
                    sgn_m = -1;
                else
                    sgn_m = 1;
            else if (if_e == len)
                if (dig == '-')
                    sgn_k = -1;
                else
                    sgn_k = 1;
            else
                status = ERR_INPUT_DIG;
        }
        else if (dig == 'E' || dig == 'e')
            if (!if_e)
                if_e = len;
            else
                status = ERR_INPUT_DIG;
        else if (dig == '.')
            if (!if_dot && !if_e) // порядок - обязательно целое число => точка может быть до Е
                if_dot = 1;
            else
                status = ERR_INPUT_DIG;
        else if (dig <= '9' && dig >= '0')
            if (if_e && ln_k < MAX_EXP_LEN) // после е => ввод порядка
            {
                k = k * 10 + (dig - '0');
                ln_k++;
                len++;
            }
            else if (!if_e && len < MAX_MANT_LEN) // до e => ввод самого числа
            {
                if (dig != '0')
                    if_not_zero = 1;
                fnum->mant[len++] = dig - '0';
                if (!if_dot && (dig != '0' || (dig == '0' && if_not_zero))) // до точки
                    ln_dot++;
                ln_m++;
            }
            else
                status = ERR_INPUT_LEN;
        else if (isspace(dig))
            ; // чтобы пробелы не влияли на общую длину числа
        else
            status = ERR_INPUT_DIG;
    }
    if (!status)
    {

        fnum->sign_m = sgn_m;
        fnum->l_m = ln_m;
        int tmp_k = k * sgn_k + ln_dot;
        if (tmp_k < 0)
        {
            fnum->k = tmp_k * (-1);
            fnum->sign_k = -1;
        }
        else
        {
            fnum->k = tmp_k;
            fnum->sign_k = 1;
        }

    }

    // нормализовать порядок - перенести точку в начало
    //to_norm(fnum);

    return status;
}

int read_int(struct iint *inum)
{
    int status = SUCCESS;
    int sign = 1, len = 0; // по умолчанию число положительное
    char dig;

    print_invite(INT_INPUT);
    while (!status && scanf("%c", &dig) == 1 && dig != '\n' && dig != '\0')
    {
        // if (len == MAX_INT_LEN && dig <= '9' && dig >= '0')
        //     status = ERR_INPUT_LEN;
        if (dig == '-' && len == 0)
            sign = -1;
        else if (dig == '+' && len == 0)
            sign = 1;
        else if (dig <= '9' && dig >= '0')
            if (len < MAX_INT_LEN)
                inum->num[len++] = dig - '0';
            else
                status = ERR_INPUT_LEN;
        else if (isspace(dig))
            ;
        else
            status = ERR_INPUT_DIG;
    }

    if (len > 0)
    {
        inum->l = len;
        inum->sign = sign;
    }
    else
        status = ERR_EMPTY_INPUT;
    return status;
}

// void to_norm(struct ffloat *fnum)
// {
//     int i = 0;
//     while (fnum->mant[i++] == 0)
//     {
//         fnum->l_m--;
//         fnum->k--;
//     }
// }

void print_invite(int type) // 1 - int 0 - float0 pvg[g b2.3/.;]
{
    if (type == INT_INPUT)
    {
        printf("Введите второй множитель, следуя правилам:\n");
        printf("1. Вводите ТОЛЬКО десятичные цифры\n");
        printf("|- В начале числа может быть знак +/-\n");
        printf("|- Если в начале числа больше одного знака +/-, то применится последний введенный\n");
        printf("|- Ввод порядка, точки или зяпятой недопустим\n");
        printf("'- Все пробелы во время ввода игнорируются\n");
        printf("2. Число не должно быть длиннее 30 символов\n");
        printf("|- Если при вводе число начинается с незначащих нулей, то они входят в общую длину числа\n");
        printf("'- Т.е. число '012' в программе будет считаться как 12, но иметь длину 3\n");
        printf("       +1-------10--------20--------30\n");
        printf("        |---|----|----|----|----|----|\n");
        printf("Число: ");
    }
    else
    {
        printf("Введите первый множитель, следуя правилам:\n");
        printf("1. Для мантиссы и порядка вводите ТОЛЬКО десятичные цифры\n");
        printf("|- В начале числа и в начале порядка может быть ОДИН знак +/-\n");
        printf("'- В качестве разделителя десятичной части используйте точку .\n");
        printf("2. Порядок - ЦЕЛОЕ число\n");
        printf("'- Для ввода порядка используйте E или e\n");
        printf("3. Все пробелы во время ввода игнорируются\n");
        printf("4. Мантисса не должна быть длиннее 40 символов, порядок - 5\n");
        printf("-> Примеры корректного ввода: 1e10 +4.5E3\n");
        printf("       +1-------10--------20--------30--------40+1---5\n");
        printf("        |---|----|----|----|----|----|---------|-|---|\n");
        printf("Число: ");
    }
}