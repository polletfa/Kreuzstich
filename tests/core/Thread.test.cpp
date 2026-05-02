/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "core/Thread.hpp"

class ThreadTests: public testing::Test {
protected:
    void testConstructor(const std::string& color, bool isValid, ColorSpace::ColorRGBA expected) {
        Thread thr("thread", color);
        EXPECT_EQ(thr.name(), "thread");
        if(isValid) {
            ASSERT_TRUE(thr);
            EXPECT_EQ(thr.color(), expected);
            auto expectedHSL = ColorSpace::toHSL(expected);
            EXPECT_NEAR(thr.hsl().hue, expectedHSL.hue, 0.001);
            EXPECT_NEAR(thr.hsl().saturation, expectedHSL.saturation, 0.001);
            EXPECT_NEAR(thr.hsl().lightness, expectedHSL.lightness, 0.001);
        } else {
            ASSERT_FALSE(thr);
        }
    }
};

// --- constructor, isValid, name, color, hsl

TEST_F(ThreadTests, constuctorValid)           { testConstructor("123456", true, {0x12, 0x34, 0x56}); }
TEST_F(ThreadTests, constuctorValidWithSpaces) { testConstructor("  12 34 56 ", true, {0x12, 0x34, 0x56}); }
TEST_F(ThreadTests, constuctorTooShort)        { testConstructor("12345", false, {}); }
TEST_F(ThreadTests, constuctorInvalidChar)     { testConstructor("1g3456", false, {}); }
TEST_F(ThreadTests, constuctorInvalidInput)    { testConstructor("wrong", false, {}); }
TEST_F(ThreadTests, constuctorEmpty)           { testConstructor("      ", false, {}); }

// --- distance

TEST_F(ThreadTests, distanceFromThread) {
    // Test values generated with http://www.brucelindbloom.com/
    Thread thr1("color1", "7b2d43"), // rgb(123, 45, 67) == lab(30.6264, 36.0117,  4.1579)
        thr2("color2", "0c4e29");    // rgb( 12, 78, 41) == lab(28.6077, -29.5564, 16.3536)

    EXPECT_NEAR(thr1.distance(thr2, ColorSpace::DistanceAlgo::CIE1976), 66.7232, 0.0001);
    EXPECT_NEAR(thr1.distance(thr2, ColorSpace::DistanceAlgo::CIEDE2000), 51.9866, 0.0001);
}

TEST_F(ThreadTests, distanceFromLAB) {
    // Test values generated with http://www.brucelindbloom.com/
    Thread thread("color1", "7b2d43");             // rgb(123, 45, 67) == lab(30.6264, 36.0117,  4.1579)
    ColorSpace::ColorLAB color{28.6077, -29.5564, 16.3536};

    EXPECT_NEAR(thread.distance(color, ColorSpace::DistanceAlgo::CIE1976), 66.7232, 0.0001);
    EXPECT_NEAR(thread.distance(color, ColorSpace::DistanceAlgo::CIEDE2000), 51.9866, 0.0001);
}
