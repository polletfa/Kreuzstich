/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

// STL
#include <vector>
#include <memory>

// Qt
#include <QApplication>
#include <QAction>
#include <QLabel>
#include <QTranslator>

namespace Application {

int main(int argc, char** argv);

/**
 * Load translations
 *
 * Internationalization is done through the QtLinguist tool.
 * All strings requiring translation must be wrapped inside tr() (literal strings only)
 *
 * The translation files are provided in resources/i18n/gui-desktop/LOCALE.ts and are build
 * directly into the binary as a resource.
 *
 * To add new translation strings:
 * - Build the program. It will call lupdate and update the *.ts files
 * - Use QtLinguist to translate any new string found.
 * - Build the program again.
 *
 * To add a new language:
 * - Create an empty *.ts file with just the root element (no translations)
 * - Add it in CMakeLists.txt
 * - Proceed as specified above ("add new translation strings")
 */
[[nodiscard]] std::vector<std::unique_ptr<QTranslator>> loadTranslations(QApplication& app);

/**
 * @copydoc Version::replaceVersionVars(QString&)
 * @param win Widget - call replaceVersionVars on specific properties of the widget
 */
void replaceVersionVars(QWidget* win);

/**
 * @copydoc Version::replaceVersionVars(QString&)
 * @param action Action Widget - call replaceVersionVars on specific properties of the widget
 */
void replaceVersionVars(QAction* action);

/**
 * @copydoc Version::replaceVersionVars(QString&)
 * @param label Label Widget - call replaceVersionVars on specific properties of the widget
 */
void replaceVersionVars(QLabel* label);

}

#endif // APPLICATION_HPP
