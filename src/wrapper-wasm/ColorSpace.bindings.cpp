/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/ColorSpace.hpp"

EMSCRIPTEN_BINDINGS(ColorSpace) {
    emscripten::value_object<ColorSpace::ColorRGBA>("ColorSpace_ColorRGBA")
        .field("red", &ColorSpace::ColorRGBA::red)
        .field("green", &ColorSpace::ColorRGBA::green)
        .field("blue", &ColorSpace::ColorRGBA::blue)
        .field("alpha", &ColorSpace::ColorRGBA::alpha)
        ;
    emscripten::function("ColorSpace_rgbaEquals", &ColorSpace::operator==);

    emscripten::value_object<ColorSpace::ColorHSL>("ColorSpace_ColorHSL")
        .field("hue", &ColorSpace::ColorHSL::hue)
        .field("saturation", &ColorSpace::ColorHSL::saturation)
        .field("lightness", &ColorSpace::ColorHSL::lightness)
        ;

    emscripten::value_object<ColorSpace::ColorLAB>("ColorSpace_ColorLAB")
        .field("lightness", &ColorSpace::ColorLAB::lightness)
        .field("a", &ColorSpace::ColorLAB::a)
        .field("b", &ColorSpace::ColorLAB::b)
        ;

    emscripten::function("ColorSpace_compositeRGBAOntoBackground", &ColorSpace::compositeRGBAOntoBackground);
    emscripten::function("ColorSpace_toHSL", &ColorSpace::toHSL);
    emscripten::function("ColorSpace_toLAB", &ColorSpace::toLAB);

    emscripten::enum_<ColorSpace::DistanceAlgo>("ColorSpace_DistanceAlgo", emscripten::enum_value_type::string)
        .value("CIE1976", ColorSpace::DistanceAlgo::CIE1976)
        .value("CIEDE2000", ColorSpace::DistanceAlgo::CIEDE2000)
        ;

    emscripten::function("ColorSpace_distance", &ColorSpace::distance);
}
