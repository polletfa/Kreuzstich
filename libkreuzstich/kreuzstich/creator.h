/* $Id: creator.h 53 2016-01-11 18:34:15Z polletfa $

   Copyright (C) 2013-2020 Fabien Pollet <polletfa@posteo.de>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/
/**
 * \mainpage Kreuzstich 
 * Kreuzstich generates a kreuzstich grid from a picture
 * as well as a list of required threads.
 *
 * All classes and functions belong to the namespace Kreuzstich, except the main function.
 */
#ifndef KREUZSTICH_CREATOR_H
#define KREUZSTICH_CREATOR_H

#include <string>

#include <Magick++.h>

#include <kreuzstich/thread.h>
#include <kreuzstich/report.h>

namespace Kreuzstich {

    class ColorHash {
    public:
        std::size_t operator()(const ThreadColor& col) const;
    };

    class ProgressCallback {
    public:
        // value between 0 and 1
        virtual void operator()(double percent) = 0;
    };

    class _NoProgressCallback : public ProgressCallback {
        void operator()(double percent) {}
    };
    extern _NoProgressCallback NoProgressCallback;

    class Creator {
    public:
        Creator();
        Creator(size_t width, size_t height, ThreadColor fill);
        Creator(std::string filename);
        ~Creator();

        size_t width() const;
        size_t height() const;
        const Magick::Image& image() const;
        ThreadColors colortable() const;
        void setColortable(std::string colortable);

        std::map<std::string, std::string> properties() const;
        void clearProperties();
        bool hasProperty(std::string key);
        void setProperty(std::string key, std::string value);
        std::string property(std::string key);

        void importPicture(std::string);

        /**
         * Resize the image
         * \param width Width
         * \param height Height
         * \throws std::exception
         */
        void resize(size_t width, size_t height);
        /**
         * Reduce the number of colors.
         * \param maxColors Maximum number of colors
         * \throws std::exception
         */
        void quantizeColors(size_t maxColors);
        /**
         * Choose a thread for each pixel.
         * \throws std::exception
         */
        void chooseThreads(ProgressCallback& callback = NoProgressCallback);

        /**
         * Create the grid and save into a file.
         *
         * Note: always call \ref chooseThread before writing the grid.
         *
         * \param filename Output file name
         * \param callback Callback object for progress notification
         * \throws std::exception
         */
        void writeGrid(std::string filename, ProgressCallback& callback = NoProgressCallback);
        /**
         * Create the script and save into a file.
         *
         * Note: always call \ref chooseThread before writing the script.
         *
         * \param script Writer (LaTeXWriter or TextWriter)
         * \param header Header
         * \throws std::exception
         */
        void writeScript(Report::Writer& script, Report::Header header);

        void writeProjectFile(std::string filename);

    private:
        static const int PROJECT_FILE_FORMAT_VERSION;

        static std::string dateString();
        static std::string escapeStringForXMLTag(std::string);
        static void xmlNullErrorHandler(void*, const char*, ...);

        void initInternProperties();

        Magick::Image m_image;          /**< Image data */
        size_t m_columns;               /**< Width */
        size_t m_rows;                  /**< Height */
        ThreadColors m_colortable;      /**< Color table */
        ThreadColors m_required;        /**< List of required colors */
        std::map<std::string, std::string> m_properties;
    };
    
}

#endif
