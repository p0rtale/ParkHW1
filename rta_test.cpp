#include <gtest/gtest.h>

extern "C" {
    #include "roman_to_arabic.h"
}

TEST(NORMAL_WORK, OneRomanDigit) {
    int res = 0;
    EXPECT_EQ(translate_roman_to_arabic("L", &res), 0);
    EXPECT_EQ(res, 50);
}

TEST(NORMAL_WORK, FewRomanDigits) {
    int res = 0;
    EXPECT_EQ(translate_roman_to_arabic("MDXCVIII", &res), 0);
    EXPECT_EQ(res, 1598);
}

TEST(ERROR_WORK, NotRomanNumber) {
    int res = 0;
    EXPECT_EQ(translate_roman_to_arabic("LVI3I", &res), -1);
}

TEST(ERROR_WORK, NullPointer) {
    int res = 0;
    EXPECT_EQ(translate_roman_to_arabic(NULL, &res), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
