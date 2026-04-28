/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include <gtest/gtest.h>

#include "core/ThreadList.hpp"

class ThreadListTests: public testing::Test {
public:
    ThreadListTests()
        : m_threads({
                Thread{"1", "bfaa40"}, // 50, 50%, 50%
                Thread{"2", "c8c814"}, // 60, 82%, 43%
                Thread{"3", "bfbf40"}  // 60, 50%, 50%
            })
    {
        auto usage = m_threads.getUsage();
        for(auto& item: usage) {
            if(item.first.get().name() == "1") { item.second = 20; }
            else if(item.first.get().name() == "2") { item.second = 90; }
            else { item.second = 50; }
        }
        m_threads.setUsage(usage);
    }

protected:
    ThreadList m_threads;

    void SetUp() override {
    }
};

// -- get

TEST_F(ThreadListTests, get_HSL_ASC) {
    std::vector<std::string> expected = {"1", "3", "2"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::HSL, ThreadList::SortOrder::ASC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

TEST_F(ThreadListTests, get_HSL_DESC) {
    std::vector<std::string> expected = {"2", "3", "1"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::HSL, ThreadList::SortOrder::DESC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

TEST_F(ThreadListTests, get_HLS_ASC) {
    std::vector<std::string> expected = {"1", "2", "3"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::HLS, ThreadList::SortOrder::ASC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

TEST_F(ThreadListTests, get_HLS_DESC) {
    std::vector<std::string> expected = {"3", "2", "1"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::HLS, ThreadList::SortOrder::DESC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

TEST_F(ThreadListTests, get_Name_ASC) {
    std::vector<std::string> expected = {"1", "2", "3"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::Name, ThreadList::SortOrder::ASC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

TEST_F(ThreadListTests, get_Name_DESC) {
    std::vector<std::string> expected = {"3", "2", "1"};
    std::vector<std::string> sorted;
    for(auto item: m_threads.get(ThreadList::SortBy::Name, ThreadList::SortOrder::DESC)) {
        sorted.push_back(item.get().name());
    }
    EXPECT_EQ(sorted, expected);
}

// -- findClosest

TEST_F(ThreadListTests, findClosest_empty) {
    ThreadList emptyList{{}};
    ASSERT_FALSE(emptyList.findClosest({0, 0, 0}));
}

TEST_F(ThreadListTests, findClosest) {
    auto res = m_threads.findClosest({0xc9, 0xc7, 0x10});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "2");
}

// -- findClosestInUse

TEST_F(ThreadListTests, findClosestInUse_empty) {
    ThreadList threads{{Thread{"1", "bfaa40"}}}; // usage = 0
    ASSERT_FALSE(threads.findClosestInUse({0, 0, 0}));
}

TEST_F(ThreadListTests, findClosestInUse) {
    auto usage = m_threads.getUsage();
    usage[0].second = 0;
    m_threads.setUsage(usage);
    auto res = m_threads.findClosestInUse({0xc9, 0xc7, 0x10});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "3"); // 2 is the closest, but not in use
}

// -- findThread

TEST_F(ThreadListTests, findThread_found) {
    auto res = m_threads.findThread({0xbf, 0xbf, 0x40});
    ASSERT_TRUE(res);
    EXPECT_EQ(res->get().name(), "3");
}

TEST_F(ThreadListTests, findThread_notfound) {
    ASSERT_FALSE(m_threads.findThread({1, 2, 4}));
}

// -- getUsage

TEST_F(ThreadListTests, getUsage) {
    auto usage = m_threads.getUsage();

    EXPECT_EQ(usage.size(), m_threads.get().size());

    EXPECT_EQ(usage[0].first.get().name(), "2");
    EXPECT_EQ(usage[0].second, 90);

    EXPECT_EQ(usage[1].first.get().name(), "3");
    EXPECT_EQ(usage[1].second, 50);

    EXPECT_EQ(usage[2].first.get().name(), "1");
    EXPECT_EQ(usage[2].second, 20);
}

// -- setUsage

TEST_F(ThreadListTests, setUsage) {
    auto usage = m_threads.getUsage();

    // change count
    for(auto& item: usage) {
        if(item.first.get().name() == "1") { item.second = 200; }
        else if(item.first.get().name() == "2") { item.second = 90; }
        else { item.second = 50; }
    }
    m_threads.setUsage(usage);

    // reread usage
    usage = m_threads.getUsage();
    EXPECT_EQ(usage[0].first.get().name(), "1");
    EXPECT_EQ(usage[0].second, 200);

    EXPECT_EQ(usage[1].first.get().name(), "2");
    EXPECT_EQ(usage[1].second, 90);

    EXPECT_EQ(usage[2].first.get().name(), "3");
    EXPECT_EQ(usage[2].second, 50);
}

// -- updateUsage

TEST_F(ThreadListTests, updateUsage) {
    // update usage
    m_threads.updateUsage(Thread{"2", "c8c814"}, Thread{"1", "bfaa40"}, 50);

    auto usage = m_threads.getUsage();
    EXPECT_EQ(usage[0].first.get().name(), "1");
    EXPECT_EQ(usage[0].second, 70);

    EXPECT_EQ(usage[1].first.get().name(), "3");
    EXPECT_EQ(usage[1].second, 50);

    EXPECT_EQ(usage[2].first.get().name(), "2");
    EXPECT_EQ(usage[2].second, 40);
}
