/* $Id: creator.cpp 53 2016-01-11 18:34:15Z polletfa $

   Copyright (C) 2013-2020 Fabien Pollet <polletfa@posteo.de>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>

#include <boost/lexical_cast.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <kreuzstich/creator.h>
#include <kreuzstich/resources.h>
#include <kreuzstich/exceptions.h>

#include <libxml/encoding.h>
#include <libxml/xmlwriter.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

using namespace std;
using namespace Kreuzstich;
using namespace Magick;

namespace pt = boost::property_tree;

// size (in pixel) of a cell in the grid
#define GRID_RESOLUTION 10
// number of cells between two thick lines
#define GRID_MOD 10

Kreuzstich::_NoProgressCallback Kreuzstich::NoProgressCallback;

std::size_t ColorHash::operator()(const ThreadColor& col) const {
    return col.hash();
}

const int Creator::PROJECT_FILE_FORMAT_VERSION = 1;

Creator::Creator() : m_columns(0), m_rows(0) {
    initInternProperties();
}
Creator::Creator(size_t width, size_t height, ThreadColor fill)
    : m_columns(width), m_rows(height), m_image(Magick::Geometry(width, height), fill.rgb())
{
    initInternProperties();
}

Creator::Creator(std::string filename) {
    xmlDocPtr doc;
    xmlGenericErrorFunc nullerror = &Creator::xmlNullErrorHandler;
    initGenericErrorDefaultFunc(&nullerror);
    doc = xmlReadFile(filename.c_str(), NULL, 0);
    if (doc == NULL) {
        xmlErrorPtr err = xmlGetLastError();
        if(err->domain == XML_FROM_IO)
            throw FileIOError(filename, errno);
        else if(err->domain == XML_FROM_MEMORY)
            throw MemoryError();
        else
            throw InvalidFileFormat(filename);
    }
    xmlNodePtr root = xmlDocGetRootElement(doc);

    // check version
    if(!xmlStrEqual(root->name, BAD_CAST "kreuzstich"))
        throw InvalidFileFormat(filename);
    xmlChar* version = xmlGetProp(root, BAD_CAST "version");
    if(version == NULL) throw InvalidFileFormat(filename);
    try {
        int ver = boost::lexical_cast<int>((const char*)version);
        if(ver > PROJECT_FILE_FORMAT_VERSION) {
            if(version) xmlFree(version);
            throw WrongFileFormatVersion(filename, ver, PROJECT_FILE_FORMAT_VERSION);
        }
    } catch(boost::bad_lexical_cast& exc) {
        if(version) xmlFree(version);
        throw InvalidFileFormat(filename);
    }
    if(version) xmlFree(version);

    // find properties, colortable & picture nodes
    xmlNodePtr properties, picture, colortable;
    for(xmlNodePtr cur = root->children; cur; cur = cur->next) {
        if(xmlStrEqual(cur->name, BAD_CAST "properties"))
            properties = cur;
        else if(xmlStrEqual(cur->name, BAD_CAST "colortable"))
            colortable = cur;
        else if(xmlStrEqual(cur->name, BAD_CAST "picture"))
            picture = cur;
    }
    if(!properties || !picture || !colortable)
        throw InvalidFileFormat(filename);

    // properties
    for(xmlNodePtr cur = properties->children; cur; cur = cur->next) {
        xmlChar* content = xmlNodeGetContent(cur);
        if(cur->name && content)
            setProperty((const char*)cur->name, (const char*)content);
        if(content) xmlFree(content);
    }

    // colortable
    xmlChar* ctname = xmlGetProp(colortable, BAD_CAST "name");
    if(ctname) {
        m_colortable.setName((const char*)ctname);
        xmlFree(ctname);
    }
    for(xmlNodePtr cur = colortable->children; cur; cur = cur->next) {
        // color
        ThreadColor rgb;
        xmlChar* rchar, *gchar, *bchar;
        try {
            double r, g, b;
            rchar = xmlGetProp(cur, BAD_CAST "r");
            gchar = xmlGetProp(cur, BAD_CAST "g");
            bchar = xmlGetProp(cur, BAD_CAST "b");
            if(!bchar || !gchar | !rchar) throw 1;
            r = boost::lexical_cast<double>((const char*)rchar);
            g = boost::lexical_cast<double>((const char*)gchar);
            b = boost::lexical_cast<double>((const char*)bchar);
            rgb = ColorRGB(r, g, b);
        } catch(...) {
            if(rchar) xmlFree(rchar);
            if(gchar) xmlFree(gchar);
            if(bchar) xmlFree(bchar);
            throw InvalidFileFormat(filename);
        }

        ThreadIDList idlist;
        if(cur->children) {
            for(xmlNodePtr cur2 = cur->children; cur2; cur2 = cur2->next) {
                xmlChar* content = xmlNodeGetContent(cur2);
                idlist.push_back(string((const char*)content));
                if(content) xmlFree(content);
            }
        }
        m_colortable[rgb] = idlist;
    }

    // picture
    xmlChar* pencoded = xmlNodeGetContent(picture);
    if(!pencoded) throw InvalidFileFormat(filename);
    size_t length = xmlStrlen(pencoded) / 2;
    char* data = new char[length];
    const char* src = (const char*)pencoded;
    char* dst = data;
    try {
        for(int i = 0; i < length; i++) {
            int h, l;
            if(*src >= '0' && *src <= '9') h = *src - '0';
            else if(*src >= 'a' && *src <= 'f') h = *src - 'a' + 10;
            else throw 1;
            src++;
            if(*src >= '0' && *src <= '9') l = *src - '0';
            else if(*src >= 'a' && *src <= 'f') l = *src - 'a' + 10;
            else throw 1;
            src++;

            *dst = (h<<4) | l;
            dst++;
        }
        Magick::Blob blob(data, length);
        m_image.read(blob, "MIFF");
        m_columns = m_image.columns();
        m_rows = m_image.rows();
    } catch(...) {
        if(pencoded) xmlFree(pencoded);
        delete[] data;
        throw InvalidFileFormat(filename);
    }
    if(pencoded) xmlFree(pencoded);
    delete[] data;

    xmlFreeDoc(doc);
}

Creator::~Creator() {}

void Creator::importPicture(std::string filename) {
    // import a picture file
    try {
        m_image.read(filename);
        m_columns = m_image.columns();
        m_rows = m_image.rows();
        initInternProperties();
        setProperty("pictureImportedFrom", filename);
    } catch(Magick::ErrorFileOpen&) {
        throw FileIOError(filename, errno);
    } catch(Magick::WarningFileOpen&) {
        throw FileIOError(filename, errno);

    } catch(Magick::ErrorCorruptImage&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningCorruptImage&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorOption&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningOption&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorMissingDelegate&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningMissingDelegate&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorResourceLimit&) {
        throw MemoryError();
    } catch(Magick::WarningResourceLimit&) {
        throw MemoryError();

    } catch(Magick::Error& exc) {
        throw UnknownError();
    } catch(Magick::Warning& exc) {
        throw UnknownError();
    } catch(std::exception& e) {
        throw UnknownError();
    }
}

void Creator::initInternProperties() {
    char* oldlocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C"); // we want to avoid localized format

    setProperty("createdOn", dateString());
    setProperty("createdWithLibraryVersion", versionString());

    setlocale(LC_ALL, oldlocale);
}

ThreadColors Creator::colortable() const { return m_colortable; }
size_t Creator::width() const { return m_columns; }
size_t Creator::height() const { return m_rows; }
const Magick::Image& Creator::image() const { return m_image; }

bool Creator::hasProperty(string key) { return m_properties.find(key) != m_properties.end(); }
std::map<std::string, std::string> Creator::properties() const { return m_properties; }
void Creator::clearProperties() { m_properties.clear(); }
void Creator::setProperty(std::string key, std::string prop) {
    m_properties[key] = prop;
}
std::string Creator::property(std::string key) {
    if(hasProperty(key))
        return m_properties[key];
    else
        return "";
}

void Creator::resize(size_t width, size_t height) {
    Geometry geom(width, height);
    geom.aspect(true);
    m_image.resize(geom);
    m_columns = m_image.columns();
    m_rows = m_image.rows();
}

void Creator::setColortable(string colortable) {
    m_colortable = ThreadColors(colortable);
}

void Creator::quantizeColors(size_t maxColors) {
    if(maxColors > 0) {
        m_image.quantizeColorSpace( YUVColorspace );
        m_image.quantizeColors(maxColors);
        m_image.quantizeDither(true);
        m_image.quantize();
    }
}

void Creator::chooseThreads(ProgressCallback& callback) {
    typedef std::map<ThreadColor, std::pair<ThreadIDList, int>, ColorComparator > ThreadColorsWithCounter;
    ThreadColorsWithCounter requiredThreads;

    // select the best match for each pixel
    unordered_map<ThreadColor, ThreadColor, ColorHash> bestMatches;
    for(int x = 0, i = 0; x < m_columns; ++x) {
        for(int y = 0; y < m_rows; ++y, ++i) {
            ThreadColor rgb(m_image.pixelColor(x, y));
            unordered_map<ThreadColor, ThreadColor, ColorHash>::iterator it = bestMatches.find(rgb);
            ThreadColors::const_iterator bestMatch;
            if(it != bestMatches.end()) {
                bestMatch = m_colortable.bestMatch(it->second);
            } else {
                bestMatch = m_colortable.bestMatch(rgb);
                bestMatches[rgb] = bestMatch->first;
            }
            // add to list of required threads
            auto found = requiredThreads.find(bestMatch->first);
            if(found == requiredThreads.end()) {
                requiredThreads[bestMatch->first] = std::make_pair(bestMatch->second, 1);
            } else {
                found->second.second ++;
            }
            // change pixel
            m_image.pixelColor(x, y, bestMatch->first.rgb());
            
            if(!(i%100))
                callback((double)i/(m_columns*m_rows));
        }
    }

    // for all colors with less than 10 stitches, replace by the closest color among the rest
    ThreadColors requiredFiltered;
    ThreadColors toBeReplaced;
    int threshold = 10;
    for(ThreadColorsWithCounter::iterator it = requiredThreads.begin(); it != requiredThreads.end(); it++) {
        if(it->second.second >= threshold) {
            requiredFiltered[it->first] = it->second.first;
        } else {
            toBeReplaced[it->first] = it->second.first;
        }
    }
    for(int x = 0, i = 0; x < m_columns; ++x) {
        for(int y = 0; y < m_rows; ++y, ++i) {
            ThreadColor rgb(m_image.pixelColor(x, y));
            m_image.pixelColor(x, y, requiredFiltered.bestMatch(rgb)->first.rgb());
        }
    }

    // save list of required threads
    m_required.clear();
    for(ThreadColors::iterator it = requiredFiltered.begin(); it != requiredFiltered.end(); it++) {
        m_required[it->first] = it->second;
    }
}

void Creator::writeProjectFile(string filename) {
    char* oldlocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "C"); // we want to avoid localized format
    setProperty("lastModifiedOn", dateString());
    setProperty("lastModifiedWithLibraryVersion", versionString());

    xmlTextWriterPtr writer;
    const char* encoding = "UTF-8";

    writer = xmlNewTextWriterFilename(filename.c_str(), 1);
    if (writer == NULL) {
        setlocale(LC_ALL, oldlocale);
        xmlErrorPtr err = xmlGetLastError();
        if(err->domain == XML_FROM_IO)
            throw FileIOError(filename, errno);
        else if(err->domain == XML_FROM_MEMORY)
            throw MemoryError();
        else
            throw UnknownError();
    }

    xmlTextWriterStartDocument(writer, NULL, encoding, NULL);
    xmlTextWriterStartElement(writer, BAD_CAST "kreuzstich");
    xmlTextWriterWriteFormatAttribute(writer, BAD_CAST "version", "%d", PROJECT_FILE_FORMAT_VERSION);

    // properties
    xmlTextWriterStartElement(writer, BAD_CAST "properties");
    for(std::map<std::string,std::string>::const_iterator it = m_properties.begin(); it != m_properties.end(); it++) {
        xmlTextWriterWriteElement(writer, BAD_CAST escapeStringForXMLTag(it->first).c_str(), BAD_CAST it->second.c_str());
    }
    xmlTextWriterEndElement(writer);

    // colortable
    xmlTextWriterStartElement(writer, BAD_CAST "colortable");
    xmlTextWriterWriteAttribute(writer, BAD_CAST "name", BAD_CAST m_colortable.name().c_str());
    for(ThreadColors::const_iterator it = m_colortable.begin(); it != m_colortable.end(); ++it) {
        xmlTextWriterStartElement(writer, BAD_CAST "color");
        xmlTextWriterWriteFormatAttribute(writer, BAD_CAST "r", "%f", it->first.rgb().red());
        xmlTextWriterWriteFormatAttribute(writer, BAD_CAST "g", "%f", it->first.rgb().green());
        xmlTextWriterWriteFormatAttribute(writer, BAD_CAST "b", "%f", it->first.rgb().blue());
        for(ThreadIDList::const_iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
            xmlTextWriterWriteElement(writer, BAD_CAST "thread", BAD_CAST it2->c_str());
        xmlTextWriterEndElement(writer);
    }
    xmlTextWriterEndElement(writer);

    // picture
    xmlTextWriterStartElement(writer, BAD_CAST "picture");
    try {
        Blob blob;
        Magick::Image im = m_image;
        im.modifyImage();
        im.write(&blob, "MIFF");
        char* encodedblob = new char[blob.length() * 2 + 1];
        const char* src = (const char*)blob.data();
        char* dst = encodedblob;
        const char* digits = "0123456789abcdef";
        for(int i = 0; i < blob.length(); i++, src++) {
            *(dst++) = digits[(*src>>4) & 0xf];
            *(dst++) = digits[*src&0xf];
        }
        *dst= 0;
        xmlTextWriterWriteCDATA(writer, BAD_CAST encodedblob);
        delete[] encodedblob;
    } catch(Magick::ErrorResourceLimit&) {
        throw MemoryError();
    } catch(Magick::Error&) {
        throw UnknownError();
    }

    xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);

    setlocale(LC_ALL, oldlocale);
}

std::string Creator::dateString() {
    time_t rawtime;
    char datestring[2000];
    time (&rawtime);
    strftime(datestring, 2000, "%c", localtime (&rawtime));
    return std::string(datestring);
}

std::string Creator::escapeStringForXMLTag(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(!isalnum(str[i]))
            str[i] = '_';
    }
    return str;
}

void Creator::xmlNullErrorHandler(void*, const char*, ...) {}

void Creator::writePicture(std::string filename, ProgressCallback& callback) {
    try {
        callback(0);

        // save
        m_image.write(filename);
    } catch(Magick::ErrorFileOpen&) {
        throw FileIOError(filename, errno);
    } catch(Magick::WarningFileOpen&) {
        throw FileIOError(filename, errno);

    } catch(Magick::ErrorCorruptImage&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningCorruptImage&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorOption&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningOption&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorMissingDelegate&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningMissingDelegate&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorResourceLimit&) {
        throw MemoryError();
    } catch(Magick::WarningResourceLimit&) {
        throw MemoryError();

    } catch(Magick::Error&) {
        throw UnknownError();
    } catch(Magick::Warning&) {
        throw UnknownError();
    } catch(std::exception&) {
        throw UnknownError();
    }
}

void Creator::writeGrid(std::string filename, ProgressCallback& callback) {
    try {
        callback(0);

        // clone image
        Image grid = m_image;
        grid.modifyImage();

        // scale up. GRID_RESOLUTION pixels per pixel
        grid.scale(Geometry(m_columns*GRID_RESOLUTION,m_rows*GRID_RESOLUTION));
        // draw the grid (thick line every ten pixels)
        grid.strokeColor("#000000");
        for(int x = 1; x < m_columns; x++) {
            if(!(x % GRID_MOD)) grid.strokeWidth(3);
            else grid.strokeWidth(1);
            grid.draw(DrawableLine(x*GRID_RESOLUTION,0,x*GRID_RESOLUTION,m_rows*GRID_RESOLUTION));
            callback(0.5*x/(m_columns-1));
        }
        for(int y = 1; y < m_rows; y++) {
            if(!(y % GRID_MOD)) grid.strokeWidth(2);
            else grid.strokeWidth(1);
            grid.draw(DrawableLine(0,y*GRID_RESOLUTION,m_columns*GRID_RESOLUTION,y*GRID_RESOLUTION));
            callback(0.5+0.5*y/(m_rows-1));
        }
        // save
        grid.write(filename);
    } catch(Magick::ErrorFileOpen&) {
        throw FileIOError(filename, errno);
    } catch(Magick::WarningFileOpen&) {
        throw FileIOError(filename, errno);

    } catch(Magick::ErrorCorruptImage&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningCorruptImage&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorOption&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningOption&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorMissingDelegate&) {
        throw InvalidFileFormat(filename);
    } catch(Magick::WarningMissingDelegate&) {
        throw InvalidFileFormat(filename);

    } catch(Magick::ErrorResourceLimit&) {
        throw MemoryError();
    } catch(Magick::WarningResourceLimit&) {
        throw MemoryError();

    } catch(Magick::Error&) {
        throw UnknownError();
    } catch(Magick::Warning&) {
        throw UnknownError();
    } catch(std::exception&) {
        throw UnknownError();
    }
}

// ************************ todo: anpassen (progress, errrors, generate header from properties)
void Creator::writeScript(Report::Writer& script, Report::Header header) {
    cout << "Create the script... \033[s"<<flush;
    if(script.is_open()) {
        // some info
        std::string version = versionString();
        std::replace(version.begin(), version.end(), '_', '-');
        script << "Script generated by " << header.generator << " (" << version << ")" << Report::newline
               << "Date: " << dateString() << Report::newline
               << "Color table: " << header.colortable<<Report::newline
               << "Number of stitches: " << m_columns << "x" << m_rows<<Report::newline;

        if(header.count > 0) {
            // size of the pattern
            if(header.unit == Length::IN) {
                double width((double)m_columns / header.count);
                double height((double)m_rows / header.count);

                if(header.margin.cm() > 0.001) {
                    script << "Margin: " << Report::LengthIN(header.margin) << Report::newline;
                    height += header.margin.in() * 2;
                    width += header.margin.in() * 2;
                }
                script << "Size with";
                if(header.margin.cm() == 0) script << "out";
                script << " margin: " << Report::LengthIN(width) << " x "<< Report::LengthIN(height) << Report::newline;
            } else {
                double width((double)m_columns / header.count);
                double height((double)m_rows / header.count);

                if(header.margin.cm() > 0.001) {
                    script << "Margin: " << Report::LengthCM(header.margin) << Report::newline;
                    height += header.margin.cm() * 2;
                    width += header.margin.cm() * 2;
                }
                script << "Size with";
                if(header.margin.cm() == 0) script << "out";
                script << " margin: " << Report::LengthCM(width) << " x "<< Report::LengthCM(height) << Report::newline;
            }
        }
        script << Report::hline;

        size_t maxymod = m_rows / GRID_MOD + (m_rows%GRID_MOD ? 1 : 0);
        size_t maxxmod = m_columns / GRID_MOD + (m_columns%GRID_MOD ? 1 : 0);

        // list of required threads
        cout << "\033[u\033[Kthread list... "<< flush;
        script << "Required threads: ";
        Report::Enumeration threadlist(0);
        map<ThreadColor, size_t, ColorComparator> colorindex;
        map<ThreadColor, size_t, ColorComparator> colorcount;
        int i = 0;
        for(ThreadColors::iterator it = m_required.begin(); it != m_required.end(); it++, i++) {
            // save the index of the color
            colorindex.insert(pair<ThreadColor, size_t>(it->first, i));
        }

        // list of blocks per color
        map<ThreadColor, std::string, ColorComparator> blocksPerColor;
        for(ThreadColors::iterator it = m_required.begin(); it != m_required.end(); it++) {
            std::string list;
            bool first = true;
            
            for(int ymod = 0; ymod < maxymod; ymod++) {
                for(int xmod = 0; xmod < maxxmod; xmod++) {
                    bool found = false;
                    
                    for(int y = 0; y < GRID_MOD && ymod*GRID_MOD+y < m_rows && found == false; y++) {
                        for(int x = 0; x < GRID_MOD && xmod*GRID_MOD+x < m_columns && found == false; x++) {
                            ThreadColor pixel(m_image.pixelColor(xmod*GRID_MOD+x, ymod*GRID_MOD+y));
                            ThreadColors::const_iterator it2 = m_required.bestMatch(pixel);

                            if(it->first == it2->first) {
                                found = true;
                            }
                        }
                    }
                    if(found) {
                        stringstream ss;
                        if(!first) ss << ", ";
                        ss << xmod << "x" << ymod;
                        list.append(ss.str());
                        if(first) first = false;
                    }
                }
            }
            blocksPerColor.insert(pair<ThreadColor, std::string>(it->first, list));
        }
 
        // grid
        // the grid is shown by block of GRID_MOD^2 with 2 columns
        Report::TableProperties properties;
        size_t cellw = boost::lexical_cast<string>(threadlist.start + threadlist.items.size() - 1).size();
        for(int i = 0; i < 20; i++)
            properties.columnProperties.push_back(Report::TableColumnProperties(false, false, cellw, Report::right));
        properties.columnProperties.at(10).line_left = true;
        Report::Table table(properties);

        // for each block
        for(int ymod = 0; ymod < maxymod; ymod++) {
            for(int xmod = 0; xmod < maxxmod; xmod+=2) {
                // line title
                Report::TableRowProperties rowprop(true, true);
                Report::TableRow titlerow(rowprop);
                for(int c= 0; c < 2; c++) {
                    if(xmod+c < maxxmod) {
                        stringstream ss;
                        ss << "Block " << xmod+c << "x" << ymod << " ("
                           << (xmod+c)*GRID_MOD << "x" << ymod*GRID_MOD << " - "
                           << min<size_t>((xmod+c+1)*GRID_MOD-1, m_columns-1) << "x" << min<size_t>((ymod+1)*GRID_MOD-1, m_rows-1)
                           << ")";

                        Report::TableCell cell(10, ss.str());
                        cell.alignment = Report::centered;
                        titlerow.cells.push_back(cell);
                    }
                }
                table.rows.push_back(titlerow);

                // content
                for(int y = 0; y < GRID_MOD && ymod*GRID_MOD+y < m_rows; y++) {
                    Report::TableRowProperties rowprop(false, false);
                    Report::TableRow row(rowprop);

                    for(int c = 0; c < 2; c++) {
                        int x;
                        for(x = 0; x < GRID_MOD && (xmod+c)*GRID_MOD+x < m_columns; x++) {
                            ThreadColor pixel(m_image.pixelColor((xmod+c)*GRID_MOD+x, ymod*GRID_MOD+y));
                            try {
                                ThreadColors::const_iterator it = m_required.bestMatch(pixel);
                                colorcount[it->first] ++;
                                row.cells.push_back(Report::TableCell(1, boost::lexical_cast<string>(colorindex[it->first])));
                            } catch(Kreuzstich::Exception& kexc) {
                                // TODO
                            } catch(std::exception& exc) {
                                // TODO
                            }
                        }
                        for(; x < GRID_MOD; x++)
                            row.cells.push_back(Report::TableCell(1, ""));
                    }
                    table.rows.push_back(row);
                }
                cout << "\033[u\033[Kgrid " << (ymod*maxxmod+xmod+2)*100/(maxymod*maxxmod) << " %"<<flush;
            }
        }

        for(ThreadColors::iterator it = m_required.begin(); it != m_required.end(); it++) {
            stringstream ss;

            threadlist.items.push_back(it->second.toStdString() + " (" + std::to_string(colorcount[it->first]) + " stitches)");
        }

        cout << "\033[u\033[Ksaving..."<<flush;
        script << threadlist << Report::newpage;

        for(ThreadColors::iterator it = m_required.begin(); it != m_required.end(); it++) {
            stringstream ss;

            script << it->second.toStdString() + " (" + std::to_string(colorcount[it->first]) + " stitches)";
            script << Report::newline;
            script << blocksPerColor[it->first];
            script << Report::hline;
        }
        script << Report::newpage;

        script << table;

        script.close();
        cout << "\033[u\033[K"<< script.filename() << endl;
    } else {
        throw runtime_error(string("Unable to create the script file: ")+strerror(errno));
    }
}

