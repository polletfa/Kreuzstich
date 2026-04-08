#ifndef I18N_HPP
#define I18N_HPP

// STL
#include <vector>
#include <memory>

// Qt
#include <QStringList>
#include <QTranslator>

class I18n {
public:
    /**
     * Loads translations depending on the system locale.
     *
     * @param prefixes List of prefixes. For each prefix, the method will try to find and load
     *                 a translation file <prefix><locale_name>
     * @returns List of installed translators.
     */
    static std::vector<std::unique_ptr<QTranslator>> loadTranslations(const QStringList& prefixes);
};

#endif // I18N_HPP
