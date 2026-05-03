/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef IQSTANDARDPATHSWRAPPER_HPP
#define IQSTANDARDPATHSWRAPPER_HPP

// Qt
#include <QStandardPaths>

/**
 * Interface for QStandardPathsWrapper and Mockup_QStandardPathsWrapper
 * - QStandardPathWrapper: standard implementation using the real QStandardPath
 * - Mockup_QStandardPathsWrapper: mockup for unit tests
 */
class IQStandardPathsWrapper {
public:
    virtual ~IQStandardPathsWrapper() = default;

    [[nodiscard]] virtual QStringList standardLocations(QStandardPaths::StandardLocation location) = 0;
    [[nodiscard]] virtual QString writableLocation(QStandardPaths::StandardLocation location) = 0;
};

#endif // IQSTANDARDPATHSWRAPPER_HPP
