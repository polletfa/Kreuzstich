/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef PATTERN_HPP
#define PATTERN_HPP

#include "Thread.hpp"
#include "ThreadList.hpp"
#include "Selection.hpp"

// STL
#include <vector>
#include <cstdlib>

/**
 * Manage a pattern:
 * - Store the pattern
 * - Select area
 * - Edit
 */
class Pattern {
public:
    /**
     * Buffer containing a list of RGBA pixels
     */
    struct PixelBuffer {
        std::vector<ColorSpace::ColorRGBA> pixels;
        size_t width;
        size_t height;
    };

    constexpr static ColorSpace::ColorRGBA HIGHLIGHT{0xff, 0xff, 0, 128};

    /**
     * @param pixelBuffer Pixel buffer
     * @param threadlist Threadlist
     * @param selectThreads If true, colors in the pixel buffer are replaced by the color of the closest thread in the thread list.
     *                      Set to false when loading a saved pattern (colors already selected).
     */
    Pattern(const PixelBuffer& pixelBuffer, const ThreadList& threadlist, bool selectThreads = true);

    /**
     * Returns the threadlist
     */
    const ThreadList& threadList() const;

    /**
     * Returns the raw pixel buffer.
     */
    const PixelBuffer& get() const;

    /**
     * Returns a specific pixel
     */
    const ColorSpace::ColorRGBA& get(size_t x, size_t y) const;

    /**
     * Change the current selection.
     */
    void select(const Selection& selection);

    /**
     * Clear the selection
     */
    void unselect();

    /**
     * Compute usage for current selection sorted by decreasing usage.
     */
    ThreadList::UsageCount computeUsage() const;

    /**
     * Replace a single pixel by another thread
     * Also updates the usage statistics in the threadlist.
     */
    void replacePixel(size_t x, size_t y, const Thread& replacement);

    /**
     * Replace a thread by another in the current selection
     * Also updates the usage statistics in the threadlist.
     */
    void replaceThread(const Thread& original, const Thread& replacement);

    /**
     * Returns a copy of the pixel buffer where pixels in the selection with a specific thread are highlighted
     */
    PixelBuffer highlight(const Thread& hl) const;

private:
    PixelBuffer m_pixelBuffer;
    ThreadList m_threadList;
    Selection m_selection;
};

#endif // PATTERN_HPP
