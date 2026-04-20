#include <gtest/gtest.h>

#include "creator/utils/StringUtils.hpp"

// --- removeComment

TEST(StringUtilsTest, removeComment) {
    EXPECT_EQ(StringUtils::removeComment("this is a test # comment", "#"), "this is a test ");
    EXPECT_EQ(StringUtils::removeComment("this is a test", "#"), "this is a test");
    EXPECT_EQ(StringUtils::removeComment("", "#"), "");
}

TEST(StringUtilsTest, trim) {
    EXPECT_EQ(StringUtils::trim("test   "), "test");
    EXPECT_EQ(StringUtils::trim("   test"), "test");
    EXPECT_EQ(StringUtils::trim("   test   "), "test");
    EXPECT_EQ(StringUtils::trim("test"), "test");
    EXPECT_EQ(StringUtils::trim(""), "");
}
