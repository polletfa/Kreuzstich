#include "FileLocator.hpp"
#include "StandardFileSystem.hpp"

// STL
#include <filesystem>

FileLocator::FileLocator(std::shared_ptr<IFileSystem> fsWrapper)
    : m_filesystem(fsWrapper == nullptr ? std::shared_ptr<IFileSystem>{new StandardFileSystem} : fsWrapper)
{}

std::optional<std::string> FileLocator::findConfigFile() {
    return findFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
};

std::optional<std::string> FileLocator::findStateFile() {
    return findFile(QStandardPaths::StateLocation, STATE_FILE);
}

std::vector<std::string> FileLocator::findThreadLists() {
    return findAllFiles(QStandardPaths::AppDataLocation, THREADLISTS_EXTENSION);
}

std::string FileLocator::getPathForWritableConfigFile() {
    return getPathForWritableFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
}

std::string FileLocator::getPathForWritableStateFile() {
    return getPathForWritableFile(QStandardPaths::StateLocation, STATE_FILE);
}

std::string FileLocator::getPathForWritableThreadListFile(const std::string& basename) {
    return getPathForWritableFile(QStandardPaths::AppDataLocation, basename.ends_with(THREADLISTS_EXTENSION) ? basename : (basename+THREADLISTS_EXTENSION));
}

std::optional<std::string> FileLocator::findFile(QStandardPaths::StandardLocation location, const std::string& basename) {
    for(const QString& path: QStandardPaths::standardLocations(location)) {
        std::filesystem::path filepath{path.toStdString()};
        filepath /= basename;
        if(m_filesystem->isRegularFile(filepath)) {
            return filepath;
        }
    }
    return {}; // not found
}

std::vector<std::string> FileLocator::findAllFiles(QStandardPaths::StandardLocation location, const std::string& extension) {
    std::vector<std::string> files;
    for(const QString& path: QStandardPaths::standardLocations(location)) {
        for(const auto& entry: m_filesystem->listDirectory(path.toStdString())) {
            if(entry.ends_with(extension) && m_filesystem->isRegularFile(entry)) {
                files.push_back(entry);
            }
        }
    }
    return files;
}

std::string FileLocator::getPathForWritableFile(QStandardPaths::StandardLocation location, const std::string& basename) {
    std::filesystem::path filepath{QStandardPaths::writableLocation(location).toStdString()};
    filepath /= basename;
    return filepath;
}
