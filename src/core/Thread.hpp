/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef THREAD_HPP
#define THREAD_HPP

#include "ColorSpace.hpp"

// STL
#include <string>

/**
 * Class representing a thread (textile thread, not computing thread!):
 * - Name and color
 * - Sort/Distance operations
 *
 * @todo add data/methods to track usage of the thread, when it is part of a project-specific threadlist
 */
class Thread {
public:
    /**
     * @param rgb Color with format "RRGGBB" (hexadecimal notation)
     */
    Thread(const std::string& name, const std::string& rgb);

    operator bool() const; /**< false if the constructor fails (invalid rgb string) */

    const std::string& name() const;
    const std::string& colorString() const;
    const ColorSpace::ColorRGBA& color() const;

    // sort
    enum SortBy { HLS, HSL }; /**< Default: hue, lightness, saturation */
    static void setSortBy(SortBy sortBy);
    bool operator<(const Thread& other) const;

    // distance
    double distance(const Thread& other, ColorSpace::DistanceAlgo algo = ColorSpace::CIE1976) const;
    double distance(const ColorSpace::ColorRGBA& rgba, ColorSpace::DistanceAlgo algo = ColorSpace::CIE1976) const;

private:
    static SortBy m_sortBy;

    bool m_isValid;
    std::string m_name;
    std::string m_colorString;
    ColorSpace::ColorRGBA m_rgb; // for displaying
    ColorSpace::ColorHSL m_hsl;  // for sorting
    ColorSpace::ColorLAB m_lab;  // for distance
};

#endif // THREAD_HPP
