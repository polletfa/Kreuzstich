/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "Selection.hpp"
#include "Picture.hpp"

Selection::Iterator::Iterator(Selection& parent, bool moveToEnd)
    : m_pixels(parent.m_picture.get())
    , m_width(parent.m_picture.width())
    , m_height(parent.m_picture.height())
    , m_selection(parent.m_selection)
    , m_x(m_selection.x)
    , m_y(m_selection.y + (moveToEnd ? m_selection.height: 0))
{}

ColorSpace::ColorRGBA& Selection::Iterator::operator*() {
    return m_pixels[m_y * m_width + m_x];
}

Selection::Iterator& Selection::Iterator::operator++() {
    if(m_x >= m_selection.x + m_selection.width) {
        m_x = m_selection.x;
        ++m_y;
    } else {
        ++m_x;
    }
    return *this;
}

bool Selection::Iterator::operator!=(const Iterator& rhs) const {
    return m_pixels.data() != rhs.m_pixels.data()
        || m_y * m_width + m_x != rhs.m_y * rhs.m_width + rhs.m_x;
}

Selection::Selection(Picture& picture)
    : Selection::Selection(picture, {})
{}

Selection::Selection(Picture& picture, const Rectangle& area)
    : m_picture(picture)
    , m_selection(area)
{
    // ensure the selection is within the picture
    if(m_selection.x >= m_picture.width()) {
        m_selection.x = m_picture.width() - 1;
    }
    if(m_selection.y >= m_picture.height()) {
        m_selection.y = m_picture.height() - 1;
    }
    if(m_selection.x + m_selection.width >= m_picture.width()) {
        m_selection.width = m_picture.width() - m_selection.x - 1;
    }
    if(m_selection.y + m_selection.height >= m_picture.height()) {
        m_selection.height = m_picture.height() - m_selection.y - 1;
    }
}

Selection::Iterator Selection::begin() {
    return *this;
}

Selection::Iterator Selection::end() {
    return {*this, true};
}
