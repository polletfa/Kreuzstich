/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef FILELOCATOR_HPP
#define FILELOCATOR_HPP

#include "IQStandardPathsWrapper.hpp"

// STL
#include <string>
#include <vector>
#include <optional>

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
    std::optional<std::string> findConfigFile();

    /**
     * Go through all applicable directories and returns the first state file found (if any)
     */
    std::optional<std::string> findStateFile();

    /**
     * Go through all applicable directories and returns all threadlists files found (if any).
     */
    std::vector<std::string> findThreadLists();

    /**
     * Get the path to use to write a new config file
     * (will use user-writable directory, might supersede config files in system directories)
     */
    std::string getPathForWritableConfigFile();

    /**
     * Get the path to use to write a new state file
     * (will use user-writable directory, might supersede state files in system directories)
     */
    std::string getPathForWritableStateFile();

    /**
     * Get the path to use to write a new threadlist file
     */
    std::string getPathForWritableThreadListFile(const std::string& basename);

private:
    constexpr static std::string CONFIG_FILE{"config.xml"};
    constexpr static std::string STATE_FILE{"state.xml"};
    constexpr static std::string THREADLISTS_EXTENSION{".threads"};

    std::shared_ptr<IQStandardPathsWrapper> m_standardPath;  /**< Wrapper for QStandardPaths */

    std::optional<std::string> findFile(QStandardPaths::StandardLocation location, const std::string& basename);
    std::vector<std::string> findAllFiles(QStandardPaths::StandardLocation location, const std::string& extension);
    std::string getPathForWritableFile(QStandardPaths::StandardLocation location, const std::string& basename);
};

#endif // FILELOCATOR_HPP
