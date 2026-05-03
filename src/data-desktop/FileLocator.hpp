/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef FILELOCATOR_HPP
#define FILELOCATOR_HPP

#include "IQStandardPathsWrapper.hpp"

// STL
#include <optional>
#include <memory>

// Qt
#include <QString>
#include <QStringList>

/**
 * Class used to locate config/data files using the standard Qt search paths:
 * - Configuration file in AppConfigLocation
 * - State file in StateLocation
 * - Threadlist files in AppDataLocation
 */
class FileLocator {
public:
    /**
     * @param standardPathWrapper Wrapper for QStandardPaths, so that it can be replaced by a mockup for unit tests
     *                            Default: use QStandardPathsWrapper
     */
    explicit FileLocator(std::shared_ptr<IQStandardPathsWrapper> standardPathWrapper = nullptr);

    /**
     * Go through all applicable directories and returns the first config file found (if any)
     */
    [[nodiscard]] std::optional<QString> findConfigFile();

    /**
     * Go through all applicable directories and returns the first state file found (if any)
     */
    [[nodiscard]] std::optional<QString> findStateFile();

    /**
     * Go through all applicable directories and returns all threadlists files found (if any).
     */
    [[nodiscard]] QStringList findThreadLists();

    /**
     * Get the path to use to write a new config file
     * (will use user-writable directory, might supersede config files in system directories)
     */
    [[nodiscard]] QString getPathForWritableConfigFile();

    /**
     * Get the path to use to write a new state file
     * (will use user-writable directory, might supersede state files in system directories)
     */
    [[nodiscard]] QString getPathForWritableStateFile();

    /**
     * Get the path to use to write a new threadlist file
     */
    [[nodiscard]] QString getPathForWritableThreadListFile(const QString& basename);

private:
    constexpr static const char* CONFIG_FILE{"config.xml"};
    constexpr static const char* STATE_FILE{"state.xml"};
    constexpr static const char* THREADLISTS_EXTENSION{".threads"};

    std::shared_ptr<IQStandardPathsWrapper> m_standardPath;  /**< Wrapper for QStandardPaths */

    [[nodiscard]] std::optional<QString> findFile(QStandardPaths::StandardLocation location, const QString& basename);
    [[nodiscard]] QStringList findAllFiles(QStandardPaths::StandardLocation location, const QString& extension);
    [[nodiscard]] QString getPathForWritableFile(QStandardPaths::StandardLocation location, const QString& basename);
};

#endif // FILELOCATOR_HPP
