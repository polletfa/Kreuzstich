/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "QStandardPathsWrapper.mock.hpp"

QStringList QStandardPathsWrapper_mock::standardLocations(QStandardPaths::StandardLocation /*location*/) {
    return {
        testPath(QString("test/path/1")),
        testPath(QString("another/test/path")),
        testPath(QString("one/more/path"))
    };
}

QString QStandardPathsWrapper_mock::writableLocation(QStandardPaths::StandardLocation /*location*/) {
    return testPath(QString("test/path/1"));
}
