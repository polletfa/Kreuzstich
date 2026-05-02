/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/Version.hpp"

EMSCRIPTEN_BINDINGS(Version) {
    emscripten::constant("Version_NAME", std::string{Version::NAME});
    emscripten::constant("Version_WEBSITE", std::string{Version::WEBSITE});
    emscripten::constant("Version_MAJOR", Version::MAJOR);
    emscripten::constant("Version_MINOR", Version::MINOR);
    emscripten::constant("Version_BUILD_TIME", std::string{Version::BUILD_TIME});
    emscripten::constant("Version_GIT_COMMIT", std::string{Version::GIT_COMMIT});
    emscripten::constant("Version_RELEASE_BUILD", Version::RELEASE_BUILD);
    emscripten::constant("Version_LICENSE", std::string{Version::LICENSE});

    emscripten::function("Version_getVersionString", &Version::getVersionString);
    emscripten::function("Version_replaceVersionVars", emscripten::optional_override([](std::string str) {
        return Version::replaceVersionVars(str);
    }));
}
