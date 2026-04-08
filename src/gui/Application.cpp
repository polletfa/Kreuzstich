#include "Application.hpp"

// gui
#include "gui/MainWindow.hpp"

// common
#include "common/Version.hpp"
#include "common/I18n.hpp"

// Qt
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#ifdef DEBUG
#  include <QDirIterator>
#endif

int Application::main(int argc, char** argv) {
    QApplication app(argc, argv);

#ifdef DEBUG
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
#endif

    // load translations for: the GUI, the creator, and Qt
    auto translators = I18n::loadTranslations({":/i18n/gui/", ":/i18n/creator/", "qtbase_"});

    MainWindow win;
    win.show();
    return app.exec();
}

void Application::replaceVersionVars(QWidget* win) {
    if(win != nullptr) {
        QString title = win->windowTitle();
        win->setWindowTitle(Version::replaceVersionVars(title));
    }
}

void Application::replaceVersionVars(QAction* action) {
    if(action != nullptr) {
        QString text = action->text(),
            iconText = action->iconText(),
            toolTip = action->toolTip();
        action->setText(Version::replaceVersionVars(text));
        action->setIconText(Version::replaceVersionVars(iconText));
        action->setToolTip(Version::replaceVersionVars(toolTip));
    }
}

void Application::replaceVersionVars(QLabel* label) {
    if(label != nullptr) {
        QString text = label->text();
        label->setText(Version::replaceVersionVars(text));
    }
}
