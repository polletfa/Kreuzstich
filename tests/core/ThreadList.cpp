/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "core/ThreadList.hpp"
#include "data-qt/ThreadListParser.hpp"

class ThreadListTests: public testing::Test {
public:
    ThreadListTests()
        : m_threads({})
    {
        if(ThreadListParser parser(TEST_FILES "/ThreadListTests/DMC.threads"); parser) {
            m_threads = ThreadList(std::move(parser.threads()));
        }
    }

protected:
    ThreadList m_threads;

    void SetUp() override {
    }
};

TEST_F(ThreadListTests, findClosest_empty) {
    ThreadList emptyList{{}};
    ASSERT_FALSE(emptyList.findClosest({0, 0, 0}));
}

TEST_F(ThreadListTests, findClosest_black) {
    auto res = m_threads.findClosest({0, 0, 0});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "DMC 310");
}

TEST_F(ThreadListTests, findClosest_white) {
    auto res = m_threads.findClosest({255, 255, 255});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "DMC BLANC");
}

TEST_F(ThreadListTests, findClosest_red) {
    auto res = m_threads.findClosest({255, 0, 0});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "DMC 608");
}
