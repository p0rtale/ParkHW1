#include <gtest/gtest.h>
#include <time.h>

extern "C" {
#include "matrix_calc.h"
#include "utils.h"
}

#ifndef TIME_ITERS
#define TIME_ITERS 5
#endif

#ifndef STRESS_ITERS
#define STRESS_ITERS 5
#endif

#define RANDOM_SEED 42
#define DOUBLE_NSEC 1000000000.0
#define MATRIX_SIZE 10000

class Environment : public ::testing::Environment {
   public:
    void SetUp() override { srand(RANDOM_SEED); }
};

TEST(GetSums, NormalWork) { EXPECT_EQ(get_sums_count(10000), 19999); }

TEST(MatrixCalc, NullPointer) {
    matrix_error_t errflag = calc_sums(nullptr, nullptr, 0);
    EXPECT_EQ(errflag, ERROR_NULL_POINTER);
}

TEST(MatrixCalc, TimeMeasure) {
    size_t n = MATRIX_SIZE;
    float *matrix = (float *)malloc((n * n) * sizeof(float));
    ASSERT_NE(matrix, nullptr);

    size_t sums_num = get_sums_count(n);
    float *sums = (float *)malloc(sums_num * sizeof(float));
    if (!sums) {
        free(matrix);
        ASSERT_NE(sums, nullptr);
    }

    FILE *fp = fopen("time.txt", "w");
    if (!fp) {
        free(sums);
        free(matrix);
        ASSERT_NE(fp, nullptr);
    }

    generate_matrix(matrix, n);

    struct timespec start = {};
    struct timespec finish = {};
    double elapsed_total = 0;
    for (int t = 0; t < TIME_ITERS; t++) {
        double elapsed = 0;

        clock_gettime(CLOCK_MONOTONIC, &start);
        matrix_error_t errflag = calc_sums(sums, matrix, n);
        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / DOUBLE_NSEC;

        elapsed_total += elapsed;

        EXPECT_EQ(errflag, ERROR_SUCCESS);
    }

    fprintf(fp, "%lf\n", elapsed_total / TIME_ITERS);

    fclose(fp);
    free(sums);
    free(matrix);
}

TEST(MatrixCalc, StressTest) {
    size_t n = MATRIX_SIZE;
    float *matrix = (float *)malloc((n * n) * sizeof(float));
    ASSERT_NE(matrix, nullptr);

    size_t sums_num = get_sums_count(n);
    float *sums = (float *)malloc(sums_num * sizeof(float));
    if (!sums) {
        free(matrix);
        ASSERT_NE(sums, nullptr);
    }

    FILE *fp = fopen("report.txt", "w");
    if (!fp) {
        free(sums);
        free(matrix);
        ASSERT_NE(fp, nullptr);
    }

    for (int t = 0; t < STRESS_ITERS; t++) {
        generate_matrix(matrix, n);

        matrix_error_t errflag = calc_sums(sums, matrix, n);
        EXPECT_EQ(errflag, ERROR_SUCCESS);

        for (size_t i = 0; i < sums_num; i++) {
            fprintf(fp, "%f ", sums[i]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    free(sums);
    free(matrix);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new Environment);
    return RUN_ALL_TESTS();
}
