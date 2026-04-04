#include "gui/MainWindow.hpp"

// Qt
#include <QApplication>
#include <QTranslator>
#include <QLocale>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // load language
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        if (translator.load(":/i18n/" + QLocale(locale).name())) {
            app.installTranslator(&translator);
            break;
        }
    }

    // Display main window
    MainWindow win;
    win.show();

    // Start event loop
    return app.exec();
}
