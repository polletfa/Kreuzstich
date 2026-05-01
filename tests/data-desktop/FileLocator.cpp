/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>
#include "Mockup_QStandardPathsWrapper.hpp"

#include "data-desktop/FileLocator.hpp"

#include <iostream>
/**
 * For each test, test files are provided under:
 * - resources/test_files/TEST_SUITE_NAME/TEST_NAME.
 */
class FileLocatorTests: public testing::Test, public Mockup {
protected:
    std::shared_ptr<Mockup_QStandardPathsWrapper> mockStandardPaths{std::make_shared<Mockup_QStandardPathsWrapper>()};
    FileLocator locator{mockStandardPaths};

    void SetUp() override {
        Mockup::SetUp();
        mockStandardPaths->SetUp();
    }
};

TEST_F(FileLocatorTests, findConfigFile_firstDir) {
    auto res = locator.findConfigFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), testPath(QString("test/path/1/config.xml")));
}

TEST_F(FileLocatorTests, findConfigFile_secondDir) {
    auto res = locator.findConfigFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), testPath(QString("another/test/path/config.xml")));
}

TEST_F(FileLocatorTests, findConfigFile_notfound) {
    auto res = locator.findConfigFile();
    EXPECT_EQ(res.has_value(), false);
}

TEST_F(FileLocatorTests, findStateFile_firstDir) {
    auto res = locator.findStateFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), testPath(QString("test/path/1/state.xml")));
}

TEST_F(FileLocatorTests, findStateFile_secondDir) {
    auto res = locator.findStateFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), testPath(QString("another/test/path/state.xml")));

}

TEST_F(FileLocatorTests, findStateFile_notfound) {
    auto res = locator.findStateFile();
    EXPECT_EQ(res.has_value(), false);
}

TEST_F(FileLocatorTests, findThreadLists) {
    auto res = locator.findThreadLists();
    QStringList expected = {
        testPath(QString("test/path/1/file1.threads")),
        testPath(QString("another/test/path/file1.threads")),
        testPath(QString("another/test/path/file2.threads")),
        testPath(QString("one/more/path/file2.threads"))
    };
    EXPECT_EQ(res, expected);
}

TEST_F(FileLocatorTests, getPathForWritableConfigFile) {
    EXPECT_EQ(locator.getPathForWritableConfigFile(), testPath(QString("test/path/1/config.xml")));
}

TEST_F(FileLocatorTests, getPathForWritableStateFile) {
    EXPECT_EQ(locator.getPathForWritableStateFile(), testPath(QString("test/path/1/state.xml")));
}

TEST_F(FileLocatorTests, getPathForWritableThreadListFile) {
    EXPECT_EQ(locator.getPathForWritableThreadListFile("myList"), testPath(QString("test/path/1/myList.threads")));
}
