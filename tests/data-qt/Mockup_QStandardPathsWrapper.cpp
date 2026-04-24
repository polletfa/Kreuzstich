/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Mockup_QStandardPathsWrapper.hpp"

QStringList Mockup_QStandardPathsWrapper::standardLocations(QStandardPaths::StandardLocation /*location*/) {
    return {
        testPath(QString("test/path/1")),
        testPath(QString("another/test/path")),
        testPath(QString("one/more/path"))
    };
}

QString Mockup_QStandardPathsWrapper::writableLocation(QStandardPaths::StandardLocation /*location*/) {
    return testPath(QString("test/path/1"));
}
