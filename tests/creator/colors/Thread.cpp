#include <gtest/gtest.h>

#include "creator/colors/Thread.hpp"

class ThreadTests: public testing::Test {
protected:
    void testConstructor(const std::string& color, bool isValid, ColorSpace::rgba_t expected) {
        Thread thr("thread", color);
        EXPECT_EQ(thr.name(), "thread");
        EXPECT_EQ(thr.isValid(), isValid);
        if(isValid) {
            EXPECT_EQ(thr.color().red, expected.red);
            EXPECT_EQ(thr.color().green, expected.green);
            EXPECT_EQ(thr.color().blue, expected.blue);
        }
    }
};

// --- constructor, isValid, name, color

TEST_F(ThreadTests, constuctorValid)           { testConstructor("123456", true, {0x12/255., 0x34/255., 0x56/255.});     }
TEST_F(ThreadTests, constuctorValidWithSpaces) { testConstructor(" 12 34 56 ", true, {0x12/255., 0x34/255., 0x56/255.}); }
TEST_F(ThreadTests, constuctorTooShort)        { testConstructor("12345", false, {});                                                    }
TEST_F(ThreadTests, constuctorInvalidChar)     { testConstructor("1g3456", false, {});                                                   }
TEST_F(ThreadTests, constuctorInvalidInput)    { testConstructor("wrong", false, {});                                                    }
TEST_F(ThreadTests, constuctorEmpty)           { testConstructor("      ", false, {});                                                   }

// --- setSortBy, operator<

TEST_F(ThreadTests, sort) {
    // color1.saturation > color2.saturation
    // color1.lightness < color2.lightness
    Thread thr1("color1", "c8c814"), thr2("color2", "bfbf40");

    // default sort: HLS
    EXPECT_GT(thr2, thr1);
    EXPECT_EQ(thr1, thr1);
    EXPECT_LT(thr1, thr2);

    // Change sort to HSL
    Thread::setSortBy(Thread::HSL);
    EXPECT_GT(thr1, thr2);
    EXPECT_EQ(thr1, thr1);
    EXPECT_LT(thr2, thr1);

    // Change sort back
    Thread::setSortBy(Thread::HLS);
    EXPECT_GT(thr2, thr1);
    EXPECT_EQ(thr1, thr1);
    EXPECT_LT(thr1, thr2);
}

// --- distance

TEST_F(ThreadTests, distanceFromThread) {
    // Test values generated with http://www.brucelindbloom.com/
    Thread thr1("color1", "7b2d43"), // rgb(123, 45, 67) == lab(30.6264, 36.0117,  4.1579)
        thr2("color2", "0c4e29");    // rgb( 12, 78, 41) == lab(28.6077, 29.5564, 16.3536)

    EXPECT_NEAR(thr1.distance(thr2), 66.7232, 0.0001);
    EXPECT_NEAR(thr1.distance(thr2, ColorSpace::CIEDE2000), 51.9866, 0.0001);
}

TEST_F(ThreadTests, distanceFromRGB) {
    // Test values generated with http://www.brucelindbloom.com/
    Thread thread("color1", "7b2d43");                          // rgb(123, 45, 67) == lab(30.6264, 36.0117,  4.1579)
    ColorSpace::rgba_t color{12/255., 78/255., 41/255.}; // rgb( 12, 78, 41) == lab(28.6077, 29.5564, 16.3536)

    EXPECT_NEAR(thread.distance(color), 66.7232, 0.0001);
    EXPECT_NEAR(thread.distance(color, ColorSpace::CIEDE2000), 51.9866, 0.0001);
}
