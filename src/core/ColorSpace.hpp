/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef COLORSPACE_HPP
#define COLORSPACE_HPP

// STL
#include <cstdint>

/**
 * Datatypes and methods to handle color arithmetic:
 * - Convert between color spaces (RGB/RGBA for input/display, HSL for sorting, CIELAB for distance)
 * - Compute distance
 */
namespace ColorSpace {

/**
 * (s)RGBA color space
 */
struct ColorRGBA {
    uint8_t red{255};
    uint8_t green{255};
    uint8_t blue{255};
    uint8_t alpha{255};
};
static_assert(sizeof(ColorRGBA) == 4);
bool operator==(const ColorRGBA& lhs, const ColorRGBA& rhs);

/**
 * HSL color space (for sorting)
 */
struct ColorHSL {
    double hue;
    double saturation;
    double lightness;
};

/**
 * CIELAB colorspace (for distance)
 * D65 standard illuminant - 2° observer (CIE 1931)
 */
struct ColorLAB {
    double lightness;
    double a;          /**< green <-> red axis */
    double b;          /**< blue <-> yellow axis */
};

/**
 * Convert RGBA to simple RGB (a = 100%) by using the specified background color.
 */
[[nodiscard]] ColorRGBA compositeRGBAOntoBackground(const ColorRGBA& rgba, const ColorRGBA& bg);

/**
 * Convert RGBA to HSL
 * If alpha is not 100%, assume white background (@see compositeRGBAOntoBackground)
 *
 * See:
 * - https://en.wikipedia.org/wiki/HSL_and_HSV
 */
[[nodiscard]] ColorHSL toHSL(const ColorRGBA& rgba);

/**
 * Convert RGBA to CIELAB using standard illuminant D65 and 2° observer (CIE1931)
 * If alpha is not 100%, assume white background (@see compositeRGBAOntoBackground)
 *
 * See:
 * - http://www.brucelindbloom.com/
 * - https://en.wikipedia.org/wiki/CIELAB_color_space
 */
[[nodiscard]] ColorLAB toLAB(const ColorRGBA& rgba);

enum class DistanceAlgo { CIE1976, CIEDE2000 }; /**< Algorithms for distance computation */

/**
 * Compute the distance between two colors in the LAB space using CIEDE2000
 *
 * See:
 * - http://www.brucelindbloom.com/
 */
[[nodiscard]] double distance(const ColorLAB& color1, const ColorLAB& color2, DistanceAlgo algo);

}

#endif // COLORSPACE_HPP
