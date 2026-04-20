/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef THREADLISTPARSER_HPP
#define THREADLISTPARSER_HPP

#include "../colors/Thread.hpp"

// STL
#include <filesystem>
#include <vector>
#include <string>

// Qt
#include <QCoreApplication>

class ThreadListParser {
    Q_DECLARE_TR_FUNCTIONS(ThreadListParser)

public:
    explicit ThreadListParser(const std::filesystem::path& file);

    /**
     * Returns true if the file could be parsed
     */
    operator bool() const;

    /**
     * Get the parsed values (if parsing was successful).
     */
    std::vector<Thread>& threads();

    /**
     * Get the warnings (if parsing was successful).
     */
    const std::vector<std::string>& warnings() const;

    /**
     * Get the error message (if parsing was not successful).
     */
    const std::string& error() const;

private:
    std::filesystem::path m_file;

    bool m_parseResult{false};
    std::vector<Thread> m_threads;
    std::vector<std::string> m_warnings;
    std::string m_error;
};

#endif // THREADLISTPARSER_HPP
