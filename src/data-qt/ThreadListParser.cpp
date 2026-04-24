/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "ThreadListParser.hpp"

// Qt
#include <QFile>
#include <QTextStream>
#include <QStringView>

ThreadListParser::ThreadListParser(const QString& file)
    : m_file(file)
{
    if(QFile ifile{m_file}; ifile.open(QFile::OpenModeFlag::ReadOnly | QFile::OpenModeFlag::Text)) {
        QTextStream stream(&ifile);
        while(!stream.atEnd()) {
            QString line{stream.readLine()};
            QStringView vline{line};
            if(auto pos = vline.indexOf('#'); pos >= 0) {
                vline.truncate(pos); // remove comment
            }
            vline = vline.trimmed();
            if(vline.size() == 0) {
                continue; // ignore line (empty or comment only)
            }
            if(auto pos = vline.indexOf(':'); pos < 0) {
                m_warnings.push_back({Warning::INVALID_LINE, vline.toString()});
                continue; // ignore line
            } else {
                QStringView name = vline.left(pos).trimmed();
                QStringView rgb = vline.mid(pos+1).trimmed();

                Thread thread{name.toString().toStdString(), rgb.toString().toStdString()};
                if(!thread) {
                    m_warnings.push_back({Warning::INVALID_COLOR, vline.toString()});
                    continue; // ignore line
                }
                m_threads.push_back(thread);
            }
        }
        if(m_warnings.size() > m_threads.size()) {
            m_error = Error::TOO_MANY_ERRORS;
        } else if(m_threads.empty()) {
            m_error = Error::NO_DEFINITION_FOUND;
        } else {
            m_error = Error::SUCCESS;
        }
    } else {
        m_error = Error::OPEN_FILE_ERROR;
        m_error.message = ifile.errorString();
    }
}

ThreadListParser::operator bool() const {
    return m_error.error == Error::SUCCESS;
}

QList<Thread>& ThreadListParser::threads() {
    return m_threads;
}

const QList<ThreadListParser::Warning>& ThreadListParser::warnings() const {
    return m_warnings;
}

const ThreadListParser::Error& ThreadListParser::error() const {
    return m_error;
}
