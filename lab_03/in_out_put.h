#ifndef __IN_OUT_H__
#define __IN_OUT_H__

void input_matrix(mat_t *array, int *fill);
void input_array(col_t *column);
void print_regular_matrix(mat_t arr);
void print_irregular_matr(vec_t vec);
void print_vec_col(col_v col);
void print_result(mat_t arr, col_t col, col_t res);
void print_result_res(col_t res);
void generate_matrix(mat_t *arr, int fill);
void generate_col(col_t *col, int fill);
int read_int(char *msg, int mn, int mx);

#endif