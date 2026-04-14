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
#include <compare>

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
    bool isValid() const; /**< false if the constructor fails (invalid rgb string) */

    const std::string& name() const;
    const ColorSpace::rgba_t& color() const;

    // sort
    enum SortBy { HLS, HSL }; /**< Default: hue, lightness, saturation */
    static void setSortBy(SortBy sortBy);
    std::strong_ordering operator<=>(const Thread& other) const;
    bool operator==(const Thread& other) const;

    // distance
    double distance(const Thread& other, ColorSpace::DistanceAlgo algo = ColorSpace::CIE1976) const;
    double distance(const ColorSpace::rgba_t& rgba, ColorSpace::DistanceAlgo algo = ColorSpace::CIE1976) const;

private:
    static SortBy m_sortBy;

    bool m_isValid;
    std::string m_name;
    ColorSpace::rgba_t m_rgb; // for displaying
    ColorSpace::hsl_t m_hsl;  // for sorting
    ColorSpace::lab_t m_lab;  // for distance
};

#endif // THREAD_HPP
