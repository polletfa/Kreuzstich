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
std::expected<QByteArray,QString> loadFile(const QString& filePath);

/**
 * Prepare the image: load, resize and convert to Pattern::PixelBuffer
 */
Pattern::PixelBuffer prepareImage(const QByteArray& imageFile, const QSize& resize);

/**
 * Prepare the image: load, resize and convert to Pattern::PixelBuffer
 */
Pattern::PixelBuffer prepareImage(const QImage& image, const QSize& resize);

/**
 * Get a QImage from a Pattern::PixelBuffer
 */
QImage getImage(const Pattern::PixelBuffer& pixelBuffer);

}

#endif // PICTUREFILE_HPP
