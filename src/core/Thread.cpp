/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Thread.hpp"

// STL
#include <cctype>

Thread::SortBy Thread::m_sortBy = Thread::HLS;

Thread::Thread(const std::string& name, const std::string& rgb)
    : m_name(name), m_colorString(rgb)
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
            const int red = std::stoi(std::string{rgbNoSpaces.substr(0, 2)}, &nred, 16);
            const int green = std::stoi(std::string{rgbNoSpaces.substr(2, 2)}, &ngreen, 16);
            const int blue = std::stoi(std::string{rgbNoSpaces.substr(4, 2)}, &nblue, 16);
            if(nred != 2 || ngreen != 2 || nblue != 2) {
                m_isValid = false;
            } else {
                m_rgb = {red/255., green/255., blue/255.};
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

const std::string& Thread::name() const {
    return m_name;
}

const std::string& Thread::colorString() const {
    return m_colorString;
}

const ColorSpace::ColorRGBA& Thread::color() const {
    return m_rgb;
}

void Thread::setSortBy(Thread::SortBy sortBy) {
    m_sortBy = sortBy;
}

bool Thread::operator<(const Thread& other) const {
    if(m_sortBy == Thread::HLS) {
        return m_hsl.hue < other.m_hsl.hue || m_hsl.lightness < other.m_hsl.lightness || m_hsl.saturation < other.m_hsl.saturation;
    } else {
        return m_hsl.hue < other.m_hsl.hue || m_hsl.saturation < other.m_hsl.saturation || m_hsl.lightness < other.m_hsl.lightness;
    }
}

double Thread::distance(const Thread& other, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, other.m_lab, algo);
}

double Thread::distance(const ColorSpace::ColorRGBA& rgba, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, ColorSpace::toLAB(rgba), algo);
}
