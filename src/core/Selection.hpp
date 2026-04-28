/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef SELECTION_HPP
#define SELECTION_HPP

#include "ColorSpace.hpp"
class Pattern;

// STL
#include <limits>
#include <cstdlib>

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

    /**
     * Iterates over the list of indexes that belong to the selection
     */
    class Iterator {
    public:
        explicit Iterator(const Selection& m_parent);

        size_t operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& rhs) const;

    protected:
        size_t m_patternWidth, m_patternHeight; /**< Dimensions of the pattern to which the selection applies */
        const ColorSpace::ColorRGBA* m_pixelBufferAddr; /**< Used only to compare iterators */
        const Rectangle& m_selection;
        size_t m_x, m_y; /**< Current position */
    };
    class IteratorEnd: public Iterator {
    public:
        explicit IteratorEnd(const Selection& m_parent);
    };

    explicit Selection(const Pattern& pattern);
    Selection(const Pattern& pattern, const Rectangle& area);

    Iterator begin() const; /**< Iterate over all pixels in the selection */
    Iterator end() const;   /**< Iterate over all pixels in the selection */

private:
    size_t m_patternWidth, m_patternHeight; /**< Dimensions of the pattern to which the selection applies */
    const ColorSpace::ColorRGBA* m_pixelBufferAddr; /**< Used only to compare iterators */
    Rectangle m_selection;
};

#endif // SELECTION_HPP
