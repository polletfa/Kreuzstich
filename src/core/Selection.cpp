/*
  Kreuzstichx
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "Selection.hpp"
#include "Pattern.hpp"

Selection::Iterator::Iterator(const Selection& parent)
    : m_patternWidth(parent.m_patternWidth)
    , m_patternHeight(parent.m_patternHeight)
    , m_pixelBufferAddr(parent.m_pixelBufferAddr)
    , m_selection(parent.m_selection)
    , m_x(m_selection.x)
    , m_y(m_selection.y)
{}

size_t Selection::Iterator::operator*() {
    return m_y * m_patternWidth + m_x;
}

Selection::Iterator& Selection::Iterator::operator++() {
    if(m_x + 1 >= m_selection.x + m_selection.width) {
        m_x = m_selection.x;
        ++m_y;
    } else {
        ++m_x;
    }
    return *this;
}

bool Selection::Iterator::operator!=(const Iterator& rhs) const {
    return m_pixelBufferAddr != rhs.m_pixelBufferAddr
        || m_y * m_patternWidth + m_x != rhs.m_y * rhs.m_patternWidth + rhs.m_x;
}

Selection::IteratorEnd::IteratorEnd(const Selection& parent)
    : Iterator(parent)
{
    m_y = m_selection.y + m_selection.height;
}

Selection::Selection(const Pattern& pattern)
    : Selection::Selection(pattern, {})
{}

Selection::Selection(const Pattern& pattern, const Rectangle& area)
    : m_patternWidth(pattern.get().width)
    , m_patternHeight(pattern.get().height)
    , m_pixelBufferAddr(pattern.get().pixels.data())
    , m_selection(area)
{
    // if x or y are outside the picture, the selection is empty
    if(m_selection.x >= m_patternWidth || m_selection.y >= m_patternHeight) {
        m_selection = {0, 0, 0, 0};
    } else {
        // if the selection is too big, shrink to fit within pattern
        if(m_selection.x + m_selection.width >= m_patternWidth) {
            m_selection.width = m_patternWidth - m_selection.x;
        }
        if(m_selection.y + m_selection.height >= m_patternHeight) {
            m_selection.height = m_patternHeight - m_selection.y;
        }
    }
}

Selection::Iterator Selection::begin() const {
    return Iterator{*this};
}

Selection::Iterator Selection::end() const {
    return IteratorEnd{*this};
}
