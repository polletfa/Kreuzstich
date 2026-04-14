#ifndef ISTANDARDPATHS_HPP
#define ISTANDARDPATHS_HPP

// Qt
#include <QStandardPaths>

/**
 * Interface for standard paths operations for easy mocking in unit tests
 */
class IStandardPaths {
public:
    virtual ~IStandardPaths() = default;

    virtual QStringList standardLocations(QStandardPaths::StandardLocation location) = 0;
    virtual QString writableLocation(QStandardPaths::StandardLocation location) = 0;
};

#endif // ISTANDARDPATHS_HPP
