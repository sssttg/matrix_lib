#include <stdlib.h>
#include "matrix.h"

Matrix *mat_create(size_t rows, size_t cols) {
    (void)rows;
    (void)cols;
    return NULL;
}

MatStatus mat_add(const Matrix *a, const Matrix *b, Matrix **out) {
    (void)a;
    (void)b;
    if (out != NULL) {
        *out = NULL;
    }
    return MAT_ERR_NULL;
}

const char *mat_strerror(MatStatus st) {
    (void)st;
    return "TODO";
}

Matrix *mat_copy(const Matrix *m) {
    (void)m;
    return NULL;
}

void mat_free(Matrix *m) {
    (void)m;
}

void mat_set(Matrix *m, size_t i, size_t j, double value) {
    (void)m;
    (void)i;
    (void)j;
    (void)value;
}

double mat_get(const Matrix *m, size_t i, size_t j) {
    (void)m;
    (void)i;
    (void)j;
    return 0.0;
}

int mat_equal(const Matrix *a, const Matrix *b, double eps) {
    (void)a;
    (void)b;
    (void)eps;
    return 0;
}

MatStatus mat_mul(const Matrix *a, const Matrix *b, Matrix **out) {
    (void)a;
    (void)b;
    if (out != NULL) {
        *out = NULL;
    }
    return MAT_ERR_NULL;
}

MatStatus mat_transpose(const Matrix *a, Matrix **out) {
    (void)a;
    if (out != NULL) {
        *out = NULL;
    }
    return MAT_ERR_NULL;
}

MatStatus mat_read(FILE *in, Matrix **out) {
    (void)in;
    if (out != NULL) {
        *out = NULL;
    }
    return MAT_ERR_NULL;
}

MatStatus mat_load(const char *path, Matrix **out) {
    (void)path;
    if (out != NULL) {
        *out = NULL;
    }
    return MAT_ERR_NULL;
}

MatStatus mat_write(FILE *out, const Matrix *m) {
    (void)out;
    (void)m;
    return MAT_ERR_NULL;
}

MatStatus mat_save(const char *path, const Matrix *m) {
    (void)path;
    (void)m;
    return MAT_ERR_NULL;
}