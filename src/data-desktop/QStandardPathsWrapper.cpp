/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "QStandardPathsWrapper.hpp"

QStringList QStandardPathsWrapper::standardLocations(QStandardPaths::StandardLocation location) {
    return QStandardPaths::standardLocations(location);
}

QString QStandardPathsWrapper::writableLocation(QStandardPaths::StandardLocation location) {
    return QStandardPaths::writableLocation(location);
}
