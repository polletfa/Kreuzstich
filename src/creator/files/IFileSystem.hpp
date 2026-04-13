#ifndef IFILESYSTEM_HPP
#define IFILESYSTEM_HPP

// STL
#include <filesystem>
#include <vector>

/**
 * Interface for file system operations for easy mocking in unit tests
 */
class IFileSystem {
public:
    virtual ~IFileSystem() = default;
    virtual bool isRegularFile(const std::filesystem::path& path) = 0;
    virtual std::vector<std::string> listDirectory(const std::filesystem::path& path) = 0;
};

#endif // IFILESYSTEM_HPP
