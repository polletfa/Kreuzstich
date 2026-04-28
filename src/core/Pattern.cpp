/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "Pattern.hpp"


// STL
#include <algorithm>

Pattern::Pattern(const PixelBuffer& pixelBuffer, const ThreadList& threadlist, bool selectThreads)
    : m_pixelBuffer(pixelBuffer)
    , m_threadList(threadlist)
    , m_selection(*this)
{
    if(selectThreads) {
        for(auto& pixel: m_pixelBuffer.pixels) {
            auto found = m_threadList.findClosest(pixel);
            if(found) {
                pixel = found->get().color();
            }
            // else:
            //    The only case where !found is when the threadlist is empty.
            //    This will be checked when creating a project, so we don't need to here
        }
        m_threadList.setUsage(computeUsage());
    }
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

void Pattern::select(const Selection& selection) {
    m_selection = selection;
}

void Pattern::unselect() {
    m_selection = Selection(*this);
}

ThreadList::UsageCount Pattern::computeUsage() const {
    ThreadList::UsageCount usage;
    for(auto& thread: m_threadList.get()) {
        usage.push_back({thread, 0});
    }

    for(size_t index: m_selection) {
        auto found = m_threadList.findThread(m_pixelBuffer.pixels[index]);
        if(found) {
            auto foundUsage = std::find_if(usage.begin(), usage.end(), [&](auto& val)->bool {
                return val.first.get() == found;
            });
            ++ foundUsage->second;
        } // else: should not happen, just ignore
    }
    return usage;
}

void Pattern::replacePixel(size_t x, size_t y, const Thread& replacement) {
    auto& pixel = m_pixelBuffer.pixels[y * m_pixelBuffer.width + x];
    auto found = m_threadList.findThread(pixel);
    if(found) {
        pixel = replacement.color();
        m_threadList.updateUsage(found->get(), replacement, 1);
    }
}

void Pattern::replaceThread(const Thread& original, const Thread& replacement) {
    size_t count = 0;
    for(size_t index: m_selection) {
        if(m_pixelBuffer.pixels[index] == original) {
            ++ count;
            m_pixelBuffer.pixels[index] = replacement.color();
        }
    }
    m_threadList.updateUsage(original, replacement, count);
}

Pattern::PixelBuffer Pattern::highlight(const Thread& hl) const {
    PixelBuffer result{m_pixelBuffer};

    for(size_t index: m_selection) {
        if(result.pixels[index] == hl) {
            result.pixels[index] = ColorSpace::compositeRGBAOntoBackground(result.pixels[index], HIGHLIGHT);
        }
    }

    return m_pixelBuffer;
}
