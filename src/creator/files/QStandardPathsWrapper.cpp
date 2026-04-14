#include "QStandardPathsWrapper.hpp"

QStringList QStandardPathsWrapper::standardLocations(QStandardPaths::StandardLocation location) {
    return QStandardPaths::standardLocations(location);
}

QString QStandardPathsWrapper::writableLocation(QStandardPaths::StandardLocation location) {
    return QStandardPaths::writableLocation(location);
}
