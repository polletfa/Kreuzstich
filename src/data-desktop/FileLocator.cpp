/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "FileLocator.hpp"
#include "QStandardPathsWrapper.hpp"

// STL
#include <algorithm>

// Qt
#include <QFileInfo>
#include <QDirListing>

FileLocator::FileLocator(std::shared_ptr<IQStandardPathsWrapper> standardPathWrapper)
    : m_standardPath(standardPathWrapper == nullptr ? std::make_shared<QStandardPathsWrapper>() : standardPathWrapper)
{}

std::optional<QString> FileLocator::findConfigFile() {
    return findFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
};

std::optional<QString> FileLocator::findStateFile() {
    return findFile(QStandardPaths::StateLocation, STATE_FILE);
}

QStringList FileLocator::findThreadLists() {
    return findAllFiles(QStandardPaths::AppDataLocation, THREADLISTS_EXTENSION);
}

QString FileLocator::getPathForWritableConfigFile() {
    return getPathForWritableFile(QStandardPaths::AppConfigLocation, CONFIG_FILE);
}

QString FileLocator::getPathForWritableStateFile() {
    return getPathForWritableFile(QStandardPaths::StateLocation, STATE_FILE);
}

QString FileLocator::getPathForWritableThreadListFile(const QString& basename) {
    return getPathForWritableFile(QStandardPaths::AppDataLocation, basename.endsWith(THREADLISTS_EXTENSION) ? basename : (basename+THREADLISTS_EXTENSION));
}

std::optional<QString> FileLocator::findFile(QStandardPaths::StandardLocation location, const QString& basename) {
    for(const QString& path: m_standardPath->standardLocations(location)) {
        QFileInfo filepath{path + "/" + basename};
        if(filepath.isFile()) {
            return filepath.filePath();
        }
    }
    return {}; // not found
}

QStringList FileLocator::findAllFiles(QStandardPaths::StandardLocation location, const QString& extension) {
    QStringList files;
    for(const QString& path: m_standardPath->standardLocations(location)) {
        try {
            QStringList filesCurrentDir;
            for(const auto& entry: QDirListing{path, QDirListing::IteratorFlag::FilesOnly}) {
                if(entry.filePath().endsWith(extension)) {
                    filesCurrentDir.push_back(entry.filePath());
                }
            }
            std::sort(filesCurrentDir.begin(), filesCurrentDir.end());
            for(const auto& entry: filesCurrentDir) {
                files.push_back(entry);
            }
        } catch(...) {}
    }
    return files;
}

QString FileLocator::getPathForWritableFile(QStandardPaths::StandardLocation location, const QString& basename) {
    QString filepath{m_standardPath->writableLocation(location) + "/" + basename};
    return filepath;
}
