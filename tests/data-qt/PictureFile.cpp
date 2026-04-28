/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <gtest/gtest.h>
#include "../Mockup.hpp"

#include "data-qt/PictureFile.hpp"

class PictureFileTests: public testing::Test, public Mockup {
protected:
    void SetUp() override {
        Mockup::SetUp();
    }
};

TEST_F(PictureFileTests, loadFile_notFound) {
    auto res = PictureFile::loadFile(testPath(QString("notfound")));
    ASSERT_FALSE(res.has_value());
    EXPECT_TRUE(res.error().size() > 0);
}

TEST_F(PictureFileTests, loadFile) {
    auto res = PictureFile::loadFile(testPathFixture(QString("icon32.png")));
    ASSERT_TRUE(res.has_value());
    EXPECT_TRUE(res.value().size() == 1937);
}

// TODO finish tests
