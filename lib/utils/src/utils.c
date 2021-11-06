#include "utils.h"

static float float_rand(float min, float max) {
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

matrix_error_t generate_matrix(float *matrix, size_t n) {
    if (!matrix) {
        return ERROR_NULL_POINTER;
    }

    for (size_t i = 0; i < n * n; i++) {
        matrix[i] = float_rand(-GEN_LIMIT, GEN_LIMIT);
    }

    return ERROR_SUCCESS;
}
