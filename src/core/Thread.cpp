/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Thread.hpp"

// STL
#include <cctype>

Thread::SortBy Thread::m_sortBy = Thread::HLS;
Thread::SortOrder Thread::m_sortOrder = Thread::ASC;

Thread::Thread(const std::string& name, const std::string& rgb)
    : m_name(name)
{
    std::string rgbNoSpaces;
    for(auto ch: rgb) {
        if(!std::isspace(ch)) {
            rgbNoSpaces += ch;
        }
    }
    if(rgbNoSpaces.size() != 6) {
        m_isValid = false;
    } else {
        try {
            size_t nred, ngreen, nblue;
            const uint8_t red = std::stoi(std::string{rgbNoSpaces.substr(0, 2)}, &nred, 16);
            const uint8_t green = std::stoi(std::string{rgbNoSpaces.substr(2, 2)}, &ngreen, 16);
            const uint8_t blue = std::stoi(std::string{rgbNoSpaces.substr(4, 2)}, &nblue, 16);
            if(nred != 2 || ngreen != 2 || nblue != 2) {
                m_isValid = false;
            } else {
                m_rgb = {red, green, blue};
                m_hsl = ColorSpace::toHSL(m_rgb);
                m_lab = ColorSpace::toLAB(m_rgb);
                m_isValid = true;
            }
        } catch(...) {
            m_isValid = false;
        }
    }
}

Thread::operator bool() const {
    return m_isValid;
}

bool Thread::operator==(const Thread& rhs) const {
    return m_rgb == rhs.m_rgb;
}

bool Thread::operator==(const ColorSpace::ColorRGBA& rhs) const {
    return m_rgb == rhs;
}

const std::string& Thread::name() const {
    return m_name;
}

const ColorSpace::ColorRGBA& Thread::color() const {
    return m_rgb;
}

void Thread::setSortBy(Thread::SortBy sortBy, Thread::SortOrder sortOrder) {
    m_sortBy = sortBy;
    m_sortOrder = sortOrder;
}

bool Thread::operator<(const Thread& other) const {
    auto first = m_sortOrder == Thread::ASC ? *this : other,
        second = m_sortOrder == Thread::ASC ? other : *this;
    if(m_sortBy == Thread::Name) {
        return first.m_name < second.m_name;
    } else if(m_sortBy == Thread::HLS) {
        return first.m_hsl.hue < second.m_hsl.hue || first.m_hsl.lightness < second.m_hsl.lightness || first.m_hsl.saturation < second.m_hsl.saturation;
    } else {
        return first.m_hsl.hue < second.m_hsl.hue || first.m_hsl.saturation < second.m_hsl.saturation || first.m_hsl.lightness < second.m_hsl.lightness;
    }
}

double Thread::distance(const Thread& other, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, other.m_lab, algo);
}

double Thread::distance(const ColorSpace::ColorRGBA& rgba, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, ColorSpace::toLAB(rgba), algo);
}
