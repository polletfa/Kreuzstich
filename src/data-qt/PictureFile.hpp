/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef PICTUREFILE_HPP
#define PICTUREFILE_HPP

// core
#include "core/Pattern.hpp"

// STL
#include <expected>

// Qt
#include <QString>
#include <QByteArray>
#include <QImage>

/**
 * Helper functions to load picture files and convert between QImage and Pattern::PixelBuffer
 */
namespace PictureFile {

/**
 * Load a picture file without parsing (just load the content in memory)
 * Return error string on error.
 */
[[nodiscard]] std::expected<QByteArray,QString> loadFile(const QString& filePath);

/**
 * Prepare the image: load, resize and convert to Pattern::PixelBuffer
 * Don't resize if resize = {0, 0}
 */
[[nodiscard]] Pattern::PixelBuffer prepareImage(const QByteArray& imageFile, const QSize& resize);

/**
 * Prepare the image: load, resize and convert to Pattern::PixelBuffer
 */
[[nodiscard]] Pattern::PixelBuffer prepareImage(const QImage& image, const QSize& resize);

/**
 * Convert a pixel buffer into a QImage. The QImage uses the original buffer.
 * To get an independent QImage object, use QImage::copy on the result.
 */
[[nodiscard]] QImage asImage(const Pattern::PixelBuffer& pixelBuffer);

}

#endif // PICTUREFILE_HPP
