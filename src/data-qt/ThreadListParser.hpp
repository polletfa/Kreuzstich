/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef THREADLISTPARSER_HPP
#define THREADLISTPARSER_HPP

// core
#include "core/Thread.hpp"

// Qt
#include <QList>
#include <QString>

class ThreadListParser {
public:
    explicit ThreadListParser(const QString& file);

    struct Error {
        enum ErrorEnum {
            SUCCESS,               /**< No error */
            TOO_MANY_ERRORS,       /**< More invalid lines than valid lines */
            NO_DEFINITION_FOUND,   /**< Not a single thread definition found in the file (either empty or only invalid lines) */
            OPEN_FILE_ERROR        /**< Cannot open file */
        } error;
        QString message{};         /**< Some errors may provide an additional message (system errors only, for example OPEN_FILE_ERROR).
                                        In this case, the error message will be in the language of the system locale */

        Error(ErrorEnum error): error(error) {}
    };

    struct Warning {
        enum WarningEnum {
            INVALID_LINE,         /**< Cannot parse line */
            INVALID_COLOR         /**< Cannot parse color */
        } warning;
        QString line;             /**< Invalid line that caused the warning */
    };

    /**
     * Returns true if the file could be parsed
     */
    operator bool() const;

    /**
     * Get the parsed values (if parsing was successful).
     */
    QList<Thread>& threads();

    /**
     * Get the warnings (if parsing was successful).
     */
    const QList<Warning>& warnings() const;

    /**
     * Get the error message (if parsing was not successful).
     */
    const Error& error() const;

private:
    QString m_file;

    QList<Thread> m_threads;
    QList<Warning> m_warnings;
    Error m_error{Error::SUCCESS};
};

#endif // THREADLISTPARSER_HPP
