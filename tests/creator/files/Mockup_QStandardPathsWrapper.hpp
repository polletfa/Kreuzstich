/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef MOCKUP_QSTANDARDPATHWRAPPER_HPP
#define MOCKUP_QSTANDARDPATHWRAPPER_HPP

#include "../../MockupBase.hpp"

#include "creator/files/IQStandardPathsWrapper.hpp"

/**
 * Mockup for QStandardPathsWrapper.
 * @see QStandardPathWrapper, IQStandardPathsWrapper
 */
class Mockup_QStandardPathsWrapper: public MockupBase, public IQStandardPathsWrapper {
public:
    // MockupBase
    void SetUp() override;

    // IQStandardPathsWrapper
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;

private:
    QString m_root;
};

#endif // MOCKUP_QSTANDARDPATHWRAPPER_HPP
