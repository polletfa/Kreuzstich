/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Version.hpp"

// STL
#include <sstream>
#include <iomanip>
#include <vector>

// Qt
#include <QFile>
#include <QTextStream>

namespace Version {

std::string getVersionString() {
    static std::string versionString;
    if(versionString.empty()) {
        std::locale::global(std::locale(""));
        std::tm* tm_info = std::localtime(&BUILD_TIME);
        std::ostringstream oss;
        oss << NAME
           << " " << MAJOR << "." << MINOR
           << " " << (RELEASE_BUILD ? "release" : "debug");
        if(GIT_COMMIT[0]) {
            oss << " " << GIT_COMMIT.substr(0, 8);
        }
        oss << " " << std::put_time(tm_info, "%x %X");
        versionString = oss.str();
    }
    return versionString;
}

}

const std::string Version::VERSION_STRING = Version::getVersionString();

std::string Version::replaceVersionVars(std::string& str) {
    std::vector<std::pair<std::string_view, std::string_view>> variables {
        {"$NAME$", Version::NAME},
        {"$WEBSITE$", Version::WEBSITE},
        {"$MAJOR$", std::to_string(Version::MAJOR)},
        {"$MINOR$", std::to_string(Version::MINOR)},
        {"$BUILD_TIME$", std::to_string(Version::BUILD_TIME)},
        {"$GIT_COMMIT$", Version::GIT_COMMIT},
        {"$RELEASE_BUILD$", Version::RELEASE_BUILD ? "true" : "false"},
        {"$VERSION_STRING$", Version::VERSION_STRING}
    };

    for(const auto& var: variables) {
        for(size_t pos = str.find(var.first) ; pos != std::string::npos ; pos = str.find(var.first, pos + var.second.size())) {
            str.replace(pos, var.first.size(), var.second);
        }
    }
    return str;
}

std::optional<std::string> Version::getLicense() {
    QFile license{":/LICENSE"};
    if(license.open(QIODevice::ReadOnly)) {
        QTextStream in(&license);
        return in.readAll().toStdString();
    } else {
        return {};
    }
}
