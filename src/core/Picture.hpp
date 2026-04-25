/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

#ifndef PICTURE_HPP
#define PICTURE_HPP

#include "Thread.hpp"
#include "ThreadList.hpp"
#include "Selection.hpp"

// STL
#include <vector>
#include <cstdint>
#include <cstdlib>

/*
  TODO: refactor

  - limit the responsability of this class to the pattern picture. maybe rename in Pattern
  - don't store originalPicture and resizedPicture here (in the Project class instead)
  - load and resize probably in another class (Project?)
  - add select/clearSelect (later maybe addToSelection, removeFromSelection to allow complex selection)
  - replace/highlight automatically applies to current selection (instead of overloaded methods)

  - Thread/ThreadList class:
    - sort order as static is not good. provide sort function in ThreadList instead (with params)
       -> maybe return a sorted vector<Thread&> instead of modifying the order in-place? we will need different sorts in diff places.
    - add usage stats in ThreadList, not in Thread?
    - maintain a separate ThreadList for current selection?
       - how to avoid unnecessary copy of the list?
         --> one ThreadList, but maintains usage for both, and methods usage() & usageForSelection() that return pair<const Thread&, size_t>
             - Thread can always be returned as const&, since never modified.
*/




/**
 * Class to manage a picture, including:
 * - Original picture
 * - Resized picture
 * - Resized picture with selected colors
 * - ThreadList with usage stats
 */
class Picture {
public:
    enum FileFormat {JPEG, PNG, BMP, TGA, PSD, HDR, PIC, GIF, PNM};

    /**
     * @param pictureBuffer Content of an image file (must be supported by nothings/stb)
     * @param resizex Resize the picture to (resizex,resizey)
     * @param resizey Resize the picture to (resizex,resizey)
     * @param threadlist Threadlist for color selection
     *
     * @note The object is constructed with a picture file loaded in memory, not a file path, because
     *       core must be independent of the filesystem. The frontend will decide how to load the file
     *       depending on the context (for example, in a WebAssembly core wouldn't have filesystem access).
     */
    Picture(const std::vector<uint8_t>& pictureBuffer, size_t resizex, size_t resizey, const ThreadList& threadlist);

    /**
     * Create an instance for which all data has already been calculated (when loading a project from storage)
     */
    static Picture loadFromStorage(FileFormat format,
                                   const std::vector<uint8_t>& originalPicture,
                                   const std::vector<uint8_t>& resizedPicture,
                                   const std::vector<ColorSpace::ColorRGBA>& patternPicture,
                                   size_t width, size_t height,
                                   const ThreadList& threadList);

    FileFormat format() const;
    std::vector<uint8_t> originalPicture() const; /**< Get the original picture in the original format */
    std::vector<uint8_t> resizedPicture() const;  /**< Get the resized picture in the same format as the original */
    std::vector<uint8_t> patternPicture() const;  /**< Get the pattern picture (resized, selected colors) in the same format as the original */

    /**
     * Returns the threadlist
     */
    const ThreadList& threadList() const;

    size_t width() const;  /**< Width of the pattern picture */
    size_t height() const; /**< Height of the pattern picture */

    /**
     * Returns the raw pixel buffer for the pattern picture
     */
    std::vector<ColorSpace::ColorRGBA>& get();

    /**
     * Returns a specific pixel from the pattern picture
     */
    ColorSpace::ColorRGBA& get(size_t x, size_t y);

    /**
     * Replace a single pixel by another thread in the pattern picture.
     * Also updates the usage statistics in the threadlist.
     */
    void replacePixel(size_t x, size_t y, const Thread& replacement);

    /**
     * Replace a thread by another in the pattern picture.
     * Also updates the usage statistics in the threadlist.
     */
    void replaceThread(const Thread& original, const Thread& replacement);

    /**
     * @copydoc replaceThread(const Thread&, const Thread&)
     * @param selection Apply only to the selected aread
     */
    void replaceThread(const Thread& original, const Thread& replacement, Selection& selection);

    /**
     * Returns a copy of the pixel buffer where pixels with a specific thread are highlighted
     */
    std::vector<ColorSpace::ColorRGBA> highlight(const Thread& hl) const;

    /**
     * @copydoc highlight(const Thread&)
     * @param selection Apply only to the selected aread
     */
    std::vector<ColorSpace::ColorRGBA> highlight(const Thread& hl, Selection& selection) const;

private:
    ThreadList m_threadList;

    FileFormat m_format;
    std::vector<uint8_t> m_originalPicture;
    std::vector<uint8_t> m_resizedPicture;

    size_t m_width;  /**< Width of the pattern picture */
    size_t m_height; /**< Height of the pattern picture */
    std::vector<ColorSpace::ColorRGBA> m_patternPicture;
};

#endif // PICTURE_HPP
