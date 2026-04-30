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
    // resize, unless resize = {0, 0} or resize = current size
    QImage scaled = (resize.width() == 0 && resize.height() == 0) || (resize.width() == image.width() && resize.height() == image.height())
        ? image
        : image.scaled(resize.width(), resize.height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

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

QImage PictureFile::asImage(const Pattern::PixelBuffer& buffer) {
    return QImage(reinterpret_cast<const uchar*>(buffer.pixels.data()), buffer.width, buffer.height, buffer.width*4, QImage::Format_RGBA8888);
}
