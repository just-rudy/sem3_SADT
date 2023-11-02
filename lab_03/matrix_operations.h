#ifndef __TASK_H__
#define __TASK_H__

void translate_to_vector(mat_t arr, vec_t *vec);
void translate_col_to_vector(col_t col, col_v *vec);
void multiply_arrays_regular(mat_t arr, col_t col, col_t *res_r);
void multiply_arrays_irregular(vec_t vec, col_v col, col_t *res_i);

#endif