/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "Thread.hpp"

Thread::SortBy Thread::m_sortBy = Thread::HLS;

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
            const int red = std::stoi(rgbNoSpaces.substr(0, 2), &nred, 16);
            const int green = std::stoi(rgbNoSpaces.substr(2, 2), &ngreen, 16);
            const int blue = std::stoi(rgbNoSpaces.substr(4, 2), &nblue, 16);
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

bool Thread::isValid() const {
    return m_isValid;
}

const std::string& Thread::name() const {
    return m_name;
}

const ColorSpace::rgba_t& Thread::color() const {
    return m_rgb;
}

void Thread::setSortBy(Thread::SortBy sortBy) {
    m_sortBy = sortBy;
}

std::strong_ordering Thread::operator<=>(const Thread& other) const {
    auto compare = [](double mine, double other) -> std::strong_ordering {
        if(mine < other) { return std::strong_ordering::less; }
        else if(mine > other) { return std::strong_ordering::greater; }
        else { return std::strong_ordering::equal; }
    };
    if(auto res = compare(m_hsl.hue, other.m_hsl.hue); res != std::strong_ordering::equal) {
        return res;
    }

    if(m_sortBy == Thread::HLS) {
        if(auto res = compare(m_hsl.lightness, other.m_hsl.lightness); res != std::strong_ordering::equal) {
            return res;
        }
        return compare(m_hsl.saturation, other.m_hsl.saturation);
    } else {
        if(auto res = compare(m_hsl.saturation, other.m_hsl.saturation); res != std::strong_ordering::equal) {
            return res;
        }
        return compare(m_hsl.lightness, other.m_hsl.lightness);
    }
}

// Note: Unlike a default operator<=>, a custom operator<=> does not generate operator== for performance reasons (a faster implementation is usually possible for operator==)
bool Thread::operator==(const Thread& other) const {
    return m_hsl.hue == other.m_hsl.hue && m_hsl.saturation == other.m_hsl.saturation && m_hsl.lightness == other.m_hsl.lightness;
}

double Thread::distance(const Thread& other, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, other.m_lab, algo);
}

double Thread::distance(const ColorSpace::rgba_t& rgba, ColorSpace::DistanceAlgo algo) const {
    return ColorSpace::distance(m_lab, ColorSpace::toLAB(rgba), algo);
}
