#include "consts.h"
#include "in_out_put.h"
#include "matrix_operations.h"
#include "time_mem_measure.h"

int main()
{
    srand(0);

    long long int beg = 0, end = 0, time_reg = 0, time_irr = 0;

    printf("hello! let's start\n\n");

    printf("if you want to see only the results of time'n'mem measure experiment, then input 0\n"
           "(else input anything else)\n: ");

    int method = 0;
    if (scanf("%d", &method) == 1 && method == 0)
    {
        measure_time_experiment();
        return 0;
    }

    mat_t arr = {};
    vec_t vec = {};
    col_v col_vec = {};
    int fill = 0; // процент заполнения матрицы

    // а нужен ли мне тут вообще fill? для замера времени

    input_matrix(&arr, &fill);
    translate_to_vector(arr, &vec);

    print_regular_matrix(arr);
    print_irregular_matr(vec);

    //количество столбцов матрицы = количеству "строк" вектора-столбца
    col_t col = {}, res_r = {}, res_i = {};
    input_array(&col);
    translate_col_to_vector(col, &col_vec);
    printf("your regular col:\n");
    for (int i = 0; i < col.n; i++)
        printf("%d\n", col.arr[i]);

    print_vec_col(col_vec);

    if (arr.col_c != col.n)
    {
        printf("error in your arrays sizes\ncolumn cnt in matrix = 'row' cnt in vector-column\n");
        return 1;
    }

    // умножить обычную матрицу на столбец
    beg = time_now();
    multiply_arrays_regular(arr, col, &res_r);
    end = time_now();
    time_reg = end - beg;
    printf("\nres reg:\n");
    print_result_res(res_r);

    // умножить необычную матрицу на столбец
    beg = time_now();
    multiply_arrays_irregular(vec, col_vec, &res_i);
    end = time_now();
    time_irr = end - beg;
    printf("\nres irregular:\n");
    print_result_res(res_i);
    printf("\n");
    printf("Your time info: \n");
    printf("For   regular: %lld ms\n", time_reg);
    printf("For irregular: %lld ms\n", time_irr);
    printf("bye!");
}