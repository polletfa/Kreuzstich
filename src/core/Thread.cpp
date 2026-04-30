/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Thread.hpp"

// STL
#include <cctype>

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

const ColorSpace::ColorHSL& Thread::hsl() const {
    return m_hsl;
}

double Thread::distance(const Thread& other, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, other.m_lab, algo);
}

double Thread::distance(const ColorSpace::ColorLAB& lab, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, lab, algo);
}
