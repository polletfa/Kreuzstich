/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "../Mockup.hpp"

#include "data-qt/ThreadListParser.hpp"

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
    ThreadListParser parser{qTestPath({"file_not_found"})};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::Error::OPEN_FILE_ERROR);
}

TEST_F(ThreadListParserTests, found) {
    ThreadListParser parser{qTestPath({"list.threads"})};
    ASSERT_TRUE(parser);

    auto warnings = parser.warnings();
    EXPECT_EQ(warnings[0].warning, ThreadListParser::Warning::INVALID_LINE);
    EXPECT_EQ(warnings[0].line, QString("invalid"));
    EXPECT_EQ(warnings[1].warning, ThreadListParser::Warning::INVALID_COLOR);
    EXPECT_EQ(warnings[1].line, QString("thread 5: invalid color"));
    EXPECT_EQ(warnings[2].warning, ThreadListParser::Warning::INVALID_COLOR);
    EXPECT_EQ(warnings[2].line, QString("thread 7:"));

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
    ThreadListParser parser{qTestPath({"invalid.threads"})};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::Error::TOO_MANY_ERRORS);
}

TEST_F(ThreadListParserTests, emptyFile) {
    ThreadListParser parser{qTestPath({"empty.threads"})};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::Error::NO_DEFINITION_FOUND);
}
