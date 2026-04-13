#include "StandardFileSystem.hpp"

bool StandardFileSystem::isRegularFile(const std::filesystem::path& path) {
    return std::filesystem::is_regular_file(path);
}

std::vector<std::string> StandardFileSystem::listDirectory(const std::filesystem::path& path) {
    std::vector<std::string> list;
    for(const auto& entry: std::filesystem::directory_iterator{path}) {
        list.push_back(entry.path());
    }
    return list;
}
