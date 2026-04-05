#include "version.hpp"

// STL
#include <sstream>

// Qt
#include <QApplication>
#include <QDateTime>
#include <QLocale>

QString Version::getVersionString() {
    static QString versionString;
    if(versionString.isEmpty()) {
        QDateTime dt = QDateTime::fromSecsSinceEpoch(Version::BUILD_TIME);
        std::stringstream ss;
        ss << Version::NAME
           << " " << Version::MAJOR << "." << Version::MINOR
           << " " << (Version::RELEASE_BUILD ? "release" : "debug")
           << " " << QString(Version::GIT_COMMIT).first(8).toStdString() << (Version::GIT_DIRTY ? "-dirty" : "")
           << " " << QLocale::system().toString(dt, QLocale::ShortFormat).toStdString();
        versionString = ss.str().data();
    }
    return versionString;
}
