/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Mockup.hpp"

void Mockup::SetUp() {
    const auto* info = testing::UnitTest::GetInstance()->current_test_info();
    m_testSuite = info->test_suite_name();
    m_testName = info->name();

    std::filesystem::path testData{TEST_FILES};
    testData /= m_testSuite;
    testData /= m_testName;

    m_testData = std::string{TEST_FILES} + "/" + m_testSuite + "/" + m_testName + "/";
}

void Mockup::TearDown() {
}

const std::string& Mockup::testSuite() const {
    return m_testSuite;
}

const std::string& Mockup::testName() const {
    return m_testName;
}

std::filesystem::path Mockup::testPath(const std::vector<std::string>& relativePath) const {
    auto path = m_testData;
    for(const auto& pathComponent: relativePath) {
        path /= pathComponent;
    }
    return path;
}
