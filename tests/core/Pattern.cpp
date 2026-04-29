/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <gtest/gtest.h>
#include "../Mockup.hpp"

#include "core/Pattern.hpp"
#include "data-qt/PictureFile.hpp"
#include "data-qt/ThreadListParser.hpp"

class PatternTests : public testing::Test, public Mockup {
public:
    PatternTests()
        : list({})
    {
        Mockup::SetUp();
        auto loadPicture = [this](QString filepath)->Pattern::PixelBuffer {
            if(auto res = PictureFile::loadFile(testPathFixture(filepath)); res) {
                return PictureFile::prepareImage(*res, {300, 225});
            } else {
                throw std::runtime_error{res.error().toStdString()};
            }
        };
        // load original.jpg
        original = loadPicture("original.png");
        // load selected.jpg
        selected = loadPicture("selected.png");
        // load threadlist
        ThreadListParser parser(testPathFixture(QString("list.threads")));
        list = ThreadList{parser.threads()};
    }

protected:
    Pattern::PixelBuffer original;
    Pattern::PixelBuffer selected;
    ThreadList list;
};

TEST_F(PatternTests, constructor_noSelectThreads) {
    Pattern pattern{original, list, false};
    EXPECT_EQ(pattern.get().pixels, original.pixels);
}

TEST_F(PatternTests, constructor_selectThreads) {
    Pattern pattern{original, list, true};
    EXPECT_EQ(pattern.get().pixels, selected.pixels);
}

// TODO finish tests
