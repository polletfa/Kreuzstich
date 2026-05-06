/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "Pattern.hpp"

// STL
#include <algorithm>
#include <unordered_map>

Pattern::Pattern(const PixelBuffer& pixelBuffer, const ThreadList& threadlist, bool _selectThreads, ColorSpace::DistanceAlgo algo)
    : m_pixelBuffer(pixelBuffer)
    , m_threadList(threadlist)
    , m_selection(*this)
{
    if(_selectThreads) {
        selectThreads(algo);
    }
    m_threadList.setUsage(computeUsage());
    createGrid();
}

const ThreadList& Pattern::threadList() const {
    return m_threadList;
}

const Pattern::PixelBuffer& Pattern::get() const {
    return m_pixelBuffer;
}

const ColorSpace::ColorRGBA& Pattern::get(size_t x, size_t y) const {
    return m_pixelBuffer.pixels[y * m_pixelBuffer.width + x];
}

const Pattern::PixelBuffer& Pattern::grid() const {
    return m_grid;
}

void Pattern::select(const Selection::Rectangle& selection) {
    m_selection = Selection{*this, selection};
}

ThreadList::UsageCount Pattern::computeUsage() const {
    ThreadList::UsageCount usage;
    for(auto& thread: m_threadList.get()) {
        usage.push_back({thread, 0});
    }

    for(size_t index: m_selection) {
        auto found = std::find_if(usage.begin(), usage.end(), [&](auto& val)->bool {
            return val.first.get().color() == m_pixelBuffer.pixels[index];
        });
        if(found != usage.end()) {
            ++ found->second;
        }
    }
    return usage;
}

void Pattern::replacePixel(size_t x, size_t y, const Thread& replacement) {
    auto& pixel = m_pixelBuffer.pixels[y * m_pixelBuffer.width + x];
    auto found = m_threadList.findThread(pixel);
    if(found) {
        pixel = replacement.color();
        m_threadList.updateUsage(found->get(), replacement, 1);
        drawPixelOnGrid(x, y);
    }
}

void Pattern::replaceThread(const Thread& original, const Thread& replacement) {
    size_t count = 0;
    for(size_t index: m_selection) {
        if(m_pixelBuffer.pixels[index] == original) {
            ++ count;
            m_pixelBuffer.pixels[index] = replacement.color();
            drawPixelOnGrid(index % m_pixelBuffer.width, index / m_pixelBuffer.width);
        }
    }
    m_threadList.updateUsage(original, replacement, count);
}

Pattern::PixelBuffer Pattern::highlight(const Thread& original, const ColorSpace::ColorRGBA& highlight) const {
    PixelBuffer layer { std::vector<ColorSpace::ColorRGBA>(m_grid.width * m_grid.height, {0, 0, 0, 0}), m_grid.width, m_grid.height };

    for(size_t index: m_selection) {
        if(m_pixelBuffer.pixels[index] == original) {
            drawPixelOnGrid(index % m_pixelBuffer.width, index / m_pixelBuffer.width, layer, highlight);
        }
    }

    return layer;
}

void Pattern::selectThreads(ColorSpace::DistanceAlgo algo) {
    std::unordered_map<int, ColorSpace::ColorRGBA> cache;
    for(auto& pixel: m_pixelBuffer.pixels) {
        int cacheIndex = pixel.red<<16 | pixel.green<<8 | pixel.blue;
        if(auto found = cache.find(cacheIndex); found != cache.end()) {
            pixel = found->second;
        } else {
            auto closest = m_threadList.findClosest(pixel, algo);
            if(closest) {
                pixel = closest->get().color();
                cache[cacheIndex] = pixel;
            }
            // else:
            //    The only case where !closest is when the threadlist is empty.
            //    This will be checked when creating a project, so we don't need to here
        }
    }
}

void Pattern::createGrid() {
    m_grid.width = m_pixelBuffer.width * CELL_SIZE + GRID_BORDER * 2;
    m_grid.height = m_pixelBuffer.height * CELL_SIZE + GRID_BORDER * 2;
    m_grid.pixels = std::vector<ColorSpace::ColorRGBA>(m_grid.width * m_grid.height, BORDER_COLOR);

    for(size_t x = 0; x < m_pixelBuffer.width; ++x) {
        for(size_t y = 0; y < m_pixelBuffer.height; ++y) {
            drawPixelOnGrid(x, y);
        }
    }
}

void Pattern::drawPixelOnGrid(size_t x, size_t y) {
    drawPixelOnGrid(x, y, m_grid, get(x, y));
}

void Pattern::drawPixelOnGrid(size_t x, size_t y, PixelBuffer& grid, const ColorSpace::ColorRGBA& color) const {
    size_t marginLeft = x == 0                          ? 0
        : x % GROUP_SIZE                                ? CELL_BORDER - CELL_BORDER/2
        :                                                 GROUP_BORDER - GROUP_BORDER/2;
    size_t marginRight = x == m_pixelBuffer.width - 1   ? 0
        : (x+1) % GROUP_SIZE                            ? CELL_BORDER/2
        :                                                 GROUP_BORDER/2;
    size_t marginTop = y == 0                           ? 0
        : y % GROUP_SIZE                                ? CELL_BORDER - CELL_BORDER/2
        :                                                 GROUP_BORDER - GROUP_BORDER/2;
    size_t marginBottom = y == m_pixelBuffer.height - 1 ? 0
        : (y+1) % GROUP_SIZE                            ? CELL_BORDER/2
        :                                                 GROUP_BORDER/2;
    size_t rx = GRID_BORDER + x * CELL_SIZE + marginLeft;
    size_t ry = GRID_BORDER + y * CELL_SIZE + marginTop;
    size_t width = CELL_SIZE - marginLeft - marginRight;
    size_t height = CELL_SIZE - marginTop - marginBottom;

    for(size_t xi = 0; xi < width; ++xi) {
        for(size_t yi = 0; yi < height; ++yi) {
            grid.pixels[(ry+yi) * grid.width + rx + xi] = color;
        }
    }
}
