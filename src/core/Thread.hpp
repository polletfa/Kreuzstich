/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
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

    [[nodiscard]] const std::string& name() const;
    [[nodiscard]] const ColorSpace::ColorRGBA& color() const;
    [[nodiscard]] const ColorSpace::ColorHSL& hsl() const;

    // distance
    [[nodiscard]] double distance(const Thread& other, ColorSpace::DistanceAlgo algo) const;
    [[nodiscard]] double distance(const ColorSpace::ColorLAB& lab, ColorSpace::DistanceAlgo algo) const;

private:
    bool m_isValid;
    std::string m_name;
    ColorSpace::ColorRGBA m_rgb; // for displaying
    ColorSpace::ColorHSL m_hsl;  // for sorting
    ColorSpace::ColorLAB m_lab;  // for distance
};

#endif // THREAD_HPP
