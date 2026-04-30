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

    /**
     * @param pixelBuffer Pixel buffer
     * @param threadlist Threadlist
     * @param selectThreads If true, colors in the pixel buffer are replaced by the color of the closest thread in the thread list.
     *                      Set to false when loading a saved pattern (colors already selected).
     * @param algo Algorithm to use for distance calculations.
     */
    Pattern(const PixelBuffer& pixelBuffer, const ThreadList& threadlist, bool selectThreads = true, ColorSpace::DistanceAlgo algo = ColorSpace::CIEDE2000);

    /**
     * Returns the threadlist
     */
    [[nodiscard]] const ThreadList& threadList() const;

    /**
     * Returns the raw pixel buffer.
     */
    [[nodiscard]] const PixelBuffer& get() const;

    /**
     * Returns a specific pixel
     */
    [[nodiscard]] const ColorSpace::ColorRGBA& get(size_t x, size_t y) const;

    /**
     * Returns the picture as a grid (each pixel from the original picture is replaced by a square with black border)
     */
    [[nodiscard]] const PixelBuffer& grid() const;

    /**
     * Change the current selection.
     *
     * By default, the whole picture is selected, until this method is called with a smaller area.
     * You can restore the default selection by calling select without parameter.
     * @note For now we can only select a rectangle, but later more complex selection may be added.
     */
    void select(const Selection::Rectangle& selection = {});

    /**
     * Compute usage for current selection sorted by decreasing usage.
     *
     * @see select
     */
    [[nodiscard]] ThreadList::UsageCount computeUsage() const;

    /**
     * Replace a single pixel by another thread
     */
    void replacePixel(size_t x, size_t y, const Thread& replacement);

    /**
     * Replace a thread by another in the current selection
     *
     * @see select
     */
    void replaceThread(const Thread& original, const Thread& replacement);

    /**
     * Create a layer to put on top of the grid to highlight a specific thread within the selection.
     * This isn't the full grid, just the highlighting layer where the selected thread is replaced by the highlight color
     * and all other pixels are fully tranparent.
     *
     * @see select
     */
    [[nodiscard]] PixelBuffer highlight(const Thread& thread, const ColorSpace::ColorRGBA& highlight) const;

private:
    static constexpr size_t GRID_BORDER = 3; /**< border around the grid */
    static constexpr size_t CELL_BORDER = 1; /**< border separating cells (painted over the cells, not between them) */
    static constexpr size_t GROUP_BORDER = 3; /**< border separating groups (painted over the cells, not between them) */
    static constexpr size_t CELL_SIZE = 10;
    static constexpr size_t GROUP_SIZE = 10;
    static constexpr ColorSpace::ColorRGBA BORDER_COLOR{0, 0, 0};

    PixelBuffer m_pixelBuffer;
    PixelBuffer m_grid; /**< The image as a grid */
    ThreadList m_threadList;
    Selection m_selection;

    void selectThreads(ColorSpace::DistanceAlgo algo);
    void createGrid();

    void drawPixelOnGrid(size_t x, size_t y);
    void drawPixelOnGrid(size_t x, size_t y, PixelBuffer& grid, const ColorSpace::ColorRGBA& color) const;
};

#endif // PATTERN_HPP
