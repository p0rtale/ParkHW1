#include "matrix_read.h"

#include <stdlib.h>
#include <string.h>

matrix_error_t read_matrix(FILE *fp, float matrix[], size_t n) {
    if (!fp || !matrix) {
        return ERROR_NULL_POINTER;
    }

    float *input = (float *)malloc((n * n) * sizeof(float));
    if (!input) {
        return ERROR_MEMORY_ALLOCATION;
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            int res = fscanf(fp, "%f", &input[i * n + j]);
            if (res == EOF) {
                free(input);
                return ERROR_STREAM;
            }
        }
    }

    if (ferror(fp)) {
        free(input);
        return ERROR_STREAM;
    }

    memcpy(matrix, input, (n * n) * sizeof(float));

    free(input);

    return ERROR_SUCCESS;
}
