#include "matrix_calc.h"

size_t get_sums_count(size_t n) { return n * 2 - 1; }

matrix_error_t calc_sums(float *sums, const float *matrix, size_t n) {
    if (!sums || !matrix) {
        return ERROR_NULL_POINTER;
    }

    size_t sums_num = get_sums_count(n);

    for (size_t i = 0; i < sums_num; i++) {
        sums[i] = 0;
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            sums[i + j] += matrix[i * n + j];
        }
    }

    return ERROR_SUCCESS;
}
