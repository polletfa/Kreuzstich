/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "PictureFile.hpp"

// STL
#include <vector>

// Qt
#include <QFile>
#include <QColorSpace>

std::expected<QByteArray,QString> PictureFile::loadFile(const QString& filePath) {
    if(QFile file{filePath}; file.open(QFile::OpenModeFlag::ReadOnly)) {
        QByteArray content = file.readAll();
        file.close();
        return content;
    } else {
        return std::unexpected(file.errorString());
    }
}

Pattern::PixelBuffer PictureFile::prepareImage(const QByteArray& imageFile, const QSize& resize) {
    return prepareImage(QImage::fromData(imageFile), resize);
}

Pattern::PixelBuffer PictureFile::prepareImage(const QImage& image, const QSize& resize) {
    // resize
    QImage scaled = image.scaled(resize.width(), resize.height());

    // Convert color space
    if(scaled.colorSpace().isValid() && scaled.colorSpace() != QColorSpace(QColorSpace::SRgb)) {
        scaled.convertToColorSpace(QColorSpace::SRgb);
    }

    // Convert to PixelBuffer
    QImage rgba = scaled.convertToFormat(QImage::Format_RGBA8888);
    ColorSpace::ColorRGBA* data = reinterpret_cast<ColorSpace::ColorRGBA*>(rgba.bits());
    return Pattern::PixelBuffer{
        {data, data + rgba.width() * rgba.height()},
        static_cast<size_t>(rgba.width()),
        static_cast<size_t>(rgba.height())
    };
}

QImage PictureFile::getImage(const Pattern::PixelBuffer& buffer) {
    auto copy = new std::vector<ColorSpace::ColorRGBA>{buffer.pixels};
    return QImage(reinterpret_cast<uchar*>(copy->data()), buffer.width, buffer.height, buffer.width*4, QImage::Format_RGBA8888,
           [](void* ptr) { delete static_cast<std::vector<ColorSpace::ColorRGBA>*>(ptr); },
           copy);
}
