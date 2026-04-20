/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef MOCKUP_HPP
#define MOCKUP_HPP

#include <gtest/gtest.h>

// STL
#include <string>
#include <vector>
#include <filesystem>

/**
 * Helper class for mockups
 */
class Mockup {
public:
    virtual void SetUp();
    virtual void TearDown();

    const std::string& testSuite() const;
    const std::string& testName() const;
    std::filesystem::path testPath(const std::vector<std::string>& relativePath) const;

private:
    std::string m_testSuite;
    std::string m_testName;
    std::filesystem::path m_testData;
};

#endif // MOCKUP_HPP
