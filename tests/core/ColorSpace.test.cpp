/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "core/ColorSpace.hpp"

class ColorSpaceTests: public testing::Test {
protected:
    void testCompositeRGBAOntoBackground(ColorSpace::ColorRGBA color, ColorSpace::ColorRGBA background, ColorSpace::ColorRGBA expected) {
        auto res = ColorSpace::compositeRGBAOntoBackground(color, background);
        EXPECT_EQ(  res.red,   expected.red);
        EXPECT_EQ(res.green, expected.green);
        EXPECT_EQ( res.blue,  expected.blue);
        EXPECT_EQ(res.alpha, expected.alpha);
    }

    void testToHSL(ColorSpace::ColorRGBA color, ColorSpace::ColorHSL expected) {
        auto res = ColorSpace::toHSL(color);
        EXPECT_NEAR(       res.hue,        expected.hue, 0.01);
        EXPECT_NEAR(res.saturation, expected.saturation, 0.0001);
        EXPECT_NEAR( res.lightness,  expected.lightness, 0.0001);
    }

    void testToLAB(ColorSpace::ColorRGBA color, ColorSpace::ColorLAB expected) {
        auto res = ColorSpace::toLAB(color);
        EXPECT_NEAR(res.lightness, expected.lightness, 0.0001);
        EXPECT_NEAR(res.a, expected.a, 0.0001);
        EXPECT_NEAR(res.b, expected.b, 0.0001);
    }

    void testDistance(ColorSpace::ColorLAB color1, ColorSpace::ColorLAB color2, ColorSpace::DistanceAlgo algo, double expected) {
        double res = ColorSpace::distance(color1, color2, algo);
        EXPECT_NEAR(res, expected, 0.0001);
    }
};

// --- compositeRGBAOntoBackground
// Test values generated with https://colorstudio.online/tools/opacity-calculator

TEST_F(ColorSpaceTests, compositeRGBAOntoBackground_1) {
    testCompositeRGBAOntoBackground({ 59, 130, 246, 204},  {  1,   2,   3}, { 47,  104, 197});
}
TEST_F(ColorSpaceTests, compositeRGBAOntoBackground_2) {
    testCompositeRGBAOntoBackground({255, 120,   0, 153}, {255, 255, 255}, {255, 174, 102});
}
TEST_F(ColorSpaceTests, compositeRGBAOntoBackground_3) {
    testCompositeRGBAOntoBackground({ 97,  53, 131, 51},  { 99,  69,  44}, { 99,  66,  61});
}

// --- toHSL
// Test values generated with https://colordesigner.io/convert/rgbtohsl

TEST_F(ColorSpaceTests, toHSL_1) { testToHSL({123,  45, 67}, {343.08, 0.4643, 0.3294}); }
TEST_F(ColorSpaceTests, toHSL_2) { testToHSL({ 12,  78, 41}, {146.36, 0.7333, 0.1765}); }
TEST_F(ColorSpaceTests, toHSL_3) { testToHSL({255, 120,  0, 153}, {28.24, 1, 0.7}); } // rgb = {255, 174, 102}

// --- toLAB
// Test values generated with http://www.brucelindbloom.com/
TEST_F(ColorSpaceTests, toLAB_1) { testToLAB({123,  45, 67}, {30.6264, 36.0117, 4.1579}); }
TEST_F(ColorSpaceTests, toLAB_2) { testToLAB({ 12,  78, 41}, {28.6077, -29.5564, 16.3536}); }
TEST_F(ColorSpaceTests, toLAB_3) { testToLAB({255, 120,  0, 153}, {77.5767, 22.6387, 48.4033}); } // rgb = {255, 174, 102}

// --- distance
// Test values generated with http://www.brucelindbloom.com/

TEST_F(ColorSpaceTests, distance_CIE1976_1) { testDistance({64, 12, -48}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIE1976, 102.3621); }
TEST_F(ColorSpaceTests, distance_CIE1976_2) { testDistance({64, 90, -48}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIE1976, 60.1165); }
TEST_F(ColorSpaceTests, distance_CIE1976_3) { testDistance({64, 90,  -8}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIE1976, 23.9582); }
TEST_F(ColorSpaceTests, distance_CIE1976_4) { testDistance({70, 90,  -8}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIE1976, 20.7364); }

TEST_F(ColorSpaceTests, distance_CIEDE2000_1) { testDistance({64, 12, -48}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIEDE2000, 42.9367); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_2) { testDistance({64, 90, -48}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIEDE2000, 21.7480); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_3) { testDistance({64, 90,  -8}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIEDE2000, 13.0841); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_4) { testDistance({70, 90,  -8}, {79, 95, 10}, ColorSpace::DistanceAlgo::CIEDE2000, 9.2152); }
