#include "FileLocator.hpp"
#include "QStandardPathsWrapper.hpp"

// STL
#include <filesystem>

FileLocator::FileLocator(std::shared_ptr<IStandardPaths> standardPathWrapper)
    : m_standardPath(standardPathWrapper == nullptr ? std::make_shared<QStandardPathsWrapper>() : standardPathWrapper)
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
    for(const QString& path: m_standardPath->standardLocations(location)) {
        std::filesystem::path filepath{path.toStdString()};
        filepath /= basename;
        if(std::filesystem::is_regular_file(filepath)) {
            return filepath;
        }
    }
    return {}; // not found
}

std::vector<std::string> FileLocator::findAllFiles(QStandardPaths::StandardLocation location, const std::string& extension) {
    std::vector<std::string> files;
    for(const QString& path: m_standardPath->standardLocations(location)) {
        for(const auto& entry: std::filesystem::directory_iterator(path.toStdString())) {
            if(entry.path().string().ends_with(extension) && std::filesystem::is_regular_file(entry)) {
                files.push_back(entry.path());
            }
        }
    }
    return files;
}

std::string FileLocator::getPathForWritableFile(QStandardPaths::StandardLocation location, const std::string& basename) {
    std::filesystem::path filepath{m_standardPath->writableLocation(location).toStdString()};
    filepath /= basename;
    return filepath;
}
