/* $Id: units.h 40 2015-05-09 21:05:15Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#ifndef KREUZSTICH_UNITS_H
#define KREUZSTICH_UNITS_H

#include <string>
#include <utility>

namespace Kreuzstich {

    class Length {
    public:
        enum Unit { CM, IN };
        Length();
        Length(double, Unit unit = Length::CM);
        Length(std::string value, Unit unit = Length::CM);
        double in() const;
        std::pair<int, std::pair<int, int> > fraction() const;
        double cm() const;

    private:
        double m_in;
        double m_cm;
    };    

}

#endif
