/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef I18N_HPP
#define I18N_HPP

// STL
#include <vector>
#include <memory>

// Qt
#include <QStringList>
#include <QTranslator>

/**
 * Internationalization is done through the QtLinguist tool.
 * All strings requiring translation must be wrapped inside tr() (literal strings only)
 *
 * Each component (creator and application(s)) has its own translation file provided in:
 * - resources/i18n/COMPONENT/LOCALE.ts
 * The TS files are build directly into the binary as a resource.
 *
 * When starting the program, I18n::loadTranslations must be called and will:
 * - Load the translations for the creator in the current system locale.
 * - Load any additional translations provided as parameter.
 *   For example, the gui component will need to load it's own translation file as well as the Qt standard translations.
 *
 * To add new translation strings:
 * - Build the program. It will call lupdate and update the *.ts files
 * - Use QtLinguist to translate any new string found.
 * - Build the program again.
 *
 * To add a new language:
 * - For each component:
 *   - Create an empty *.ts file with just the root element (no translations)
 *   - Add it in CMakeLists.txt
 * - Proceed as specified above ("add new translation strings")
 */
namespace I18n {

/**
 * Loads translations depending on the system locale.
 *
 * @param additionalTranslationFiles By default, the method only loads the translations for the creator lib. Additional translations
 *                                   for the GUI can be specified with this parameter. The method will then search for a translation
 *                                   file <item><locale_name> (without separator) for each item of the list.
 * @returns List of installed translators.
 */
std::vector<std::unique_ptr<QTranslator>> loadTranslations(const QStringList& additionalTranslationFiles = {});

}

#endif // I18N_HPP
