#include <gtest/gtest.h>

extern "C" {
#include "matrix_read.h"
}

TEST(MatrixRead, NullPointer) {
    matrix_error_t errflag = read_matrix(nullptr, nullptr, 0);
    EXPECT_EQ(errflag, ERROR_NULL_POINTER);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}