/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/Thread.hpp"

EMSCRIPTEN_BINDINGS(Thread) {
    emscripten::class_<Thread>("Thread")
        .constructor<const std::string&, const std::string&>()
        .function("isValid", &Thread::operator bool)
        .function("equalsToThread", emscripten::select_overload<bool(const Thread&)const>(&Thread::operator==))
        .function("equalsToColorRGBA", emscripten::select_overload<bool(const ColorSpace::ColorRGBA&)const>(&Thread::operator==))
        .function("name", &Thread::name)
        .function("color", &Thread::color)
        .function("hsl", &Thread::hsl)
        .function("distanceFromThread", emscripten::select_overload<double(const Thread&, ColorSpace::DistanceAlgo)const>(&Thread::distance))
        .function("distanceFromColorLAB", emscripten::select_overload<double(const ColorSpace::ColorLAB&, ColorSpace::DistanceAlgo)const>(&Thread::distance))
        ;
}
