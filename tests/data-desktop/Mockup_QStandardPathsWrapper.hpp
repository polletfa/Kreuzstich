/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef MOCKUP_QSTANDARDPATHWRAPPER_HPP
#define MOCKUP_QSTANDARDPATHWRAPPER_HPP

#include "../Mockup.hpp"

#include "data-desktop/IQStandardPathsWrapper.hpp"

/**
 * Mockup for QStandardPathsWrapper.
 * @see QStandardPathWrapper, IQStandardPathsWrapper
 */
class Mockup_QStandardPathsWrapper: public Mockup, public IQStandardPathsWrapper {
public:
    // IQStandardPathsWrapper
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;
};

#endif // MOCKUP_QSTANDARDPATHWRAPPER_HPP
