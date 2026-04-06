#include "gui/MainWindow.hpp"

// Qt
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // load language
    // We look for a locale within the user preferences with both a custom and a Qt translation file.
    QTranslator translator, qtTranslator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString name = QLocale(locale).name();
        const bool hasCustomTranslation = translator.load(":/i18n/" + name);
        const bool hasQtTranslation = qtTranslator.load("qtbase_" + name, QLibraryInfo::path(QLibraryInfo::TranslationsPath));
        if (hasCustomTranslation && hasQtTranslation) {
            app.installTranslator(&translator);
            app.installTranslator(&qtTranslator);
            break;
        }
    }

    // Display main window
    MainWindow win;
    win.show();

    // Start event loop
    return app.exec();
}
