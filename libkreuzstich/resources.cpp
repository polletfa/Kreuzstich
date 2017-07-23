/* $Id: resources.cpp 44 2015-05-11 20:48:11Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#include <kreuzstich/resources.h>
#include <kreuzstich/exceptions.h>

#include <sstream>

#include <boost/filesystem.hpp>

using namespace std;
namespace fs = boost::filesystem;

const std::string Kreuzstich::USERCONFIG_FOLDER = std::string(".kreuzstich");
const std::string Kreuzstich::COLORTABLE_DEFAULT = std::string("default");
const std::string Kreuzstich::COLORTABLE_EXTENSION = std::string("colors");

std::string Kreuzstich::versionString() {
    std::stringstream ss;
    ss << PROJECT_NAME << " " << MAJOR_VERSION << "." << MINOR_VERSION << "r"<<SVN_REVISION << " build " << BUILD_TIME
       << " " << SYSTEM << " " << PROCESSOR;
    return ss.str();
}

std::vector<std::string> Kreuzstich::threadLists() {
    std::vector<std::string> list;

    try {
        fs::directory_iterator end;
        for( fs::directory_iterator dir(string(getenv("HOME"))+"/"+Kreuzstich::USERCONFIG_FOLDER) ; dir != end ; ++dir) {
            if (fs::is_regular_file(dir->path()) && !dir->path().extension().string().compare(".colors")) {
                if(!dir->path().filename().string().compare(Kreuzstich::COLORTABLE_DEFAULT+"."+Kreuzstich::COLORTABLE_EXTENSION)) {
                    list.insert(list.begin(), dir->path().stem().string());
                } else {
                    list.push_back(dir->path().stem().string());
                }
            }
        }
        return list;
    } catch(...) {
        throw ColorTablesNotFound();
    }
}
