#include "consts.h"
#include "in.h"
#include "proccess.h"
#include "out.h"

int error_handler(int);

int main()
{
    int status = SUCCESS;
    struct ffloat fnum; // структура, содержащая действительный множитель
    struct iint inum;   // структура, содержащая целое число
    struct ffloat res;  // результат умножения

    // ввод первого множителя - действительного числа
    status = read_float(&fnum);
    
    if (!status)
    {
        // ввод второго множителя - целого числа
        status = read_int(&inum);
        if (!status)
        {
            // умножение
            status = multiply(fnum, inum, &res);
            if (!status)
                // вывод результата
                print_res(res);
        }
    }

    return error_handler(status);
}

int error_handler(int status)
{
    switch (status)
    {
    case ERR_INPUT_DIG:
        printf("ERROR: введен неверный символ");
        break;

    case ERR_INPUT_LEN:
        printf("ERROR: слишком длинный ввод");
        break;

    case ERR_EMPTY_INPUT:
        printf("ERROR: пусто");
        break;

    default:
        break;
    }
    return status;
}
