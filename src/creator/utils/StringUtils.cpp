/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "StringUtils.hpp"

// STL
#include <cctype>
#include <algorithm>

std::string_view StringUtils::removeComment(std::string_view str, const char* delimiter) {
    return str.substr(0, str.find(delimiter));
}

std::string_view StringUtils::trim(std::string_view str) {
    auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c){ return std::isspace(c); });
    auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c){ return std::isspace(c); }).base();
    if(start >= end) {
        return std::string_view{};
    }
    return std::string_view(start, end);
}
