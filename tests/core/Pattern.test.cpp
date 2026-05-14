
/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <gtest/gtest.h>
#include "Mockup.hpp"

#include "core/Pattern.hpp"
#include "data-desktop/PictureFile.hpp"
#include "data-desktop/ThreadListParser.hpp"

class PatternTests : public testing::Test, public Mockup {
public:
    PatternTests()
        : list({})
    {
        Mockup::SetUp();
        // load original.jpg
        original = loadPicture(testPathFixture(QString("original.png")), {300, 225});
        // load selected.jpg
        selected = loadPicture(testPathFixture(QString("selected.png")));
        // load threadlist
        ThreadListParser parser(testPathFixture(QString("list.threads")));
        list = ThreadList{parser.threads()};
    }

protected:
    Pattern::PixelBuffer original;
    Pattern::PixelBuffer selected;
    ThreadList list;

    Pattern::PixelBuffer loadPicture(QString filepath, QSize resize = {0, 0}) {
        if(auto res = PictureFile::loadFile(filepath); res) {
            return PictureFile::prepareImage(*res, resize);
        } else {
            throw std::runtime_error{res.error().toStdString()};
        }
    };
};

TEST_F(PatternTests, constructor_noSelectThreads) {
    Pattern pattern{original, list, false};
    EXPECT_EQ(pattern.get().pixels, original.pixels);
}

TEST_F(PatternTests, constructor_selectThreads) {
    Pattern pattern{original, list, true};
    EXPECT_EQ(pattern.get().pixels, selected.pixels);
}

TEST_F(PatternTests, get) {
    Pattern pattern(selected, list, false);
    auto buffer = pattern.get();
    EXPECT_EQ(buffer.width, 300);
    EXPECT_EQ(buffer.height, 225);
    EXPECT_EQ((pattern[10,5]), buffer.pixels[5*300 + 10]);
    EXPECT_EQ((pattern[100,75]), buffer.pixels[75*300 + 100]);
}

TEST_F(PatternTests, grid) {
    Pattern pattern(selected, list, false);
    auto image = loadPicture(testPath(QString("grid.png")));
    EXPECT_EQ(image.width, pattern.grid().width);
    EXPECT_EQ(image.height, pattern.grid().height);
    EXPECT_EQ(image.pixels, pattern.grid().pixels);
}

TEST_F(PatternTests, computeUsage_fullPic) {
    Pattern pattern(selected, list, false);
    pattern.select(); // not necessary since this is the default, but we want to check that select
                      // without parameter does select the whole picture

    const auto& usage = pattern.computeUsage();
    size_t count{0};
    for(const auto& item: usage) {
        count += item.second;
    }
    EXPECT_EQ(count, pattern.get().width * pattern.get().height);
    EXPECT_EQ(usage.size(), pattern.threadList().get().size());

    // Note: we don't check the exact content of usage, but it will be indirectly at least partially done
    //       by other tests where we use usage to select a color (replacePixel or replaceThread for example)
}

TEST_F(PatternTests, computeUsage_area) {
    Pattern pattern(selected, list, false);
    pattern.select({10, 5, 3, 3});

    const auto& usage = pattern.computeUsage();
    size_t count{0};
    for(const auto& item: usage) {
        count += item.second;
    }
    EXPECT_EQ(count, 3*3);
    EXPECT_EQ(usage.size(), pattern.threadList().get().size());
}

TEST_F(PatternTests, replacePixel) {
    Pattern pattern(selected, list, false);
    auto usage = pattern.threadList().usage();

    // find a pixel with the color from usage[0]
    bool found = false;
    for(size_t x = 0; x < pattern.get().width; ++x) {
        for(size_t y = 0; y < pattern.get().height; ++y) {
            if(pattern[x, y] == usage[0].first.get().color()) {
                found = true;

                // replace pixel with the color from usage[1]
                pattern.replacePixel(x, y, usage[1].first.get());

                // check pixel and new usage
                EXPECT_EQ((pattern[x, y]), usage[1].first.get().color());
                EXPECT_EQ(pattern.threadList().usage()[0].second, usage[0].second - 1);
                EXPECT_EQ(pattern.threadList().usage()[1].second, usage[1].second + 1);
                break;
            }
        }
        if(found) { break; }
    }
    ASSERT_TRUE(found);

    // check grid
    auto grid = loadPicture(testPath(QString("grid.png")));
    EXPECT_EQ(grid.pixels, pattern.grid().pixels);
}

TEST_F(PatternTests, replaceThread_fullPic) {
    Pattern pattern(selected, list, false);
    const auto& usage = pattern.threadList().usage();

    pattern.replaceThread(usage[0].first.get(), usage[50].first.get());

    auto image = loadPicture(testPath(QString("replaced.png")));
    EXPECT_EQ(image.pixels, pattern.get().pixels);

    auto grid = loadPicture(testPath(QString("grid.png")));
    EXPECT_EQ(grid.pixels, pattern.grid().pixels);
}

TEST_F(PatternTests, replaceThread_area) {
    Pattern pattern(selected, list, false);
    pattern.select({220, 20, 50, 75});
    const auto& usage = pattern.threadList().usage();

    pattern.replaceThread(usage[0].first.get(), usage[50].first.get());

    auto image = loadPicture(testPath(QString("replaced.png")));
    EXPECT_EQ(image.pixels, pattern.get().pixels);

    auto grid = loadPicture(testPath(QString("grid.png")));
    EXPECT_EQ(grid.pixels, pattern.grid().pixels);
}

TEST_F(PatternTests, highlight_fullPic) {
    Pattern pattern(selected, list, false);
    const auto& usage = pattern.threadList().usage();

    auto highlighted = pattern.highlight(usage[15].first.get(), {0xff, 0xff, 0});

    auto image = loadPicture(testPath(QString("highlighted.png")));
    EXPECT_EQ(image.pixels, highlighted.pixels);
}

TEST_F(PatternTests, highlight_area) {
    Pattern pattern(selected, list, false);
    pattern.select({20, 20, 50, 75});
    const auto& usage = pattern.threadList().usage();

    auto highlighted = pattern.highlight(usage[15].first.get(), {0xff, 0xff, 0});

    auto image = loadPicture(testPath(QString("highlighted.png")));
    EXPECT_EQ(image.pixels, highlighted.pixels);
}
