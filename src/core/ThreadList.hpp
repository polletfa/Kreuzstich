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
#include <utility>

/**
 * Class to manage a list of threads
 */
class ThreadList {
public:
    using RefList = std::vector<std::reference_wrapper<const Thread>>;
    using UsageCount = std::vector<std::pair<std::reference_wrapper<const Thread>, size_t>>;
    using OptionalRef = std::optional<std::reference_wrapper<const Thread>>;

    explicit ThreadList(const std::vector<Thread>& threads);

    enum SortBy { HLS, HSL, Name };
    enum SortOrder { ASC, DESC };

    /**
     * Returns list of thread in the specified sort order
     */
    RefList get(SortBy sortBy = HLS, SortOrder sortOrder = ASC) const;

    /**
     * Find thread with the clothest color.
     * Always retuns a value unless the threadlist is empty.
     */
    OptionalRef findClosest(const ColorSpace::ColorRGBA& color, ColorSpace::DistanceAlgo algo) const;

    /**
     * Find thread with the clothest color among the threads with usage count > 0.
     * Always retuns a value unless the threadlist is empty or all threads have 0 usage count
     */
    OptionalRef findClosestInUse(const ColorSpace::ColorRGBA& color, ColorSpace::DistanceAlgo algo) const;

    /**
     * Find exact match
     */
    OptionalRef findThread(const ColorSpace::ColorRGBA& color) const;

    /**
     * Get usage cout sorted by decreasing usage
     */
    const UsageCount& getUsage() const;

    /**
     * Set usage count
     */
    void setUsage(const UsageCount& usage);

    /**
     * Update usage count when a thread is replaced by another
     */
    void updateUsage(const Thread& origin, const Thread& replacement, size_t count);

private:
    std::vector<Thread> m_threads;
    RefList m_threadsAsRefList;
    UsageCount m_usage;

    bool compareThreads(const Thread& lhs, const Thread& rhs, SortBy sortBy, SortOrder sortOrder) const;
    void sortUsage();

    OptionalRef findClosestInList(const ColorSpace::ColorRGBA& color, const RefList& list, ColorSpace::DistanceAlgo algo) const;
};

#endif // THREADLIST_HPP
