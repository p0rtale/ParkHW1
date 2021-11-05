#pragma once

#include <stdio.h>

#include "errors.h"

matrix_error_t read_matrix(FILE *fp, float matrix[], size_t n);
