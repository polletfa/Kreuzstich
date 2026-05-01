/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Version.hpp"

// STL
#include <sstream>
#include <chrono>
#include <vector>
#include <utility>

[[nodiscard]] std::string Version::getVersionString() {
    static std::string versionString;
    if(versionString.empty()) {
        std::ostringstream oss;
        oss << NAME
            << " " << std::to_string(MAJOR) << "." << std::to_string(MINOR);
        if(!GIT_COMMIT.empty()) {
            oss << " commit " << GIT_COMMIT.substr(0, 8);
        }
        oss << (RELEASE_BUILD ? "" : " debug")
            << " build " << std::format("{:%Y-%m-%d %H:%M:%SZ}", std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::from_time_t(BUILD_TIME)));
        versionString = oss.str();
    }
    return versionString;
}

std::string Version::replaceVersionVars(std::string& str) {
    const std::string major{std::to_string(MAJOR)};
    const std::string minor{std::to_string(MINOR)};
    const std::string buildTime{std::to_string(BUILD_TIME)};
    std::vector<std::pair<std::string_view, std::string_view>> variables {
        {"$NAME$", NAME},
        {"$WEBSITE$", WEBSITE},
        {"$MAJOR$", major},
        {"$MINOR$", minor},
        {"$BUILD_TIME$", buildTime},
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
