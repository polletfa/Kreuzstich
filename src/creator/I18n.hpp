#ifndef I18N_HPP
#define I18N_HPP

// STL
#include <vector>
#include <memory>

// Qt
#include <QStringList>
#include <QTranslator>

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
