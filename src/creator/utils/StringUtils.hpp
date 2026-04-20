/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

// STL
#include <string_view>

namespace StringUtils {

std::string_view removeComment(std::string_view str, const char* delimiter);
std::string_view trim(std::string_view str);

}

#endif // STRINGUTILS_HPP
