/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef PICTURE_HPP
#define PICTURE_HPP

#include "ColorSpace.hpp"

// STL
#include <vector>
#include <cstdlib>
#include <utility>

namespace Picture {

enum FileFormat {JPEG, PNG, BMP, TGA, PSD, HDR, PIC, GIF, PNM};

/**
 * Buffer containing the content of a picture file
 */
using FileBuffer = std::vector<uint8_t>;

/**
 * Buffer containing a list of RGBA pixels
 */
struct PixelBuffer {
    std::vector<ColorSpace::ColorRGBA> pixels;
    size_t width;
    size_t height;
};

std::pair<PixelBuffer, FileFormat> readFile(const FileBuffer& fileContent);
FileBuffer writeFile(const PixelBuffer& pixelBuffer, FileFormat format);
PixelBuffer resize(const PixelBuffer, size_t newWidth, size_t newHeight);

}

#endif // PICTURE_HPP
