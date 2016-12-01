/* $Id: exceptions.cpp 45 2015-07-31 17:08:02Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#include <kreuzstich/exceptions.h>

#include <sstream>

using namespace Kreuzstich;

Exception::Exception(int errorCode, std::string message) : m_errorCode(errorCode), m_message(message) {}
Exception::~Exception() throw() {}
int Exception::errorCode() const { return m_errorCode; }
const char* Exception::what() const throw() {
    std::ostringstream oss;
    oss << errorCode()<<" libkreuzstich/"<<m_message;
    return oss.str().c_str();
}

UnknownError::UnknownError()
    : Exception(EXC_UNKNOWN_ERROR, "UnknownError") {}
UnknownError::~UnknownError() throw() {}

// SystemError
SystemError::SystemError(int errorCode, std::string message)
    : Exception(errorCode, std::string("SystemError/")+message) {}
SystemError::~SystemError() throw() {}

MemoryError::MemoryError()
    : SystemError(EXC_MEMORY_ERROR, "MemoryError") {}
MemoryError::~MemoryError() throw() {}

// SystemError/FileError
FileError::FileError(int errorCode, std::string message)
    : SystemError(errorCode, std::string("FileError/")+message) {}
FileError::~FileError() throw() {}

FileNotFound::FileNotFound(std::string filename)
    : FileError(EXC_FILE_NOT_FOUND, "FileNotFound"),
      m_fileName(filename) {}
FileNotFound::~FileNotFound() throw() {}
std::string FileNotFound::fileName() const { return m_fileName; }

FileIOError::FileIOError(std::string filename, int errorNumber)
    : FileError(EXC_FILE_IO_ERROR, "FileIOError"), m_fileName(filename), m_errorNumber(errorNumber) {}
FileIOError::~FileIOError() throw() {}
std::string FileIOError::fileName() const { return m_fileName; }
int FileIOError::errorNumber() const { return m_errorNumber; }

// DataError

DataError::DataError(int errorCode, std::string message)
    : Exception(errorCode, std::string("DataError/")+message) {}
DataError::~DataError() throw() {}

// DataError/ColorTableError

ColortTableError::ColortTableError(int errorCode, std::string message)
    : DataError(errorCode, std::string("ColorTableError/")+message) {}
ColortTableError::~ColortTableError() throw() {}

ColorTablesNotFound::ColorTablesNotFound()
    : ColortTableError(EXC_COLOR_TABLES_NOT_FOUND, "ColorTablesNotFound") {}
ColorTablesNotFound::~ColorTablesNotFound() throw() {}

EmptyColorTable::EmptyColorTable(std::string colorTable)
    : ColortTableError(EXC_EMPTY_COLOR_TABLE, "EmptyColorTable"),
    m_colorTable(colorTable) {}
EmptyColorTable::~EmptyColorTable() throw() {}
std::string EmptyColorTable::colorTable() const { return m_colorTable; }

// DataError/FormatError

FormatError::FormatError(int errorCode, std::string message)
    : DataError(errorCode, std::string("FormatError/")+message) {}
FormatError::~FormatError() throw() {}

InvalidLength::InvalidLength(std::string invalidString)
    : FormatError(EXC_INVALID_LENGTH, "InvalidLength"),
      m_invalidString(invalidString) {}
InvalidLength::~InvalidLength() throw() {}
std::string InvalidLength::invalidString() const { return m_invalidString; }

InvalidFileFormat::InvalidFileFormat(std::string filename)
    : FormatError(EXC_INVALID_FILE_FORMAT, "InvalidFileFormat"),
      m_fileName(filename) {}
InvalidFileFormat::~InvalidFileFormat() throw() {}
std::string InvalidFileFormat::fileName() const { return m_fileName; }

WrongFileFormatVersion::WrongFileFormatVersion(std::string filename, int version, int expectedVersion)
    : FormatError(EXC_WRONG_FILE_FORMAT_VERSION, "WrongFileFormatVersion"),
      m_fileName(filename), m_version(version), m_expectedVersion(expectedVersion) {}
WrongFileFormatVersion::~WrongFileFormatVersion() throw() {}
std::string WrongFileFormatVersion::fileName() const { return m_fileName; }
int WrongFileFormatVersion::exceptedVersion() const { return m_expectedVersion; }
int WrongFileFormatVersion::version() const { return m_version; }
