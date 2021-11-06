#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "matrix_calc.h"

typedef struct {
    const float *matrix;
    float *sums;
    size_t n;
    size_t sum_begin;
    size_t sum_num;
} data_t;

static void *thread_routine(void *thread_data) {
    data_t *data = (data_t *)thread_data;

    if (data->sum_num == 0) {
        return NULL;
    }

    size_t diag_num = data->sum_num;
    size_t n = data->n;

    /*
        Вычисляем начало первой диагонали (с номером sum_begin)

        Например, так выглядит расположение начал диагоналей для матрицы 5x5:

            0 1 2 3 4
            * * * * 5
            * * * * 6
            * * * * 7
            * * * * 8
    */

    size_t i = 0;
    size_t left_j = n - 1;
    if (data->sum_begin < n) {
        left_j = data->sum_begin;
    } else {
        i = data->sum_begin - n + 1;
    }

    size_t right_j = left_j + diag_num;
    if (right_j > n) {
        right_j = n;
    }

    /*
        Проходим по диагоналям горизонтально

        Например, для матрицы 5x5, где sum_begin = 2, sum_num = 4:

            *  *  -> -> ->
            *  -> -> -> ->
            -> -> -> -> *
            -> -> -> *  *
            -> -> *  *  *
    */

    while (diag_num > 0 && i < n) {
        for (size_t j = left_j; j < right_j; j++) {
            data->sums[i + j] += data->matrix[i * n + j];
        }

        if (left_j > 0) {
            left_j--;
        } else {
            diag_num--;
        }

        right_j = left_j + diag_num;
        if (right_j > n) {
            right_j = n;
        }

        i++;
    }

    return NULL;
}

size_t get_sums_count(size_t n) { return n * 2 - 1; }

matrix_error_t calc_sums(float *sums, const float *matrix, size_t n) {
    if (!sums || !matrix) {
        return ERROR_NULL_POINTER;
    }

    size_t sums_num = get_sums_count(n);
    size_t diag_num = sums_num;

    memset(sums, 0, sums_num * sizeof(float));

    size_t thread_num = sysconf(_SC_NPROCESSORS_ONLN);
    size_t required_num = (n * n) / thread_num;

    pthread_t *threads = (pthread_t *)malloc(thread_num * sizeof(pthread_t));
    if (!threads) {
        return ERROR_MEMORY_ALLOCATION;
    }

    data_t *thread_data = (data_t *)malloc(thread_num * sizeof(data_t));
    if (!thread_data) {
        free(threads);
        return ERROR_MEMORY_ALLOCATION;
    }

    size_t j = 1;
    for (size_t i = 0; i < thread_num; i++) {
        thread_data[i].matrix = matrix;
        thread_data[i].sums = sums;
        thread_data[i].n = n;
        thread_data[i].sum_begin = j - 1;

        size_t picked = 0;
        while (j <= diag_num && picked < required_num) {
            if (j <= n) {
                picked += j;
            } else {
                picked += diag_num - j + 1;
            }
            j++;
        }

        thread_data[i].sum_num = j - thread_data[i].sum_begin - 1;

        int errflag = pthread_create(&threads[i], NULL, thread_routine, &thread_data[i]);
        if (errflag) {
            return ERROR_PTHREAD_CREATE;
        }
    }

    for (size_t i = 0; i < thread_num; i++) {
        int errflag = pthread_join(threads[i], NULL);
        if (errflag) {
            free(threads);
            free(thread_data);
            return ERROR_PTHREAD_JOIN;
        }
    }

    free(threads);
    free(thread_data);

    return ERROR_SUCCESS;
}
