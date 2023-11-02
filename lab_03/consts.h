#ifndef __CONST_H__
#define __CONST_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_MAT_LEN 120

typedef struct
{
    int matrix[MAX_MAT_LEN][MAX_MAT_LEN];
    int row_c;
    int col_c;
} mat_t;

typedef struct
{
    int n;
    int n_ia;
    int a[MAX_MAT_LEN * MAX_MAT_LEN];
    int ja[MAX_MAT_LEN * MAX_MAT_LEN];
    int ia[MAX_MAT_LEN];
} vec_t;

typedef struct
{
    int n;
    int a[MAX_MAT_LEN];
    int ja[MAX_MAT_LEN];
} col_v;

typedef struct
{
    int n;
    int arr[MAX_MAT_LEN];
} col_t;

#endif