/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "ThreadList.hpp"

// STL
#include <algorithm>

ThreadList::ThreadList(const std::vector<Thread>& threads)
    : m_threads(threads)
{
    for(const auto& thread: m_threads) {
        m_usage.push_back({thread, 0});
    }
}

ThreadList::RefList ThreadList::get(SortBy sortBy, SortOrder sortOrder) const {
    // init list with references
    RefList list;
    for(const auto& thread: m_threads) {
        list.push_back(thread);
    }

    // sort
    std::sort(list.begin(), list.end(), [=, this](const Thread& lhs, const Thread& rhs)->bool {
        return compareThreads(lhs, rhs, sortBy, sortOrder);
    });

    return list;
}

ThreadList::OptionalRef ThreadList::findClosest(const ColorSpace::ColorRGBA& color) const {
    if(m_threads.empty()) {
        return {};
    } else {
        const Thread* closest{&m_threads[0]};
        double minDistance;
        bool minDistanceSet{false};
        for(auto& thread: m_threads) {
            if(double distance = thread.distance(color); !minDistanceSet || distance < minDistance) {
                minDistance = distance;
                minDistanceSet = true;
                closest = &thread;
            }
        }
        return *closest;
    }
}

ThreadList::OptionalRef ThreadList::findClosestInUse(const ColorSpace::ColorRGBA& color) const {
    RefList inUse;
    for(const auto& item: m_usage) {
        if(item.second > 0) {
            inUse.push_back(item.first);
        }
    }
    if(inUse.empty()) {
        return {};
    } else {
        const Thread* closest{&inUse[0].get()};
        double minDistance;
        bool minDistanceSet{false};
        for(auto& thread: inUse) {
            if(double distance = thread.get().distance(color); !minDistanceSet || distance < minDistance) {
                minDistance = distance;
                minDistanceSet = true;
                closest = &thread.get();
            }
        }
        return *closest;
    }
}

ThreadList::OptionalRef ThreadList::findThread(const ColorSpace::ColorRGBA& color) const {
    auto found = std::find(m_threads.begin(), m_threads.end(), color);
    return found != m_threads.end() ? OptionalRef(*found) : std::nullopt;
}

const ThreadList::UsageCount& ThreadList::getUsage() const {
    return m_usage;
}

void ThreadList::setUsage(const UsageCount& usage) {
    m_usage = usage;
    sortUsage();
}

void ThreadList::updateUsage(const Thread& original, const Thread& replacement, size_t count) {
    auto search = [](const auto& val, const auto& searchingFor)->bool {
        return val.first == searchingFor;
    };
    auto foundOriginal = std::find_if(m_usage.begin(), m_usage.end(), [&](auto val) { return search(val, original); }),
        foundReplacement = std::find_if(m_usage.begin(), m_usage.end(), [&](auto val) { return search(val, replacement); });
    if(foundOriginal != m_usage.end() && foundReplacement != m_usage.end()) {
        if(foundOriginal->second <= count) { // should normally not happend, but let's make sure
            foundReplacement->second += foundOriginal->second;
            foundOriginal->second = 0;
        } else {
            foundOriginal->second -= count;
            foundReplacement->second += count;
        }
    }
    sortUsage();
}

bool ThreadList::compareThreads(const Thread& lhs, const Thread& rhs, SortBy sortBy, SortOrder sortOrder) const {
    auto first = sortOrder == ThreadList::SortOrder::ASC ? lhs : rhs,
        second = sortOrder == ThreadList::SortOrder::ASC ? rhs : lhs;
    if(sortBy == ThreadList::SortBy::Name) {
        return first.name() < second.name();
    } else if(sortBy == ThreadList::SortBy::HLS) {
        return first.hsl().hue < second.hsl().hue
            || (first.hsl().hue == second.hsl().hue && first.hsl().lightness < second.hsl().lightness)
            || (first.hsl().hue == second.hsl().hue && first.hsl().lightness == second.hsl().lightness && first.hsl().saturation < second.hsl().saturation);
    } else /* if(sortBy == ThreadList::SortBy::HSL) */ {
        return first.hsl().hue < second.hsl().hue
            || (first.hsl().hue == second.hsl().hue && first.hsl().saturation < second.hsl().saturation)
            || (first.hsl().hue == second.hsl().hue && first.hsl().saturation == second.hsl().saturation && first.hsl().lightness < second.hsl().lightness);
    }
}

void ThreadList::sortUsage() {
    std::sort(m_usage.begin(), m_usage.end(), [](const auto& lhs, const auto& rhs)->bool {
        return lhs.second > rhs.second; // decreasing
    });
}
