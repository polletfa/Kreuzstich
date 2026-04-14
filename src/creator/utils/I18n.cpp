/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "I18n.hpp"

// Qt
#include <QCoreApplication>
#include <QLocale>

namespace I18n {
constexpr const char* TRANSLATION_FILES_PREFIX = ":/i18n/creator/";

std::unique_ptr<QTranslator> loadTranslation(QCoreApplication* app, QStringList uiLanguages, const QString& prefix) {
    auto translator = std::make_unique<QTranslator>();
    for (const QString &locale : uiLanguages) {
        const QString name = QLocale(locale).name();
        if (translator->load(prefix + name)) {
            app->installTranslator(translator.get());
            return translator;
            break;
        }
    }
    return nullptr;
}
}

std::vector<std::unique_ptr<QTranslator>> I18n::loadTranslations(const QStringList& additionalTranslationFiles) {
    std::vector<std::unique_ptr<QTranslator>> translators;

    if(auto app = QCoreApplication::instance(); app == nullptr) {
        return translators; // empty list if the application doesn't exist yet
    } else {
        const QStringList uiLanguages = QLocale::system().uiLanguages();

        if(auto&& translator = loadTranslation(app, uiLanguages, TRANSLATION_FILES_PREFIX); translator != nullptr) {
            translators.push_back(std::move(translator));
        }
        for(auto prefix: additionalTranslationFiles) {
            if(auto&& translator = loadTranslation(app, uiLanguages, prefix); translator != nullptr) {
                translators.push_back(std::move(translator));
            }
        }

        return translators;
    }
}
