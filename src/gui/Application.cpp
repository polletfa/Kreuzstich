/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Application.hpp"
#include "MainWindow.hpp"

// creator
#include "creator/utils/Version.hpp"
#include "creator/utils/I18n.hpp"

// Qt
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

#include <QStandardPaths>
#ifdef DEBUG
#  include <QDirIterator>
#endif

int Application::main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName(QString(Version::NAME.data()).toLower());

#ifdef DEBUG
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
#endif

    // load translations for the creator + additional translations for the GUI (including Qt)
    auto translators = I18n::loadTranslations({":/i18n/gui/", "qtbase_"});

    MainWindow win;
    win.show();
    return app.exec();
}

void Application::replaceVersionVars(QWidget* win) {
    if(win != nullptr) {
        std::string title = win->windowTitle().toStdString();
        win->setWindowTitle(Version::replaceVersionVars(title).data());
    }
}

void Application::replaceVersionVars(QAction* action) {
    if(action != nullptr) {
        std::string text = action->text().toStdString(),
            iconText = action->iconText().toStdString(),
            toolTip = action->toolTip().toStdString();
        action->setText(Version::replaceVersionVars(text).data());
        action->setIconText(Version::replaceVersionVars(iconText).data());
        action->setToolTip(Version::replaceVersionVars(toolTip).data());
    }
}

void Application::replaceVersionVars(QLabel* label) {
    if(label != nullptr) {
        std::string text = label->text().toStdString();
        label->setText(Version::replaceVersionVars(text).data());
    }
}
