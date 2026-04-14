#ifndef QSTANDARDPATHWRAPPER_HPP
#define QSTANDARDPATHWRAPPER_HPP

#include "IStandardPaths.hpp"

/**
 * Wrapper for QStandardPaths.
 * Can be replaced by a mockup for unit tests (@see IStandardPaths)
 */
class QStandardPathsWrapper: public IStandardPaths {
public:
    QStringList standardLocations(QStandardPaths::StandardLocation location) override;
    QString writableLocation(QStandardPaths::StandardLocation location) override;
};

#endif // QSTANDARDPATHWRAPPER_HPP
