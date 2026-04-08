#include <gtest/gtest.h>

#include "creator/dummy.hpp"

class DummyTest: public testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(DummyTest, dummy) {
    Dummy dummy;
    EXPECT_EQ(dummy.dummy(2, 3), 5   );
}
