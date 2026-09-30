/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Version.hpp"

// STL
#include <sstream>
#include <chrono>
#include <vector>
#include <utility>

[[nodiscard]] const std::string& Version::getVersionString() {
    static std::string versionString;
    if(versionString.empty()) {
        std::ostringstream oss;
        oss << NAME
            << " " << std::to_string(MAJOR) << "." << std::to_string(MINOR)
            << " " << (GIT_COMMIT.empty() ? "dev-build" : GIT_COMMIT.substr(0, 8))
            << (RELEASE_BUILD ? "" : " debug-build")
            << (BUILD_TIME.empty() ? "" : " ") << BUILD_TIME;
        versionString = oss.str();
    }
    return versionString;
}

std::string Version::replaceVersionVars(std::string& str) {
    const std::string major{std::to_string(MAJOR)};
    const std::string minor{std::to_string(MINOR)};
    std::vector<std::pair<std::string_view, std::string_view>> variables {
        {"$NAME$", NAME},
        {"$WEBSITE$", WEBSITE},
        {"$MAJOR$", major},
        {"$MINOR$", minor},
        {"$BUILD_TIME$", BUILD_TIME},
        {"$GIT_COMMIT$", GIT_COMMIT},
        {"$RELEASE_BUILD$", RELEASE_BUILD ? "true" : "false"},
        {"$VERSION_STRING$", getVersionString()},
        {"$LICENSE$", LICENSE}
    };

    for(const auto& var: variables) {
        for(size_t pos = str.find(var.first) ; pos != std::string::npos ; pos = str.find(var.first, pos + var.second.size())) {
            str.replace(pos, var.first.size(), var.second);
        }
    }
    return str;
}
