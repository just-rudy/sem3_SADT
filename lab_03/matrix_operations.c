#include "consts.h"
#include "matrix_operations.h"

void translate_to_vector(mat_t arr, vec_t *vec)
{
    int n_a = 0;
    for (int i = 0; i < arr.row_c; i++)
    {
        vec->ia[i] = n_a;
        for (int j = 0; j < arr.col_c; j++)
        {
            if (arr.matrix[i][j] != 0)
            {
                vec->a[n_a] = arr.matrix[i][j];
                vec->ja[n_a] = j;
                n_a++;
            }
        }
    }
    vec->ia[arr.row_c] = n_a; //для контроля
    vec->n = n_a;
    vec->n_ia = arr.row_c;
}

void translate_col_to_vector(col_t arr, col_v *vec)
{
    int n = 0;
    for (int i = 0; i < arr.n; i++)
        if (arr.arr[i] != 0)
        {
            vec->a[n] = arr.arr[i];
            vec->ja[n] = i;
            n++;
        }
    vec->n = n;
}

void multiply_arrays_irregular(vec_t vec, col_v col, col_t *res_i)
{
    for (int i = 0; i < vec.n_ia; i++)
    {
        int sum = 0;
        int j_col = 0;
        for (int j = vec.ia[i]; j < vec.ia[i + 1]; j++)
        {
            while (vec.ja[j] > col.ja[j_col])
                j_col++;
            if (vec.ja[j] == col.ja[j_col])
            {
                sum += vec.a[j] * col.a[j_col];
                j_col++;
            }
        }
        res_i->arr[i] = sum;
    }
    res_i->n = vec.n_ia;
}

void multiply_arrays_regular(mat_t arr, col_t col, col_t *res_r)
{
    res_r->n = arr.row_c;
    for (int i = 0; i < arr.row_c; i++)
    {
        int sum = 0;
        for (int j = 0; j < arr.col_c; j++)
            sum += arr.matrix[i][j] * col.arr[j];
        res_r->arr[i] = sum;
    }
}