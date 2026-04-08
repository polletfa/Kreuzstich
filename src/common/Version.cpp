#include "Version.hpp"

// STL
#include <sstream>

// Qt
#include <QDateTime>
#include <QLocale>

const QString Version::VERSION_STRING = Version::getVersionString();

QString Version::getVersionString() {
    static QString versionString;
    if(versionString.isEmpty()) {
        QDateTime dt = QDateTime::fromSecsSinceEpoch(BUILD_TIME);
        std::stringstream ss;
        ss << NAME
           << " " << MAJOR << "." << MINOR
           << " " << (RELEASE_BUILD ? "release" : "debug");
        if(GIT_COMMIT[0]) {
            ss << " " << QString(GIT_COMMIT).first(8).toStdString();
        }
        ss << " " << QLocale::system().toString(dt, QLocale::ShortFormat).toStdString();
        versionString = ss.str().data();
    }
    return versionString;
}

QString Version::replaceVersionVars(QString& str) {
    return str
        .replace("$NAME$", Version::NAME)
        .replace("$WEBSITE$", Version::WEBSITE)
        .replace("$MAJOR$", QString::number(Version::MAJOR))
        .replace("$MINOR$", QString::number(Version::MINOR))
        .replace("$BUILD_TIME$", QString::number(Version::BUILD_TIME))
        .replace("$GIT_COMMIT$", Version::GIT_COMMIT)
        .replace("$RELEASE_BUILD$", Version::RELEASE_BUILD ? "true" : "false")
        .replace("$VERSION_STRING$", Version::VERSION_STRING);
}
