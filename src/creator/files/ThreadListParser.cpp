/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "ThreadListParser.hpp"

#include "../utils/StringUtils.hpp"

// STL
#include <fstream>
#include <cerrno>
#include <cstring>

ThreadListParser::ThreadListParser(const std::filesystem::path& file)
    : m_file(file)
{
    if(std::ifstream ifile{m_file}; ifile) {
        std::string line;
        while(std::getline(ifile, line)) {
            std::string_view vline = StringUtils::trim(StringUtils::removeComment(line, "#"));
            if(vline.size() == 0) {
                continue; // ignore line (empty or comment only)
            }
            if(auto pos = vline.find(':'); pos == std::string::npos) {
                m_warnings.push_back(tr("Invalid line: %1").arg(std::string{vline}.data()).toStdString());
                continue; // ignore line
            } else {
                std::string_view name = StringUtils::trim(vline.substr(0, pos));
                std::string_view rgb = StringUtils::trim(vline.substr(pos+1));

                Thread thread{std::string{name}, std::string{rgb}};
                if(!thread) {
                    m_warnings.push_back(tr("Invalid color: %1").arg(std::string{rgb}.data()).toStdString());
                    continue; // ignore line
                }
                m_threads.push_back(thread);
            }
        }
        if(m_warnings.size() > m_threads.size()) {
            m_error = tr("Invalid file (too many errors)").toStdString();
            m_parseResult = false;
        } else if(m_threads.empty()) {
            m_error = tr("Invalid file (no thread definition found)").toStdString();
            m_parseResult = false;
        } else {
            m_parseResult = true;
        }
    } else {
        m_error = tr("Cannot open file: %1.")
            .arg(strerror(errno))
            .toStdString();
        m_parseResult = false;
    }
}

ThreadListParser::operator bool() const {
    return m_parseResult;
}

std::vector<Thread>& ThreadListParser::threads() {
    return m_threads;
}

const std::vector<std::string>& ThreadListParser::warnings() const {
    return m_warnings;
}

const std::string& ThreadListParser::error() const {
    return m_error;
}
