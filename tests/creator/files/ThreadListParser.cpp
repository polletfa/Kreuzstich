/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "../../Mockup.hpp"

#include "creator/files/ThreadListParser.hpp"

/**
 * For each test, test files are provided under:
 * - resources/test_files/TEST_SUITE_NAME/TEST_NAME.
 */
class ThreadListParserTests: public testing::Test, public Mockup {
protected:
    void SetUp() override {
        Mockup::SetUp();
    }
};

TEST_F(ThreadListParserTests, fileNotFound) {
    ThreadListParser parser{testPath({"file_not_found"})};
    ASSERT_FALSE(parser);
    EXPECT_TRUE(parser.error().starts_with("Cannot open file: "));
}

TEST_F(ThreadListParserTests, found) {
    ThreadListParser parser{testPath({"list.threads"})};
    ASSERT_TRUE(parser);

    auto warnings = parser.warnings();
    std::vector<std::string> expectedWarnings = {
        "Invalid line: invalid",
        "Invalid color: invalid color",
        "Invalid color: "
    };
    EXPECT_EQ(warnings, expectedWarnings);

    auto threads = parser.threads();
    EXPECT_EQ(threads.size(), 3);
    EXPECT_EQ(threads[0].name(), "thread 1");
    EXPECT_EQ(threads[0].colorString(), "012345");
    EXPECT_EQ(threads[1].name(), "thread 2, thread 3, thread 4");
    EXPECT_EQ(threads[1].colorString(), "abcdef");
    EXPECT_EQ(threads[2].name(), "thread 6");
    EXPECT_EQ(threads[2].colorString(), "112233");
}

TEST_F(ThreadListParserTests, invalidFile) {
    ThreadListParser parser{testPath({"invalid.threads"})};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error(), "Invalid file (too many errors)");
}

TEST_F(ThreadListParserTests, emptyFile) {
    ThreadListParser parser{testPath({"empty.threads"})};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error(), "Invalid file (no thread definition found)");
}
