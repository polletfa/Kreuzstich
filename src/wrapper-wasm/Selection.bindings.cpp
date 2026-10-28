/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/Selection.hpp"

// Note: We only need bindings for the structures. The Selection class itself is only used
//       internally by the Pattern class and doesn't need to be accessible directly.
EMSCRIPTEN_BINDINGS(Selection) {
    emscripten::value_object<Selection::Rectangle>("Selection_Rectangle")
        .field("x", &Selection::Rectangle::x)
        .field("y", &Selection::Rectangle::y)
        .field("width", &Selection::Rectangle::width)
        .field("height", &Selection::Rectangle::height)
        ;
}
