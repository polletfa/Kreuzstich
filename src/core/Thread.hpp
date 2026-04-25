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
 */
class Thread {
public:
    /**
     * @param rgb Color with format "RRGGBB" (hexadecimal notation)
     */
    explicit Thread(const std::string& name, const std::string& rgb);

    operator bool() const; /**< false if the constructor fails (invalid rgb string) */
    bool operator==(const Thread& rhs) const;
    bool operator==(const ColorSpace::ColorRGBA& rhs) const;

    const std::string& name() const;
    const ColorSpace::ColorRGBA& color() const;

    // sort
    enum SortBy { HLS, HSL, Name }; /**< Default: hue, lightness, saturation */
    enum SortOrder { ASC, DESC }; /**< Default: ascending */
    static void setSortBy(SortBy sortBy = HLS, SortOrder sortOrder = ASC);
    bool operator<(const Thread& other) const;

    // distance
    double distance(const Thread& other, ColorSpace::DistanceAlgo algo = ColorSpace::CIEDE2000) const;
    double distance(const ColorSpace::ColorRGBA& rgba, ColorSpace::DistanceAlgo algo = ColorSpace::CIEDE2000) const;

private:
    static SortBy m_sortBy;
    static SortOrder m_sortOrder;

    bool m_isValid;
    std::string m_name;
    ColorSpace::ColorRGBA m_rgb; // for displaying
    ColorSpace::ColorHSL m_hsl;  // for sorting
    ColorSpace::ColorLAB m_lab;  // for distance
};

#endif // THREAD_HPP
