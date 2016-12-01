/* $Id: units.cpp 44 2015-05-11 20:48:11Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include <kreuzstich/units.h>
#include <kreuzstich/exceptions.h>

using namespace std;
using namespace Kreuzstich;

#define IN_TO_CM 2.54

Length::Length() : m_in(0), m_cm(0) {}
Length::Length(double value, Length::Unit unit) {
    if(unit == Length::CM) {
        m_cm = value;
        m_in = m_cm / IN_TO_CM;
    } else {
        m_in = value;
        m_cm = m_in * IN_TO_CM;
    }
}

Length::Length(string value, Length::Unit unit) : m_in(0), m_cm(0) {
    // format: 10mm, 1cm, 0.1dm, 0.01m, 1in, 1in1/2, 1.5in

    if(value.empty()) return;
    
    try {
        boost::regex defaultunit("[0-9\\.]+");
        boost::regex metric("([0-9\\.]+)([mcd]?m)");
        boost::regex inches("([0-9]+)in([1-9][0-9]*)/([1-9][0-9]*)");
        boost::regex inchesdouble("([0-9\\.]+)in");
        boost::cmatch matches;

        if(boost::regex_match(value.c_str(), matches, defaultunit)) {
            if(unit == Length::CM) {
                m_cm = boost::lexical_cast<double>(value);
                m_in = m_cm / IN_TO_CM;
            } else {
                m_in = boost::lexical_cast<double>(value);
                m_cm = m_in * IN_TO_CM;
            }
        } else if(boost::regex_match(value.c_str(), matches, metric)) {
            m_cm = boost::lexical_cast<double>(matches[1]);
            if(!string(matches[2]).compare("mm"))
                m_cm /= 10;
            else if(!string(matches[2]).compare("dm"))
                m_cm *= 10;
            else if(!string(matches[2]).compare("m"))
                m_cm *= 100;
            m_in = m_cm / IN_TO_CM;
        } else if(boost::regex_match(value.c_str(), matches, inches)) {
            int ipart = boost::lexical_cast<int>(matches[1]);
            m_in = (double)ipart + boost::lexical_cast<double>(matches[2]) / boost::lexical_cast<double>(matches[3]);
            m_cm = m_in * IN_TO_CM;
        } else if(boost::regex_match(value.c_str(), matches, inchesdouble)) {
            m_in = boost::lexical_cast<double>(matches[1]);
            m_cm = m_in * IN_TO_CM;
        } else {
            throw InvalidLength(value);
        }
    } catch(std::exception&) {
        throw InvalidLength(value);
    }
}

std::pair<int, std::pair<int, int> > Length::fraction() const {
    pair<int, pair<int, int> > frac;
    frac.first = (int)m_in;

    double rest = m_in - (int)m_in;
    if(rest > 0.0001) {
        frac.second.first = (int)(rest*pow(2,5));
        frac.second.second = pow(2, 5);
        while(frac.second.first % 2 == 0) {
            frac.second.first /= 2;
            frac.second.second /= 2;
        }
    }
    return frac;
}

double Length::in() const { return m_in; }
double Length::cm() const { return m_cm; }
