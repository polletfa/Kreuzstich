/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
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

    /**
     * Get a path to a test file for the current test
     * <test_files>/<testsuite>/<testname>/<relativePath>
     */
    std::filesystem::path testPath(const std::string& relativePath) const;
    /**
     * Get a path to a test file for the current test
     * <test_files>/<testsuite>/<testname>/<relativePath>
     */
    QString testPath(const QString& relativePath) const;

    /**
     * Get a path to a test file for the current test suite
     * <test_files>/<testsuite>/<relativePath>
     */
    std::filesystem::path testPathFixture(const std::string& relativePath) const;
    /**
     * Get a path to a test file for the current test suite
     * <test_files>/<testsuite>/<relativePath>
     */
    QString testPathFixture(const QString& relativePath) const;

private:
    std::string m_testSuite;
    std::string m_testName;
};

#endif // MOCKUP_HPP
