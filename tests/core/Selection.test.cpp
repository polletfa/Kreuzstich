/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <gtest/gtest.h>

#include "core/Selection.hpp"
#include "core/Pattern.hpp"

// STL
#include <vector>
#include <string>

class SelectionTests: public testing::Test {
public:
    SelectionTests()
        : pattern(Pattern::PixelBuffer{
                std::vector<ColorSpace::ColorRGBA>(50, {0xff, 0xff, 0xff}),
                10,5
            }, ThreadList{std::vector<Thread>{}}, false)
    {}

protected:
    void compareAreas(std::vector<bool> expected, std::vector<bool> found, size_t w, size_t h) {
        auto expectedAsStr = areaToString(expected, w, h);
        auto foundAsStr = areaToString(found, w, h);
        EXPECT_EQ(foundAsStr, expectedAsStr); // compare as strings for a better output on error
    }

    std::string areaToString(std::vector<bool> area, size_t w, size_t h) {
        std::string res;
        for(size_t y = 0; y < h; ++y) {
            for(size_t x = 0; x < w; ++x) {
                res += area[y * w + x] ? 'X' : '_';
            }
            res += '\n';
        }
        return res;
    }
    Pattern pattern;
};

TEST_F(SelectionTests, iterate_fullPic) {
    Selection sel{pattern};
    std::vector<bool> expected(50, true), found(50, false);

    for(size_t index: sel) {
        found[index] = true;
    }
    compareAreas(expected, found, 10, 5);
}

TEST_F(SelectionTests, iterate_area) {
    Selection sel{pattern, {3, 1, 4, 2}};
    std::vector<bool> expected(50, false), found(50, false);
    for(size_t i = 3; i < 3+4; ++i) {
        for(size_t j = 1; j < 1+2; ++j) {
            expected[j*pattern.get().width + i] = true;
        }
    }
    for(size_t index: sel) {
        found[index] = true;
    }
    compareAreas(expected, found, 10, 5);
}

TEST_F(SelectionTests, iterate_edge) {
    Selection sel{pattern, {3, 1, 7, 4}};
    std::vector<bool> expected(50, false), found(50, false);
    for(size_t i = 3; i < 10; ++i) {
        for(size_t j = 1; j < 5; ++j) {
            expected[j*pattern.get().width + i] = true;
        }
    }
    for(size_t index: sel) {
        found[index] = true;
    }
    compareAreas(expected, found, 10, 5);
}

TEST_F(SelectionTests, iterate_overshoot) {
    Selection sel{pattern, {3, 1, 100, 100}};
    std::vector<bool> expected(50, false), found(50, false);
    for(size_t i = 3; i < 10; ++i) {
        for(size_t j = 1; j < 5; ++j) {
            expected[j*pattern.get().width + i] = true;
        }
    }
    for(size_t index: sel) {
        found[index] = true;
    }
    compareAreas(expected, found, 10, 5);
}

TEST_F(SelectionTests, iterate_areaOutsideX) {
    Selection sel{pattern, {100, 1, 4, 2}};
    std::vector<size_t> found;
    for(size_t index: sel) {
        found.push_back(index);
    }
    EXPECT_EQ(found.size(), 0);
}

TEST_F(SelectionTests, iterate_areaOutsideY) {
    Selection sel{pattern, {1, 100, 4, 2}};
    std::vector<size_t> found;
    for(size_t index: sel) {
        found.push_back(index);
    }
    EXPECT_EQ(found.size(), 0);
}
