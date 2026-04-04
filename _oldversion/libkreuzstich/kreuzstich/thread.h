/* $Id: thread.h 53 2016-01-11 18:34:15Z polletfa $

   Copyright (C) 2013-2020 Fabien Pollet <polletfa@posteo.de>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#ifndef KREUZSTICH_THREAD_H
#define KREUZSTICH_THREAD_H

#include <vector>
#include <string>

#include <Magick++.h>

/**
 * Namespace for the whole program.
 */
namespace Kreuzstich {

    /**
     * List of thread IDs.
     * Typically, the IDs are numbers (e.g. 310 for black DMC threads), but they also
     * can be names (e.g. BLANC for white DMC threads). They are stored as strings.
     * It is possible to have several IDs for a single color, for example when the thread list 
     * contains threads of different brands.
     */
    class ThreadIDList : public std::vector<std::string> {
    public:
        std::string toStdString() const;
    };

    class ColorLAB {
    public:
        ColorLAB();
        ColorLAB(double _l, double _a, double _b);
        ColorLAB(Magick::ColorRGB rgb);

        double l() const;
        double a() const;
        double b() const;

    private:
        double m_l;
        double m_a;
        double m_b;

        static const double XN;
        static const double YN;
        static const double ZN;
    };

    class ThreadColor {
    public:
        ThreadColor();
        ThreadColor(Magick::ColorRGB);

        Magick::ColorRGB rgb() const;
        ColorLAB lab() const;
        Magick::ColorHSL hsl() const;
        size_t hash() const;

        bool operator==(const ThreadColor& col) const;

    private:
        Magick::ColorRGB m_rgb;
        ColorLAB m_lab;
        Magick::ColorHSL m_hsl;
        size_t m_hash;
    };

    class ColorComparator {
    public:
        bool operator()(const ThreadColor& a, const ThreadColor& b) const;
    };

    /**
     * List of thread colors
     * For each color, a list of corresponding thread IDs is provided. It is
     * possible to assign a single thread to several colors. This is useful
     * when a color table is generated using the color table of another brand
     * and a conversion chart. For example, the Anchor thread 13 is given
     * in conversion chart as equivalent to both DMC 349 (dark coral red)
     * and 817 (very dark coral red).
     */
    class ThreadColors : public std::map<ThreadColor, ThreadIDList, ColorComparator> {
    public:
        /**
         * Default constructor
         */
        ThreadColors();
        
        /** 
         * Create the list from a color table file
         * \param colortableFile List of thread colors
         * \throws std::exception
         */
        ThreadColors (std::string colortableFile);
        ~ThreadColors();

        /**
         * Find the best match for a color.
         * \param rgb RGB value (Magick++)
         * \return Iterator to the best matching color available in the map.
         * \throws std::exception
         */
        const_iterator bestMatch(const ThreadColor& col) const;

        const_iterator itemAtIndex(size_t index) const;

        std::string name() const;
        void setName(std::string);

        int numberOfLinesNotUnderstood();
        std::vector<std::string> linesNotUnderstood();

    private:
        /**
         * Compute the distance between two colors.
         * \param left YUV value (Magick++)
         * \param right YUV value (Magick++)
         * \return Distance as a double.
         */
        static double distance(const ThreadColor& left, const ThreadColor& right);
        
        /**
         * Return the maximal possible distance between two colors.
         * \return Maximum distance between two colors.
         */
        static double maxDistance();
        
    private:
        std::string m_name;
        std::vector<std::string> m_linesNotUnderstood;
    };
}
  
#endif
