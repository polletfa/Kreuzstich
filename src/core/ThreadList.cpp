/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#include "ThreadList.hpp"

ThreadList::ThreadList(const std::vector<Thread>& threads)
    : m_threads(threads)
{}

std::optional<std::reference_wrapper<Thread>> ThreadList::findClosest(const ColorSpace::ColorRGBA& color) {
    if(m_threads.empty()) {
        return {};
    } else {
        Thread& closest{m_threads[0]};
        double minDistance;
        bool minDistanceSet{false};
        for(const auto& thread: m_threads) {
            if(double distance = thread.distance(color); !minDistanceSet || distance < minDistance) {
                minDistance = distance;
                minDistanceSet = true;
                closest = thread;
            }
        }
        return closest;
    }
}
