#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_calc.h"
#include "matrix_read.h"

int main(int argc, char *argv[]) {
    char *opts = "-:n:f:o:h";

    size_t n = 0;
    char *endptr = NULL;

    char *input_filename = NULL;
    char *output_filename = NULL;
    bool use_input_file = false;
    bool use_output_file = false;

    int opt = 0;
    while ((opt = getopt(argc, argv, opts)) != -1) {
        switch (opt) {
            case 'n':
                n = strtoul(optarg, &endptr, 10);
                if (n == 0) {
                    fprintf(stderr, "Error: n must be a positive integer\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'f':
                use_input_file = true;
                input_filename = optarg;
                break;
            case 'o':
                use_output_file = true;
                output_filename = optarg;
                break;
            case 'h':
                printf(
                    "Options:\n"
                    "  -n NUMBER      number of rows and columns in the matrix (must be specified)\n"
                    "  -f FILENAME    use file for input\n"
                    "  -o FILENAME    use file for output\n"
                    "  -h             show this help\n");
                return EXIT_SUCCESS;
            case '?':
                fprintf(stderr, "Error: unknown option %c\n", optopt);
                return EXIT_FAILURE;
            case ':':
                fprintf(stderr, "Error: missing arg for %c\n", optopt);
                return EXIT_FAILURE;
        }
    }

    if (n == 0) {
        fprintf(stderr, "Error: matrix size is not specified, use -n parameter\n");
        return EXIT_FAILURE;
    }

    FILE *fp_in = stdin;
    if (use_input_file) {
        fp_in = fopen(input_filename, "r");
    }
    if (!fp_in) {
        fprintf(stderr, "Error: couldn't open the file - %s\n", input_filename);
        return EXIT_FAILURE;
    }

    float *matrix = (float *)malloc((n * n) * sizeof(float));
    if (!matrix) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    matrix_error_t errflag = ERROR_SUCCESS;

    errflag = read_matrix(fp_in, matrix, n);
    if (errflag != ERROR_SUCCESS) {
        fprintf(stderr, "Error: could not read the matrix\n");
        fclose(fp_in);
        free(matrix);
        return EXIT_FAILURE;
    }

    size_t sums_num = get_sums_count(n);
    float *sums = (float *)malloc(sums_num * sizeof(float));
    if (!sums) {
        fprintf(stderr, "Error: failed to allocate memory\n");
        fclose(fp_in);
        free(matrix);
        return EXIT_FAILURE;
    }

    errflag = calc_sums(sums, matrix, n);
    if (errflag != ERROR_SUCCESS) {
        fprintf(stderr, "Error: could not calculate the sums\n");
        fclose(fp_in);
        free(sums);
        free(matrix);
        return EXIT_FAILURE;
    }

    FILE *fp_out = stdout;
    if (use_output_file) {
        fp_out = fopen(output_filename, "w");
    }
    if (!fp_out) {
        fprintf(stderr, "Error: couldn't open the file - %s\n", output_filename);
        fclose(fp_in);
        free(sums);
        free(matrix);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < sums_num; i++) {
        fprintf(fp_out, "%f ", sums[i]);
    }
    fprintf(fp_out, "\n");

    fclose(fp_out);
    fclose(fp_in);
    free(sums);
    free(matrix);

    return EXIT_SUCCESS;
}
