/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>
#include "Mockup_QStandardPathsWrapper.hpp"

#include "creator/files/FileLocator.hpp"

/**
 * For each test, test files are provided under:
 * - resources/test_file/TEST_SUITE_NAME/TEST_NAME.
 */
class FileLocatorTests: public testing::Test {
protected:
    std::shared_ptr<Mockup_QStandardPathsWrapper> mockStandardPaths{std::make_shared<Mockup_QStandardPathsWrapper>()};
    FileLocator locator{mockStandardPaths};

    void SetUp() override {
        mockStandardPaths->SetUp();
    }
};

TEST_F(FileLocatorTests, findConfigFile_firstDir) {
    auto res = locator.findConfigFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), TEST_FILES "/FileLocatorTests/findConfigFile_firstDir/test/path/1/config.xml");
}

TEST_F(FileLocatorTests, findConfigFile_secondDir) {
    auto res = locator.findConfigFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), TEST_FILES "/FileLocatorTests/findConfigFile_secondDir/another/test/path/config.xml");
}

TEST_F(FileLocatorTests, findConfigFile_notfound) {
    auto res = locator.findConfigFile();
    EXPECT_EQ(res.has_value(), false);
}

TEST_F(FileLocatorTests, findStateFile_firstDir) {
    auto res = locator.findStateFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), TEST_FILES "/FileLocatorTests/findStateFile_firstDir/test/path/1/state.xml");
}

TEST_F(FileLocatorTests, findStateFile_secondDir) {
    auto res = locator.findStateFile();
    ASSERT_TRUE(res.has_value());
    EXPECT_EQ(res.value(), TEST_FILES "/FileLocatorTests/findStateFile_secondDir/another/test/path/state.xml");
}

TEST_F(FileLocatorTests, findStateFile_notfound) {
    auto res = locator.findStateFile();
    EXPECT_EQ(res.has_value(), false);
}

TEST_F(FileLocatorTests, findThreadLists) {
    auto res = locator.findThreadLists();
    std::vector<std::string> expected = {
        TEST_FILES "/FileLocatorTests/findThreadLists/test/path/1/file1.threads",
        TEST_FILES "/FileLocatorTests/findThreadLists/another/test/path/file1.threads",
        TEST_FILES "/FileLocatorTests/findThreadLists/another/test/path/file2.threads",
        TEST_FILES "/FileLocatorTests/findThreadLists/one/more/path/file2.threads"
    };
    EXPECT_EQ(res, expected);
}

TEST_F(FileLocatorTests, getPathForWritableConfigFile) {
    EXPECT_EQ(locator.getPathForWritableConfigFile(), TEST_FILES "/FileLocatorTests/getPathForWritableConfigFile/test/path/1/config.xml");
}

TEST_F(FileLocatorTests, getPathForWritableStateFile) {
    EXPECT_EQ(locator.getPathForWritableStateFile(), TEST_FILES "/FileLocatorTests/getPathForWritableStateFile/test/path/1/state.xml");
}

TEST_F(FileLocatorTests, getPathForWritableThreadListFile) {
    EXPECT_EQ(locator.getPathForWritableThreadListFile("myList"), TEST_FILES "/FileLocatorTests/getPathForWritableThreadListFile/test/path/1/myList.threads");
}
