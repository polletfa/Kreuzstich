/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "core/ColorSpace.hpp"

class ColorSpaceTests: public testing::Test {
protected:
    void testCompositeRGBAOntoBackground(ColorSpace::ColorRGBA color, ColorSpace::ColorRGBA background, ColorSpace::ColorRGBA expected) {
        auto res = ColorSpace::compositeRGBAOntoBackground(color, background);
        EXPECT_NEAR(  res.red,   expected.red, 1/255.);
        EXPECT_NEAR(res.green, expected.green, 1/255.);
        EXPECT_NEAR( res.blue,  expected.blue, 1/255.);
        EXPECT_EQ(res.alpha, expected.alpha); // should be exactly one - floating point precision is not an issue
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
    testCompositeRGBAOntoBackground({ 59/255., 130/255., 246/255., 0.7},  {  1/255.,   2/255.,   3/255.}, { 42/255.,  92/255., 173/255.});
}
TEST_F(ColorSpaceTests, compositeRGBAOntoBackground_2) {
    testCompositeRGBAOntoBackground({255/255., 120/255.,   0/255., 0.54}, {255/255., 255/255., 255/255.}, {255/255., 182/255., 117/255.});
}
TEST_F(ColorSpaceTests, compositeRGBAOntoBackground_3) {
    testCompositeRGBAOntoBackground({ 97/255.,  53/255., 131/255., 0.2},  { 99/255.,  69/255.,  44/255.}, { 99/255.,  66/255.,  61/255.});
}

// --- toHSL
// Test values generated with https://colordesigner.io/convert/rgbtohsl

TEST_F(ColorSpaceTests, toHSL_1) { testToHSL({123/255.,  45/255., 67/255.}, {343.08, 0.4643, 0.3294}); }
TEST_F(ColorSpaceTests, toHSL_2) { testToHSL({ 12/255.,  78/255., 41/255.}, {146.36, 0.7333, 0.1765}); }
TEST_F(ColorSpaceTests, toHSL_3) { testToHSL({255/255., 120/255.,  0/255., 0.54}, {28.23, 1, 0.73}); } // rgb = {1, 0.714118, 0.459999}

// --- toLAB

TEST_F(ColorSpaceTests, toLAB_1) { testToLAB({123/255.,  45/255., 67/255.}, {30.6264, 36.0117, 4.1579}); }
TEST_F(ColorSpaceTests, toLAB_2) { testToLAB({ 12/255.,  78/255., 41/255.}, {28.6077, -29.5564, 16.3536}); }
TEST_F(ColorSpaceTests, toLAB_3) { testToLAB({255/255., 120/255.,  0/255., 0.54}, {79.6439, 19.5483, 43.2345}); } // rgb = {1, 0.714118, 0.459999}

// --- distance
// Test values generated with http://www.brucelindbloom.com/

TEST_F(ColorSpaceTests, distance_CIE1976_1) { testDistance({64, 12, -48}, {79, 95, 10}, ColorSpace::CIE1976, 102.3621); }
TEST_F(ColorSpaceTests, distance_CIE1976_2) { testDistance({64, 90, -48}, {79, 95, 10}, ColorSpace::CIE1976, 60.1165); }
TEST_F(ColorSpaceTests, distance_CIE1976_3) { testDistance({64, 90,  -8}, {79, 95, 10}, ColorSpace::CIE1976, 23.9582); }
TEST_F(ColorSpaceTests, distance_CIE1976_4) { testDistance({70, 90,  -8}, {79, 95, 10}, ColorSpace::CIE1976, 20.7364); }

TEST_F(ColorSpaceTests, distance_CIEDE2000_1) { testDistance({64, 12, -48}, {79, 95, 10}, ColorSpace::CIEDE2000, 42.9367); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_2) { testDistance({64, 90, -48}, {79, 95, 10}, ColorSpace::CIEDE2000, 21.7480); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_3) { testDistance({64, 90,  -8}, {79, 95, 10}, ColorSpace::CIEDE2000, 13.0841); }
TEST_F(ColorSpaceTests, distance_CIEDE2000_4) { testDistance({70, 90,  -8}, {79, 95, 10}, ColorSpace::CIEDE2000, 9.2152); }
