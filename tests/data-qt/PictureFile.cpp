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
    auto res = PictureFile::loadFile(testPathFixture(QString("3713.png")));
    ASSERT_TRUE(res.has_value());
    EXPECT_TRUE(res.value().size() == 25382);
}

TEST_F(PictureFileTests, prepareImage_10x5) {
    auto file = PictureFile::loadFile(testPathFixture(QString("3713.png")));
    ASSERT_TRUE(file.has_value());

    auto buffer = PictureFile::prepareImage(file.value(), {10, 5});
    EXPECT_EQ(buffer.pixels.size(), 50);
    EXPECT_EQ(buffer.width, 10);
    EXPECT_EQ(buffer.height, 5);
}

TEST_F(PictureFileTests, prepareImage_1x1) {
    auto file = PictureFile::loadFile(testPathFixture(QString("3713.png")));
    ASSERT_TRUE(file.has_value());

    auto buffer = PictureFile::prepareImage(file.value(), {1, 1});
    EXPECT_EQ(buffer.pixels.size(), 1);
    EXPECT_EQ(buffer.width, 1);
    EXPECT_EQ(buffer.height, 1);
    EXPECT_EQ(buffer.pixels[0].red, 0xd4);
    EXPECT_EQ(buffer.pixels[0].green, 0xbd);
    EXPECT_EQ(buffer.pixels[0].blue, 0xba);
    EXPECT_EQ(buffer.pixels[0].alpha, 0xff);
}

TEST_F(PictureFileTests, asImage) {
    auto file = PictureFile::loadFile(testPathFixture(QString("3713.png")));
    ASSERT_TRUE(file.has_value());

    auto buffer = PictureFile::prepareImage(file.value(), {10, 5});

    auto image = PictureFile::asImage(buffer);
    EXPECT_EQ(image.width(), 10);
    EXPECT_EQ(image.height(), 5);

    // save, reload and check the picture is the same
    image.save("test-res.png");
    auto file2 = PictureFile::loadFile("test-res.png");
    ASSERT_TRUE(file.has_value());
    auto buffer2 = PictureFile::prepareImage(file2.value(), {10, 5});
    EXPECT_EQ(buffer2.width, 10);
    EXPECT_EQ(buffer2.height, 5);
    EXPECT_EQ(buffer.pixels, buffer2.pixels);
}
