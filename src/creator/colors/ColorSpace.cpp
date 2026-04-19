/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "ColorSpace.hpp"

// STL
#include <algorithm>
#include <numbers>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-constexpr"   // clangd is having issues with cmath from GCC apparently
#include <cmath>
#pragma GCC diagnostic pop

namespace ColorSpace {

constexpr double toRadians(double degrees) {
    return degrees * std::numbers::pi / 180;
}

}

ColorSpace::rgba_t ColorSpace::compositeRGBAOntoBackground(const ColorSpace::rgba_t& rgba, const ColorSpace::rgba_t& bg) {
    return {
        rgba.alpha * rgba.red + (1. - rgba.alpha) * bg.red,
        rgba.alpha * rgba.green + (1. - rgba.alpha) * bg.green,
        rgba.alpha * rgba.blue + (1. - rgba.alpha) * bg.blue
    };
}

ColorSpace::hsl_t ColorSpace::toHSL(const ColorSpace::rgba_t& rgba) {
    const ColorSpace::rgba_t& rgb = rgba.alpha == 1 ? rgba : ColorSpace::compositeRGBAOntoBackground(rgba, {});

    double V = std::max({rgb.red, rgb.green, rgb.blue});
    double C = V - std::min({rgb.red, rgb.green, rgb.blue});

    // lightness
    double L = V - C/2;

    // hue
    double H;
    if(C == 0) {
        H = 0;
    } else if(V == rgb.red) {
        if(double h = std::fmod((rgb.green - rgb.blue) / C, 6.0); h < 0) { H = 60 * (h + 6); }
        else { H = 60 * h; }
    } else if(V == rgb.green) {
        H = 60 * ((rgb.blue - rgb.red) / C + 2);
    } else {
        H = 60 * ((rgb.red - rgb.green) / C + 4);
    }

    // saturation
    double S = L == 0 || L == 1 ? 0 : (V - L) / std::min(L, 1 - L);

    return {H, S, L};
}

ColorSpace::lab_t ColorSpace::toLAB(const ColorSpace::rgba_t& rgba) {
    ColorSpace::rgba_t rgb = rgba.alpha == 1 ? rgba : ColorSpace::compositeRGBAOntoBackground(rgba, {});

    // Inverse sRGB companding (sRGB -> linear RGB)
    auto inverseCompanding = [](double val) { return val <= 0.04045 ? val/12.92 : std::pow((val + 0.055) / 1.055, 2.4); };
    rgb.red = inverseCompanding(rgb.red);
    rgb.green = inverseCompanding(rgb.green);
    rgb.blue = inverseCompanding(rgb.blue);

    // Linear RGB -> CIEXYZ
    double x = 0.4124564 * rgb.red + 0.3575761 * rgb.green + 0.1804375 * rgb.blue;
    double y = 0.2126729 * rgb.red + 0.7151522 * rgb.green + 0.0721750 * rgb.blue;
    double z = 0.0193339 * rgb.red + 0.1191920 * rgb.green + 0.9503041 * rgb.blue;

    // CIEXYZ -> CIELAB
    constexpr double eps = 216. / 24389;
    constexpr double kappa = 24389. / 27;
    constexpr double refX = 0.95047, refY = 1., refZ = 1.08883; // reference white D65, 2° observer
    auto f = [](double val, double ref) { return val > eps ? std::pow(val / ref, 1./3) : (kappa * val / ref + 16)/116; };
    double fy = f(y, refY);

    return {
        116 * fy - 16,
        500 * (f(x, refX) - fy),
        200 * (fy - f(z, refZ))
    };
}

double ColorSpace::distance(const ColorSpace::lab_t& color1, const ColorSpace::lab_t& color2, DistanceAlgo algo) {
    if(algo == CIE1976) {
        return std::sqrt(
                         (color1.lightness - color2.lightness) * (color1.lightness - color2.lightness)
                         + (color1.a - color2.a) * (color1.a - color2.a)
                         + (color1.b - color2.b) * (color1.b - color2.b)
                         );
    } else { // CIEDE2000
        double Lprimebar = (color1.lightness + color2.lightness) / 2;
        double C1 = std::sqrt(color1.a * color1.a + color1.b * color1.b);
        double C2 = std::sqrt(color2.a * color2.a + color2.b * color2.b);
        double Cbar = (C1 + C2) / 2;
        double Cbar2 = Cbar * Cbar;
        double Cbar7 = Cbar2 * Cbar2 * Cbar2 * Cbar;
        double G = 0.5 * (1 - std::sqrt(Cbar7 / (Cbar7 + 6'103'515'625))); // Note: 6'103'515'625 = 25^7
        double a1prime = color1.a * (1 + G);
        double a2prime = color2.a * (1 + G);
        double C1prime = std::sqrt(a1prime * a1prime + color1.b * color1.b);
        double C2prime = std::sqrt(a2prime * a2prime + color2.b * color2.b);
        double Cprimebar = (C1prime + C2prime) / 2;
        double h1prime = std::atan2(color1.b, a1prime);
        if(h1prime < 0) { h1prime += toRadians(360); }
        double h2prime = std::atan2(color2.b, a2prime);
        if(h2prime < 0) { h2prime += toRadians(360); }
        double Hprimebar = std::abs(h1prime - h2prime) > toRadians(180) ? (h1prime + h2prime + toRadians(360)) / 2 : (h1prime + h2prime) / 2;
        double T = 1 - 0.17 * std::cos(Hprimebar - toRadians(30))
            + 0.24 * std::cos(2 * Hprimebar)
            + 0.32 * std::cos(3 * Hprimebar + toRadians(6))
            - 0.20 * std::cos(4 * Hprimebar - toRadians(63));
        double deltahprime;
        if(std::abs(h2prime - h1prime) <= toRadians(180)) {
            deltahprime = h2prime - h1prime;
        } else if(h2prime <= h1prime) {
            deltahprime = h2prime - h1prime + toRadians(360);
        } else {
            deltahprime = h2prime - h1prime - toRadians(360);
        }
        double deltaLprime = color2.lightness - color1.lightness;
        double deltaCprime = C2prime - C1prime;
        double deltaHprime = 2 * std::sqrt(C1prime * C2prime) * std::sin(deltahprime / 2);
        double Lprimebar50 = Lprimebar - 50;
        double Lprimebar2 = Lprimebar50 * Lprimebar50;
        double SL = 1 + 0.015 * Lprimebar2 / std::sqrt(20 + Lprimebar2);
        double SC = 1 + 0.045 * Cprimebar;
        double SH = 1 + 0.015 * Cprimebar * T;
        double Cprimebar2 = Cprimebar * Cprimebar;
        double Cprimebar7 = Cprimebar2 * Cprimebar2 * Cprimebar2 * Cprimebar;
        double RC = 2 * std::sqrt(Cprimebar7 / (Cprimebar7 + 6'103'515'625));
        double Hprimebar275 = (Hprimebar - toRadians(275))/toRadians(25);
        double RT = -RC * std::sin(toRadians(60) * std::exp(-Hprimebar275 * Hprimebar275));

        double Lintermediate = deltaLprime / SL; // note: KL = 1
        double Cintermediate = deltaCprime / SC; // note: KC = 1
        double Hintermediate = deltaHprime / SH; // note: KH = 1
        return std::sqrt(Lintermediate * Lintermediate + Cintermediate * Cintermediate + Hintermediate * Hintermediate + RT * Cintermediate * Hintermediate);
    }
}
