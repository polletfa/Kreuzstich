/* $Id: thread.cpp 53 2016-01-11 18:34:15Z polletfa $

   Copyright (C) 2013-2020 Fabien Pollet <polletfa@posteo.de>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#include <cmath>
#include <fstream>
#include <errno.h>
#include <iostream>
#include <utility>
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>

#include <kreuzstich/thread.h>
#include <kreuzstich/resources.h>
#include <kreuzstich/exceptions.h>

using namespace Kreuzstich;
using namespace std;
using namespace Magick;
namespace fs = boost::filesystem;

#if LAB_LIGHT != 50 and LAB_LIGHT != 65
#   error "LAB_LIGHT must be 50 or 65."
#endif

#if LAB_ANGLE != 2 and LAB_ANGLE != 10
#   error "LAB_ANGLE must be 2 or 10."
#endif

#if LAB_LIGHT == 50 and LAB_ANGLE == 2
#   pragma message "LAB-conversion using light D50 and angle 2°"
        // Light: D50, observer: 2°
        const double ColorLAB::XN = 95.047;
        const double ColorLAB::YN = 100.;
        const double ColorLAB::ZN = 108.883;
#elif LAB_LIGHT == 50 and LAB_ANGLE == 10
#   pragma message "LAB-conversion using light D50 and angle 10°"
        // Light: D50, observer: 10°
        const double ColorLAB::XN = 94.811;
        const double ColorLAB::YN = 100.;
        const double ColorLAB::ZN = 107.304;
#elif LAB_LIGHT == 65 and LAB_ANGLE == 2
#   pragma message "LAB-conversion using light D65 and angle 2°"
        // Light: D65, observer: 2°
        const double ColorLAB::XN = 96.422;
        const double ColorLAB::YN = 100.;
        const double ColorLAB::ZN = 82.521;
#elif LAB_LIGHT == 65 and LAB_ANGLE == 10
#   pragma message "LAB-conversion using light D65 and angle 10°"
        // Light: D65, observer: 10°
        const double ColorLAB::XN = 96.72;
        const double ColorLAB::YN = 100.;
        const double ColorLAB::ZN = 81.427;
#endif

bool ColorComparator::operator ()(const ThreadColor& a, const ThreadColor& b) const {
    if(a.hsl().hue() < b.hsl().hue()) return true;
    if(a.hsl().hue() == b.hsl().hue()) {
        if(a.hsl().lightness() < b.hsl().lightness()) return true;
        if(a.hsl().lightness() == b.hsl().lightness())
            return a.hsl().saturation() < b.hsl().saturation();
    }
    return false;
}

std::string ThreadIDList::toStdString() const {
    stringstream ss;
    int j = 0;
    for(ThreadIDList::const_iterator tlit = begin(); tlit != end(); tlit++, j++) {
        if(j > 0) ss << ", ";
        ss << *tlit;
    }
    return ss.str();
}

ColorLAB::ColorLAB()
    : ColorLAB(ColorRGB())
{}

ColorLAB::ColorLAB(double l, double a, double b)
    : m_l(l), m_a(a), m_b(b)
{}

ColorLAB::ColorLAB(ColorRGB rgb) {
    // https://de.wikipedia.org/wiki/Lab-Farbraum
    // 1: RGB -> XYZ
    // 2: XYZ -> LAB

    double x = 41.24564 * rgb.red() + 35.75761*rgb.green() + 18.04375 * rgb.blue();
    double y = 21.26729 * rgb.red() + 71.51522*rgb.green() + 7.21750* rgb.blue();
    double z = 1.93339 * rgb.red() + 11.91920*rgb.green() + 95.03041* rgb.blue();

    m_l = 116. * std::pow(y / YN, 1./3) - 16.;
    m_a = 500. * ( std::pow(x / XN, 1./3) - std::pow(y / YN, 1./3) );
    m_b = 200. * ( std::pow(y / YN, 1./3) - std::pow(z / ZN, 1./3) );
}

double ColorLAB::l() const { return m_l; }
double ColorLAB::a() const { return m_a; }
double ColorLAB::b() const { return m_b; }

ThreadColor::ThreadColor()
    : ThreadColor(ColorRGB())
{}

ThreadColor::ThreadColor(Magick::ColorRGB rgb)
    : m_rgb(rgb), m_hsl(rgb), m_lab(rgb)
{
    // hash
    m_hash = rgb.red() * 100 + rgb.green() * 10000 + rgb.blue() * 1000000;
}

bool ThreadColor::operator ==(const ThreadColor& col) const {
    return col.rgb() == rgb();
}

Magick::ColorRGB ThreadColor::rgb() const { return m_rgb; }
ColorLAB ThreadColor::lab() const { return m_lab; }
Magick::ColorHSL ThreadColor::hsl() const { return m_hsl; }
size_t ThreadColor::hash() const { return m_hash; }

double ThreadColors::distance(const ThreadColor& left, const ThreadColor& right) {
    return std::pow(std::abs(left.lab().l() - right.lab().l()), 2)
            + std::pow(std::abs(left.lab().a() - right.lab().a()), 2)
            + std::pow(std::abs(left.lab().b() - right.lab().b()), 2);
}

double ThreadColors::maxDistance() {
    return 100000000.0;
}

ThreadColors::ThreadColors() {
}

ThreadColors::ThreadColors(string colortableFile) : m_name(colortableFile) {
  // load color table
    string file;
    if(fs::is_regular_file(colortableFile)) {
        file = colortableFile;
        m_name = fs::path(file).stem().string();
    } else if(fs::is_regular_file(string(getenv("HOME")) + "/" + USERCONFIG_FOLDER + "/" + colortableFile + ".colors"))
        file = string(getenv("HOME")) + "/" + USERCONFIG_FOLDER + "/" + colortableFile + ".colors";
    else
        throw FileNotFound(colortableFile);
    ifstream colortable(file, ifstream::in);

    if(colortable.is_open()) {
        string line;
        while(getline(colortable, line)) {
            // ignore comments
            size_t p = line.find("#");
            if(p != string::npos) {
                line = line.substr(0, p);
            }
            // trim
            boost::trim_left(line);
            boost::trim_right(line);
            if(line.size() > 0) {
                // interpret the line
                boost::regex expr("([^:]+):([0-9a-fA-F]{6})");
                boost::cmatch matches;
                if(boost::regex_match(line.c_str(), matches, expr)) {
                    ThreadColor col(ColorRGB(string("#")+matches[2]));
                    iterator it = find(col);
                    if(it != end()) {
                        // already in the map. add the id
                        it->second.push_back(matches[1]);
                    } else{
                        // add to the map
                        ThreadIDList id;
                        id.push_back(matches[1]);
                        insert(value_type(col, id));
                    }
                } else {
                    // no match
                    m_linesNotUnderstood.push_back(line);
                }
            }
        }
        colortable.close();
    } else {
        throw FileIOError(file, errno);
    }
}

ThreadColors::~ThreadColors() {}

int ThreadColors::numberOfLinesNotUnderstood() { return m_linesNotUnderstood.size(); }
std::vector<std::string> ThreadColors::linesNotUnderstood() { return m_linesNotUnderstood; }

std::string ThreadColors::name() const { return m_name; }
void ThreadColors::setName(string n) { m_name = n; }

ThreadColors::const_iterator ThreadColors::itemAtIndex(size_t index) const {
    ThreadColors::const_iterator it = begin();
    for(int i = 0; it != end() && i != index; i++)
        ;
    return it;
}

ThreadColors::const_iterator ThreadColors::bestMatch(const ThreadColor& col) const {
  if(size() > 0) {
      const_iterator it = find(col);
      if(it != end()) {
          return it;
      } else {
          // not in the list. Find closest
          double mindist = maxDistance();
          const_iterator mindistcolor = begin();
          for(const_iterator it = begin(); it != end(); it++) {
              double dist = distance(it->first, col);
              if(dist < mindist) {
                  mindist = dist;
                  mindistcolor = it;
              }
          }
          return mindistcolor;
      }
  } else {
      throw EmptyColorTable(name());
  }
}


