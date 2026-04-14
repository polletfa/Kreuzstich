/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "FileLocator.hpp"
#include "QStandardPathsWrapper.hpp"

FileLocator::FileLocator(std::shared_ptr<IQStandardPathsWrapper> standardPathWrapper)
    : m_standardPath(standardPathWrapper == nullptr ? std::make_shared<QStandardPathsWrapper>() : standardPathWrapper)
{}

std::optional<std::filesystem::path> FileLocator::findConfigFile() {
    return findFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
};

std::optional<std::filesystem::path> FileLocator::findStateFile() {
    return findFile(QStandardPaths::StateLocation, STATE_FILE);
}

std::vector<std::filesystem::path> FileLocator::findThreadLists() {
    return findAllFiles(QStandardPaths::AppDataLocation, THREADLISTS_EXTENSION);
}

std::filesystem::path FileLocator::getPathForWritableConfigFile() {
    return getPathForWritableFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
}

std::filesystem::path FileLocator::getPathForWritableStateFile() {
    return getPathForWritableFile(QStandardPaths::StateLocation, STATE_FILE);
}

std::filesystem::path FileLocator::getPathForWritableThreadListFile(const std::string& basename) {
    return getPathForWritableFile(QStandardPaths::AppDataLocation, basename.ends_with(THREADLISTS_EXTENSION) ? basename : (basename+THREADLISTS_EXTENSION));
}

std::optional<std::filesystem::path> FileLocator::findFile(QStandardPaths::StandardLocation location, const std::string& basename) {
    for(const QString& path: m_standardPath->standardLocations(location)) {
        std::filesystem::path filepath{path.toStdString()};
        filepath /= basename;
        if(std::filesystem::is_regular_file(filepath)) {
            return filepath;
        }
    }
    return {}; // not found
}

std::vector<std::filesystem::path> FileLocator::findAllFiles(QStandardPaths::StandardLocation location, const std::string& extension) {
    std::vector<std::filesystem::path> files;
    for(const QString& path: m_standardPath->standardLocations(location)) {
        try {
            for(const auto& entry: std::filesystem::directory_iterator(path.toStdString())) {
                if(entry.path().string().ends_with(extension) && std::filesystem::is_regular_file(entry)) {
                    files.push_back(entry.path());
                }
            }
        } catch(...) {}
    }
    return files;
}

std::filesystem::path FileLocator::getPathForWritableFile(QStandardPaths::StandardLocation location, const std::string& basename) {
    std::filesystem::path filepath{m_standardPath->writableLocation(location).toStdString()};
    filepath /= basename;
    return filepath;
}
