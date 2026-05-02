/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef QSTANDARDPATHWRAPPER_MOCK_HPP
#define QSTANDARDPATHWRAPPER_MOCK_HPP

#include "Mockup.hpp"

#include "data-desktop/IQStandardPathsWrapper.hpp"

/**
 * Mockup for QStandardPathsWrapper.
 * @see QStandardPathWrapper, IQStandardPathsWrapper
 */
class QStandardPathsWrapper_mock: public Mockup, public IQStandardPathsWrapper {
public:
    // IQStandardPathsWrapper
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;
};

#endif // QSTANDARDPATHWRAPPER_MOCK_HPP
