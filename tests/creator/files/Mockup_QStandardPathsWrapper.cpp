/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Mockup_QStandardPathsWrapper.hpp"

void Mockup_QStandardPathsWrapper::SetUp() {
    MockupBase::SetUp();
    m_root = QString(TEST_FILES) + "/" + testSuite() + "/" + testName();
}

QStringList Mockup_QStandardPathsWrapper::standardLocations(QStandardPaths::StandardLocation location) {
    return {
        m_root + "/test/path/1",
        m_root + "/another/test/path",
        m_root + "/one/more/path"
    };
}

QString Mockup_QStandardPathsWrapper::writableLocation(QStandardPaths::StandardLocation location) {
    return m_root + "/test/path/1";
}
