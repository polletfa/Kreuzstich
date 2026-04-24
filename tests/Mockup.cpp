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
}

void Mockup::TearDown() {
}

const std::string& Mockup::testSuite() const {
    return m_testSuite;
}

const std::string& Mockup::testName() const {
    return m_testName;
}

std::filesystem::path Mockup::testPath(const std::string& relativePath) const {
    return std::string{TEST_FILES} + "/" + m_testSuite + "/" + m_testName + "/" + relativePath;
}

QString Mockup::testPath(const QString& relativePath) const {
    return QString(TEST_FILES).append("/").append(m_testSuite).append("/").append(m_testName).append("/").append(relativePath);
}
