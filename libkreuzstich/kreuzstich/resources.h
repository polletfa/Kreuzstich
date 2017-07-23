/* $Id: resources.h 44 2015-05-11 20:48:11Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#ifndef KREUZSTICH_RESSOURCES_H
#define KREUZSTICH_RESSOURCES_H

#include <string>
#include <vector>

namespace Kreuzstich {

    extern const std::string USERCONFIG_FOLDER;
    extern const std::string COLORTABLE_DEFAULT;
    extern const std::string COLORTABLE_EXTENSION;

    std::vector<std::string> threadLists();
    std::string versionString();
}

#endif

