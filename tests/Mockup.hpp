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
#include <filesystem>

// Qt
#include <QString>

/**
 * Helper class for mockups
 */
class Mockup {
public:
    virtual void SetUp();
    virtual void TearDown();

    const std::string& testSuite() const;
    const std::string& testName() const;
    std::filesystem::path testPath(const std::string& relativePath) const;
    QString testPath(const QString& relativePath) const;

private:
    std::string m_testSuite;
    std::string m_testName;
};

#endif // MOCKUP_HPP
