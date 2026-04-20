/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Mockup_QStandardPathsWrapper.hpp"

QStringList Mockup_QStandardPathsWrapper::standardLocations(QStandardPaths::StandardLocation /*location*/) {
    return {
        QString(testPath({"test", "path", "1"}).string().data()),
        QString(testPath({"another", "test", "path"}).string().data()),
        QString(testPath({"one", "more", "path"}).string().data())
    };
}

QString Mockup_QStandardPathsWrapper::writableLocation(QStandardPaths::StandardLocation /*location*/) {
    return QString(testPath({"test", "path", "1"}).string().data());
}
