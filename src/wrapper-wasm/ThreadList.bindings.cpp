/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include <emscripten/bind.h>

#include "core/ThreadList.hpp"

// STL
#include <exception>

struct UsagePairWASM {
    const Thread* thread;
    size_t count;
};

using RefListWASM = std::vector<const Thread*>;
using OptionalRefWASM = const Thread*;
using UsageCountWASM = std::vector<UsagePairWASM>;

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

UsageCountWASM toWASM(const ThreadList::UsageCount& in) {
    UsageCountWASM out;
    for(const auto& item: in) {
        out.push_back({&item.first.get(), item.second});
    }
    return out;
}

ThreadList::UsageCount fromWASM(const UsageCountWASM& in) {
    ThreadList::UsageCount out;
    for(const auto& item: in) {
        out.push_back(std::make_pair(std::ref(*item.thread), item.count));
    }
    return out;
}

EMSCRIPTEN_BINDINGS(ThreadList) {
    emscripten::register_vector<Thread>("ThreadVector");
    emscripten::register_vector<const Thread*>("ThreadPtrVector");
    emscripten::register_vector<UsagePairWASM>("ThreadList_UsageCountVector");
    emscripten::value_object<UsagePairWASM>("ThreadList_UsagePair")
        .field("thread", emscripten::optional_override([](const UsagePairWASM& obj) {
            return emscripten::val(obj.thread, emscripten::return_value_policy::reference());
        }), emscripten::optional_override([](UsagePairWASM& obj, emscripten::val value) {
            obj.thread = reinterpret_cast<const Thread*>(value.as<int>());
        }))
        .field("count", &UsagePairWASM::count)
        ;

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
        .function("get", emscripten::optional_override([](const ThreadList& instance, ThreadList::SortBy sortBy, ThreadList::SortOrder sortOrder)->RefListWASM {
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
        .function("usage", emscripten::optional_override([](const ThreadList& instance)->UsageCountWASM {
            auto res = toWASM(instance.usage());
            return res;
        }))
        .function("setUsage", emscripten::optional_override([](ThreadList& instance, UsageCountWASM usage)->void {
            instance.setUsage(fromWASM(usage));
        }))
        .function("updateUsage", emscripten::optional_override([](ThreadList& instance, const Thread* original, const Thread* replacement, int count) {
            instance.updateUsage(*original, *replacement, count);
        }), emscripten::return_value_policy::reference())
        ;
}
