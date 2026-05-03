/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/ThreadList.hpp"

using RefListWASM = std::vector<const Thread*>;
using OptionalRefWASM = const Thread*;

RefListWASM toWASM(const ThreadList::RefList& in) {
    RefListWASM out;
    for(const auto& item: in) {
        out.push_back(&item.get());
    }
    return out;
}

OptionalRefWASM toWASM(const ThreadList::OptionalRef& in) {
    return in ? &in->get() : nullptr;
}

EMSCRIPTEN_BINDINGS(ThreadList) {
    emscripten::register_vector<Thread>("ThreadVector");
    emscripten::register_vector<const Thread*>("ThreadPtrVector");

    emscripten::enum_<ThreadList::SortBy>("ThreadList_SortBy", emscripten::enum_value_type::string)
        .value("HLS", ThreadList::SortBy::HLS)
        .value("HSL", ThreadList::SortBy::HSL)
        .value("Name", ThreadList::SortBy::Name)
        ;
    emscripten::enum_<ThreadList::SortOrder>("ThreadList_SortOrder", emscripten::enum_value_type::string)
        .value("ASC", ThreadList::SortOrder::ASC)
        .value("DESC", ThreadList::SortOrder::DESC)
        ;

    emscripten::class_<ThreadList>("ThreadList")
        .constructor<const std::vector<Thread>&>()
        .function("get", emscripten::optional_override([](const ThreadList& instance, ThreadList::SortBy sortBy, ThreadList::SortOrder sortOrder) {
            return toWASM(instance.get(sortBy, sortOrder));
        }))
        .function("findClosest", emscripten::optional_override([](const ThreadList& instance, ColorSpace::ColorRGBA color, ColorSpace::DistanceAlgo algo)->OptionalRefWASM {
            return toWASM(instance.findClosest(color, algo));
        }), emscripten::return_value_policy::reference())
        .function("findClosestInUse", emscripten::optional_override([](const ThreadList& instance, ColorSpace::ColorRGBA color, ColorSpace::DistanceAlgo algo)->OptionalRefWASM {
            return toWASM(instance.findClosestInUse(color, algo));
        }), emscripten::return_value_policy::reference())
        .function("findThread", emscripten::optional_override([](const ThreadList& instance, ColorSpace::ColorRGBA color)->OptionalRefWASM {
            return toWASM(instance.findThread(color));
        }), emscripten::return_value_policy::reference())
            //todo usage
            //todo setUsage
            //todo updateUsage
        ;
}
