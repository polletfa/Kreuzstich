/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "ColorSpace.hpp"
class Picture;

// STL
#include <limits>
#include <cstdlib>
#include <vector>

/**
 * Data structure for area selection.
 *
 * For now, an area is always a rectangle but later, more complex selection may be added,
 * which is why we use this class instead of a simple rectangle.
 */
class Selection {
public:
    struct Rectangle {
        size_t x{0};
        size_t y{0};
        size_t width{std::numeric_limits<size_t>::max()};
        size_t height{std::numeric_limits<size_t>::max()};
    };

    class Iterator {
    public:
        Iterator(Selection& m_parent, bool moveToEnd = false);

        ColorSpace::ColorRGBA& operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& rhs) const;

    private:
        std::vector<ColorSpace::ColorRGBA>& m_pixels;
        size_t m_width, m_height; /**< Dimensions of the picture */
        const Rectangle& m_selection;
        size_t m_x, m_y; /**< Current position */
    };

    Selection(Picture& picture);
    Selection(Picture& picture, const Rectangle& area);

    Iterator begin(); /**< Iterate over all pixels in the selection */
    Iterator end();   /**< Iterate over all pixels in the selection */

private:
    Picture& m_picture;
    Rectangle m_selection;
};

#endif // SELECTION_HPP
