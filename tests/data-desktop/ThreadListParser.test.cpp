/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "Mockup.hpp"

#include "data-desktop/ThreadListParser.hpp"

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
    ThreadListParser parser{testPath(QString("file_not_found"))};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::ErrorCode::OPEN_FILE_ERROR);
}

TEST_F(ThreadListParserTests, found) {
    ThreadListParser parser{testPath(QString("list.threads"))};
    ASSERT_TRUE(parser);

    auto warnings = parser.warnings();
    EXPECT_EQ(warnings[0].warning, ThreadListParser::WarningCode::INVALID_LINE);
    EXPECT_EQ(warnings[0].line, QString("invalid"));
    EXPECT_EQ(warnings[1].warning, ThreadListParser::WarningCode::INVALID_COLOR);
    EXPECT_EQ(warnings[1].line, QString("thread 5: invalid color"));
    EXPECT_EQ(warnings[2].warning, ThreadListParser::WarningCode::INVALID_COLOR);
    EXPECT_EQ(warnings[2].line, QString("thread 7:"));

    auto threads = parser.threads();
    ColorSpace::ColorRGBA expectedColor[] = {{1, 0x23, 0x45}, {0xab, 0xcd, 0xef}, {0x11, 0x22, 0x33}};
    EXPECT_EQ(threads.size(), 3);
    EXPECT_EQ(threads[0].name(), "thread 1");
    EXPECT_EQ(threads[0].color(), expectedColor[0]);
    EXPECT_EQ(threads[1].name(), "thread 2, thread 3, thread 4");
    EXPECT_EQ(threads[1].color(), expectedColor[1]);
    EXPECT_EQ(threads[2].name(), "thread 6");
    EXPECT_EQ(threads[2].color(), expectedColor[2]);
}

TEST_F(ThreadListParserTests, invalidFile) {
    ThreadListParser parser{testPath(QString("invalid.threads"))};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::ErrorCode::TOO_MANY_ERRORS);
}

TEST_F(ThreadListParserTests, emptyFile) {
    ThreadListParser parser{testPath(QString("empty.threads"))};
    ASSERT_FALSE(parser);
    EXPECT_EQ(parser.error().error, ThreadListParser::ErrorCode::NO_DEFINITION_FOUND);
}
