/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Application.hpp"
#include "MainWindow.hpp"

// core
#include "core/Version.hpp"

// Qt
#include <QLibraryInfo>
#ifdef DEBUG
#  include <QDirIterator>
#endif

int Application::main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName(QString::fromStdString(std::string(Version::NAME)).toLower());

#ifdef DEBUG
    QDirIterator it(":", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        qDebug() << it.next();
    }
#endif

    // load translations for the creator + additional translations for the GUI (including Qt)
    auto translators = loadTranslations(app);

    MainWindow win;
    win.show();
    return app.exec();
}

std::vector<std::unique_ptr<QTranslator>> Application::loadTranslations(QApplication& app) {
    std::vector<std::unique_ptr<QTranslator>> translators;

    const QStringList uiLanguages = QLocale::system().uiLanguages();

    for(QString prefix: {":/i18n/gui-qt/", "qtbase_"}) {
        auto translator = std::make_unique<QTranslator>();
        for(const QString &locale : uiLanguages) {
            const QString name = QLocale(locale).name();
            if(prefix.startsWith(":/") ? translator->load(prefix + name) : translator->load(prefix + name, QLibraryInfo::path(QLibraryInfo::TranslationsPath))) {
                app.installTranslator(translator.get());
                translators.push_back(std::move(translator));
                break;
            }
        }
    }

    return translators;
}

void Application::replaceVersionVars(QWidget* win) {
    if(win != nullptr) {
        std::string title = win->windowTitle().toStdString();
        win->setWindowTitle(QString::fromStdString(Version::replaceVersionVars(title)));
    }
}

void Application::replaceVersionVars(QAction* action) {
    if(action != nullptr) {
        std::string text = action->text().toStdString(),
            iconText = action->iconText().toStdString(),
            toolTip = action->toolTip().toStdString();
        action->setText(QString::fromStdString(Version::replaceVersionVars(text)));
        action->setIconText(QString::fromStdString(Version::replaceVersionVars(iconText)));
        action->setToolTip(QString::fromStdString(Version::replaceVersionVars(toolTip)));
    }
}

void Application::replaceVersionVars(QLabel* label) {
    if(label != nullptr) {
        std::string text = label->text().toStdString();
        label->setText(QString::fromStdString(Version::replaceVersionVars(text)));
    }
}
