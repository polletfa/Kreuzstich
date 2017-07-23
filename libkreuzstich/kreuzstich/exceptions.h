/* $Id: exceptions.h 44 2015-05-11 20:48:11Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#ifndef KREUZSTICH_EXCEPTIONS_H
#define KREUZSTICH_EXCEPTIONS_H

#include <exception>
#include <string>

namespace Kreuzstich {

    class Exception : public std::exception {
    public:
        Exception(int errorCode, std::string message);
        ~Exception() throw();

        virtual const char* what() const throw();
        int errorCode() const;


        // error codes:
        static const int EXC_UNKNOWN_ERROR = -1;

        // SystemError
        static const int EXC_MEMORY_ERROR = 10000;

        // SystemError/FileError
        static const int EXC_FILE_NOT_FOUND = 11000;
        static const int EXC_FILE_IO_ERROR = 11001;

        // DataError/ColorTableError
        static const int EXC_COLOR_TABLES_NOT_FOUND = 21000;
        static const int EXC_EMPTY_COLOR_TABLE = 21001;

        // DataError/FormatError
        static const int EXC_INVALID_LENGTH = 22000;
        static const int EXC_INVALID_FILE_FORMAT = 22001;
        static const int EXC_WRONG_FILE_FORMAT_VERSION = 22002;

    private:
        int m_errorCode;
        std::string m_message;
    };

    class UnknownError : public Exception {
    public:
        UnknownError();
        ~UnknownError() throw();
    };

    // group (never thrown)
    class SystemError : public Exception {
    public:
        SystemError(int,std::string);
        ~SystemError() throw();
    };

    class MemoryError : public SystemError {
    public:
        MemoryError();
        ~MemoryError() throw();
    };

    // group (never thrown)
    class FileError : public SystemError {
    public:
        FileError(int,std::string);
        ~FileError() throw();
    };

    class FileNotFound : public FileError {
    public:
        FileNotFound(std::string fileName);
        ~FileNotFound() throw();

        std::string fileName() const;

    private:
        std::string m_fileName;
    };

    class FileIOError : public FileError {
    public:
        FileIOError(std::string fileName, int errorNumber);
        ~FileIOError() throw();

        std::string fileName() const;
        int errorNumber() const;

    private:
        std::string m_fileName;
        int m_errorNumber;
    };

    // group (never thrown)
    class DataError : public Exception {
    public:
        DataError(int,std::string);
        ~DataError() throw();
    };

    // group (never thrown)
    class ColortTableError : public DataError {
    public:
        ColortTableError(int,std::string);
        ~ColortTableError() throw();
    };

    class ColorTablesNotFound : public ColortTableError {
    public:
        ColorTablesNotFound();
        ~ColorTablesNotFound() throw();
    };

    class EmptyColorTable : public ColortTableError {
    public:
        EmptyColorTable(std::string colorTable);
        ~EmptyColorTable() throw();

        std::string colorTable() const;

    private:
        std::string m_colorTable;
    };

    // group (never thrown)
    class FormatError : public DataError {
    public:
        FormatError(int,std::string);
        ~FormatError() throw();
    };

    class InvalidLength : public FormatError {
    public:
        InvalidLength(std::string invalidString);
        ~InvalidLength() throw();

        std::string invalidString() const;

    private:
        std::string m_invalidString;
    };

    class InvalidFileFormat : public FormatError {
    public:
        InvalidFileFormat(std::string filename);
        ~InvalidFileFormat() throw();

        std::string fileName() const;

    private:
        std::string m_fileName;
    };

    class WrongFileFormatVersion : public FormatError {
    public:
        WrongFileFormatVersion(std::string filename, int version, int expectedVersion);
        ~WrongFileFormatVersion() throw();

        std::string fileName() const;
        int version() const;
        int exceptedVersion() const;

    private:
        std::string m_fileName;
        int m_expectedVersion;
        int m_version;
    };

}

#endif
