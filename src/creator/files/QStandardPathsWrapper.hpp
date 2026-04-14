/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef QSTANDARDPATHWRAPPER_HPP
#define QSTANDARDPATHWRAPPER_HPP

#include "IQStandardPathsWrapper.hpp"

/**
 * Wrapper for QStandardPaths.
 * For testing, use Mockup_QStandardPathsWrapper instead
 * @see IQStandardPathsWrapper
 */
class QStandardPathsWrapper: public IQStandardPathsWrapper {
public:
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;
};

#endif // QSTANDARDPATHWRAPPER_HPP
