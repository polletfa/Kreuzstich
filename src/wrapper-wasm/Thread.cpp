/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/Thread.hpp"

bool isThread(emscripten::val param) {
    return param.instanceof(emscripten::val::module_property("Thread"));
}

EMSCRIPTEN_BINDINGS(Thread) {
    emscripten::class_<Thread>("Thread")
        .constructor<const std::string&, const std::string&>()
        .function("isValid", &Thread::operator bool)
        .function("equals", emscripten::optional_override([](Thread& instance, emscripten::val param) {
            if(isThread(param)) {
                return instance.operator==(param.as<Thread>());
            } else {
                return instance.operator==(param.as<ColorSpace::ColorRGBA>());
            }
        }))
        .function("name", &Thread::name)
        .function("color", &Thread::color)
        .function("hsl", &Thread::hsl)
        .function("distance", emscripten::optional_override([](Thread& instance, emscripten::val color, ColorSpace::DistanceAlgo algo) {
            if(isThread(color)) {
                return instance.distance(color.as<Thread>(), algo);
            } else {
                return instance.distance(color.as<ColorSpace::ColorLAB>(), algo);
            }
        }))
        ;
}
