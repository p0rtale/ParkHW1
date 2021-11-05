#include <gtest/gtest.h>

extern "C" {
#include <math.h>
}

#define EPS 1e-4

TEST(CompareReports, CompareReports) {
    FILE *fp_consistent = fopen("data_consistent/report.txt", "r");
    ASSERT_NE(fp_consistent, nullptr);

    FILE *fp_parallel = fopen("data_parallel/report.txt", "r");
    if (!fp_parallel) {
        fclose(fp_consistent);
        ASSERT_NE(fp_parallel, nullptr);
    }

    bool compare_result = true;
    float value_consistent = 0;
    float value_parallel = 0;
    while (fscanf(fp_consistent, "%f", &value_consistent) != EOF &&
           fscanf(fp_parallel, "%f", &value_parallel) != EOF) {
        if (fabs(value_consistent - value_parallel) > EPS) {
            compare_result = false;
            break;
        }
    }
    if (ferror(fp_consistent) || ferror(fp_parallel)) {
        fclose(fp_parallel);
        fclose(fp_consistent);
        ASSERT_EQ(ferror(fp_consistent), 0);
        ASSERT_EQ(ferror(fp_parallel), 0);
    }

    EXPECT_EQ(compare_result, true);

    fclose(fp_parallel);
    fclose(fp_consistent);
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
