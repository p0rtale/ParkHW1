#pragma once

#include <stdio.h>

#include "errors.h"

size_t get_sums_count(size_t n);
matrix_error_t calc_sums(float *sums, const float *matrix, size_t n);
