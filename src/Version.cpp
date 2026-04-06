#include "Version.hpp"
#include "version_defs.hpp"

// STL
#include <sstream>

// Qt
#include <QApplication>
#include <QDateTime>
#include <QLocale>

QString Version::getVersionString() {
    static QString versionString;
    if(versionString.isEmpty()) {
        QDateTime dt = QDateTime::fromSecsSinceEpoch(VersionDefs::BUILD_TIME);
        std::stringstream ss;
        ss << VersionDefs::NAME
           << " " << VersionDefs::MAJOR << "." << VersionDefs::MINOR
           << " " << (VersionDefs::RELEASE_BUILD ? "release" : "debug")
           << " " << QString(VersionDefs::GIT_COMMIT).first(8).toStdString() << (VersionDefs::GIT_DIRTY ? "-dirty" : "")
           << " " << QLocale::system().toString(dt, QLocale::ShortFormat).toStdString();
        versionString = ss.str().data();
    }
    return versionString;
}

QString Version::replaceVars(QString& str) {
    return str
        .replace("$NAME$", VersionDefs::NAME)
        .replace("$WEBSITE$", VersionDefs::WEBSITE)
        .replace("$MAJOR$", QString::number(VersionDefs::MAJOR))
        .replace("$MINOR$", QString::number(VersionDefs::MINOR))
        .replace("$BUILD_TIME$", QString::number(VersionDefs::BUILD_TIME))
        .replace("$GIT_COMMIT$", VersionDefs::GIT_COMMIT)
        .replace("$GIT_DIRTY$", VersionDefs::GIT_DIRTY ? "true" : "false")
        .replace("$RELEASE_BUILD$", VersionDefs::RELEASE_BUILD ? "true" : "false")
        .replace("$VERSION_STR$", getVersionString());
}

void Version::replaceVars(QWidget* win) {
    if(win != nullptr) {
        QString title = win->windowTitle();
        win->setWindowTitle(replaceVars(title));
    }
}

void Version::replaceVars(QAction* action) {
    if(action != nullptr) {
        QString text = action->text(),
            iconText = action->iconText(),
            toolTip = action->toolTip();
        action->setText(replaceVars(text));
        action->setIconText(replaceVars(iconText));
        action->setToolTip(replaceVars(toolTip));
    }
}

void Version::replaceVars(QLabel* label) {
    if(label != nullptr) {
        QString text = label->text();
        label->setText(replaceVars(text));
    }
}
