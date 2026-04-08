#include "I18n.hpp"

// Qt
#include <QCoreApplication>
#include <QLocale>

std::vector<std::unique_ptr<QTranslator>> I18n::loadTranslations(const QStringList& prefixes) {
    std::vector<std::unique_ptr<QTranslator>> translators;

    if(auto app = QCoreApplication::instance(); app == nullptr) {
        return translators; // empty list if the application doesn't exist yet
    } else {
        const QStringList uiLanguages = QLocale::system().uiLanguages();

        for(auto prefix: prefixes) {
            auto translator = std::make_unique<QTranslator>();
            for (const QString &locale : uiLanguages) {
                const QString name = QLocale(locale).name();
                if (translator->load(prefix + name)) {
                    app->installTranslator(translator.get());
                    translators.push_back(std::move(translator));
                    break;
                }
            }
        }

        return translators;
    }
}
