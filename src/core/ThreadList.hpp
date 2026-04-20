/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef THREADLIST_HPP
#define THREADLIST_HPP

#include "Thread.hpp"

// STL
#include <vector>
#include <optional>
#include <functional>

/**
 * Class to manage a list of threads
 */
class ThreadList {
public:
    explicit ThreadList(const std::vector<Thread>& threads);

    /**
     * Find thread with the clothest color.
     * Always retuns a value unless the threadlist is empty.
     */
    std::optional<std::reference_wrapper<Thread>> findClosest(const ColorSpace::ColorRGBA& color);

private:
    std::vector<Thread> m_threads;
};

#endif // THREADLIST_HPP
