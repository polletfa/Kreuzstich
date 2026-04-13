#ifndef STANDARDFILESYSTEM_HPP
#define STANDARDFILESYSTEM_HPP

#include "IFileSystem.hpp"

/**
 * FileSystem wrapper class over std::filesystem
 * @see FileSystem
 */
class StandardFileSystem: public IFileSystem {
public:
    bool isRegularFile(const std::filesystem::path& path) override;
    std::vector<std::string> listDirectory(const std::filesystem::path& path) override;
};

#endif // STANDARDFILESYSTEM_HPP
