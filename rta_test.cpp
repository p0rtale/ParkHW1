#include <gtest/gtest.h>

extern "C" {
    #include "roman_to_arabic.h"
}

TEST(RTA_TEST, SimpleTest) {
    const char *s = "VI";
    int res = 0;
    translate_roman_to_arabic(s, &res);
    EXPECT_EQ(res, 6);
}

TEST(RTA_TEST, AnotherSimpleTest) {
    const char *s = "MDXCVIII";
    int res = 0;
    translate_roman_to_arabic(s, &res);
    EXPECT_EQ(res, 1598);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
