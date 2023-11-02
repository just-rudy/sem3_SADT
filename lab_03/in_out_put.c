#include "consts.h"
#include "in_out_put.h"

int rand(void);
void input_by_hand(mat_t *arr);
void input_size(int *n, int *m);

void input_matrix(mat_t *arr, int *fill)
{
    printf("choose the way to input matrix\n");
    printf("1 to input by hand\n");
    printf("2 to generate it\n");
    printf("method: ");

    int method = 0;
    fflush(stdin);
    method = read_int("", 1, 2);

    int n = 0, m = 0;
    input_size(&n, &m);
    arr->row_c = n;
    arr->col_c = m;
    if (method == 0)
        return;
    else if (method == 1)
        input_by_hand(arr);
    else if (method == 2)
    {
        *fill = read_int("input fill number: ", 1, 100);
        generate_matrix(arr, *fill);
    }

//    print_regular_matrix(*arr);
}

void print_vec_col(col_v col)
{
    printf("\nur irr col:\n");
    printf("a: ");
    for (int i = 0; i < col.n; i++)
        printf("%d ", col.a[i]);
    printf("\n");
    printf("\n");

    printf("ja: ");
    for (int i = 0; i < col.n; i++)
        printf("%d ", col.ja[i]);
    printf("\n");
}

void input_array(col_t *col)
{
    int n = 0;

    printf("1 to input by hand\n2 to generate\b: ");
    int method = read_int("", 1, 2);

    n = read_int("\ninput length of columun array: ", 1, MAX_MAT_LEN);
    col->n = n;

    int fill = read_int("\ninput fill %: ", 0, 100);

    if (method == 1)
    {
        for (int i = 0; i < n; i++)
        {
            printf("el %d: ", i);
            col->arr[i] = read_int("", 0, 0);
        }
    }
    else
    {
        generate_col(col, fill);
    }
}

void print_regular_matrix(mat_t arr)
{
    printf("your matrix in regular form:\n");
    for (int i = 0; i < arr.row_c; i++)
    {
        for (int j = 0; j < arr.col_c; j++)
            printf("%d ", arr.matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

void print_irregular_matr(vec_t vec)
{
    printf("your matrix in irregular form:\n");
    printf("a: ");
    for (int i = 0; i < vec.n - 1; i++)
        printf("%d, ", vec.a[i]);
    printf("%d", vec.a[vec.n - 1]);
    printf("\n");

    printf("ja: ");
    for (int i = 0; i < vec.n - 1; i++)
        printf("%d, ", vec.ja[i]);
    printf("%d", vec.ja[vec.n - 1]);
    printf("\n");

    printf("ia: ");
    for (int i = 0; i < vec.n_ia - 1; i++)
        printf("%d, ", vec.ia[i]);
    printf("%d", vec.ia[vec.n_ia - 1]);
    printf("\n");
    printf("\n");
}

//void print_result(mat_t arr, col_t col, col_t res)
//{
//    printf("result:\n");
//    int rc = arr.row_c;
//    int cc = arr.col_c;
//    for (int i = 0; i < rc; i++)
//    {
//        for (int j = 0; j < cc; j++)
//        {
//            printf("%3d ", arr.matrix[i][j]);
//        }
//        printf(" *  %3d  =  %3d\n", col.arr[i], res.arr[i]);
//    }
//}

void print_result_res(col_t res)
{
    for (int i = 0; i < res.n; i++)
        printf("%3d\n", res.arr[i]);
}

void input_size(int *n, int *m)
{
    printf("\ninput arr size\n");
    fflush(stdin);

    *n = read_int("input rows cnt: ", 1, MAX_MAT_LEN);
    *m = read_int("input cols cnt: ", 1, MAX_MAT_LEN);
}

int read_int(char *msg, int mn, int mx)
{
    int num = 0;
    if (mx)
    {
        do
        {
            printf("%s", msg);
            if (scanf("%d", &num) != 1)
            {
                while (getchar() != '\n');
                printf("Ooops, try again\n");
            }
            else if (num < mn || num > mx)
            {
                printf("Ooops, try again\n");
            }
        }
        while (num < mn || num > mx);
    }
    else
    {
        do
        {
            printf("%s", msg);
            if (scanf("%d", &num) != 1)
            {
                while (getchar() != '\n');
                printf("Ooops, try again\n");
            }
            else
                break;
        }
        while (1);
    }

    return num;
}

void input_by_hand(mat_t *arr)
{
    printf("input %d matrix elements\n(%d rows of %d cols)\n", arr->row_c * arr->col_c, arr->row_c, arr->col_c);
    for (int i = 0; i < arr->row_c; i++)
        for (int j = 0; j < arr->col_c; j++)
        {
            printf("[%d][%d]: ", i, j);
            arr->matrix[i][j] = read_int("", 0, 0);
        }
}

void generate_matrix(mat_t *arr, int fill)
{
    int cnt = arr->row_c * arr->col_c * fill / 100;

    for (int i = 0; i < arr->row_c; i++)
        for (int j = 0; j < arr->col_c; j++)
            arr->matrix[i][j] = 0;

//    printf("%d", cnt);
    for (int i = 0; i < cnt;)
    {
        int row = rand()%arr->row_c;
        int col = rand()%arr->col_c;

        if (arr->matrix[row][col] == 0)
        {
            i++;
            arr->matrix[row][col] = rand()%10+1;
        }
    }
}

void generate_col(col_t *col, int fill)
{
    for (int i = 0; i < col->n; i++)
    {
        col->arr[i] = 0;
    }

}