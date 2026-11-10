#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>  /* size_t */
#include <stdio.h>   /* FILE   */

/*
 * Матрица rows x cols. Элементы лежат ОДНИМ массивом построчно (row-major):
 * элемент (i, j) находится в data[i * cols + j], индексы с нуля.
 *
 * Правило владения:
 *   - создаёт матрицу только mat_create (или функции, которые её вызывают);
 *   - освобождает только mat_free;
 *   - кто получил матрицу через out-параметр (Matrix **out), тот её и освобождает.
 */
typedef struct {
    size_t rows;
    size_t cols;
    double *data;
} Matrix;

/* Коды результата. 0 — успех, остальное — ошибка. */
typedef enum {
    MAT_OK = 0,
    MAT_ERR_NULL,    /* вместо матрицы/указателя передан NULL            */
    MAT_ERR_ALLOC,   /* malloc/calloc вернул NULL                        */
    MAT_ERR_DIM,     /* размеры не подходят для операции                 */
    MAT_ERR_IO,      /* не удалось открыть / прочитать / записать файл   */
    MAT_ERR_FORMAT   /* файл прочитался, но данные в нём некорректны     */
} MatStatus;

/* Человекочитаемое описание ошибки (строковый литерал, освобождать не нужно). */
const char *mat_strerror(MatStatus st);

/* ---------- Жизненный цикл ---------- */

/* Матрица из нулей. NULL, если rows == 0, cols == 0 или не хватило памяти.
 * Подумай: что будет, если rows * cols переполнит size_t? */
Matrix *mat_create(size_t rows, size_t cols);

/* Освобождает data и саму структуру. mat_free(NULL) — ничего не делает. */
void mat_free(Matrix *m);

/* Глубокая копия (новый массив data). NULL при ошибке.
 * Пригодится на шаге 2: Гаусс портит матрицу, работать будем с копией. */
Matrix *mat_copy(const Matrix *m);

/* ---------- Доступ к элементам ---------- */

/* Внутри поставь assert на границы: i < rows, j < cols. */
double mat_get(const Matrix *m, size_t i, size_t j);
void   mat_set(Matrix *m, size_t i, size_t j, double value);

/* ---------- Операции ----------
 * Результат — НОВАЯ матрица в *out (её освобождает вызывающий).
 * При любой ошибке: *out == NULL и ничего не утекает. */

MatStatus mat_add(const Matrix *a, const Matrix *b, Matrix **out);       /* a + b   */
MatStatus mat_mul(const Matrix *a, const Matrix *b, Matrix **out);       /* a * b   */
MatStatus mat_transpose(const Matrix *a, Matrix **out);                  /* a^T     */

/* ---------- Сравнение (для тестов) ----------
 * 1, если размеры совпадают и |a_ij - b_ij| <= eps для всех элементов, иначе 0.
 * double никогда не сравниваем через ==. */
int mat_equal(const Matrix *a, const Matrix *b, double eps);

/* ---------- Ввод / вывод ----------
 * Формат (пробелы и переводы строк — любые):
 *   2 3
 *   1 2 3
 *   4 5 6
 * mat_read/mat_write работают с любым FILE*: файлом, stdin, stdout. */

MatStatus mat_read(FILE *in, Matrix **out);
MatStatus mat_write(FILE *out, const Matrix *m);
MatStatus mat_load(const char *path, Matrix **out);   /* fopen + mat_read + fclose  */
MatStatus mat_save(const char *path, const Matrix *m);/* fopen + mat_write + fclose */

/* ---------- Дальше (НЕ шаг 1, только чтобы видеть направление) ----------
 * Шаг 2: MatStatus mat_det(const Matrix *a, double *det);
 *        MatStatus mat_rank(const Matrix *a, size_t *rank);
 * Шаг 3: MatStatus mat_inverse(const Matrix *a, Matrix **out);
 *        MatStatus mat_solve(const Matrix *a, const Matrix *b, ...);
 */

#endif /* MATRIX_H */
