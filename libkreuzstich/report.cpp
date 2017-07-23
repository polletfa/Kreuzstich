/* $Id: report.cpp 43 2015-05-10 21:34:40Z polletfa $

   Copyright (C) 2013 Fabien Pollet <polletfa@gmail.com>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/
#include <iostream>
#include <iomanip>

#include <boost/lexical_cast.hpp>

#include <kreuzstich/report.h>

using namespace Kreuzstich;
using namespace Report;
using namespace std;

NewLine Report::newline;
NewPage Report::newpage;
HLine Report::hline;

Writer::Writer(std::string filename)
    : m_stream(filename.c_str(), std::ofstream::out), m_filename(filename)
{}

std::string Writer::filename() const { return m_filename; }
bool Writer::is_open() const { return m_stream.is_open(); }
void Writer::fill(char f) { m_stream.fill(f); }
void Writer::width(std::streamsize w) { m_stream.width(w); }

Writer& Writer::operator<<(LengthIN l) {
    m_stream << l.length.first << "\"";
    if(l.length.second.first > 0.001) {
        Fraction f(l.length.second.first, l.length.second.second);
        *this << f;
    }
    return *this;
}

Writer& Writer::operator<<(LengthCM l) {
    *this << l.length << "cm";
    return *this;
}

Writer& Writer::operator<<(int right) {
    m_stream << right;
    return *this;
}

Writer& Writer::operator<<(size_t right) {
    m_stream << right;
    return *this;
}

Writer& Writer::operator<<(double right) {
    m_stream << fixed << setprecision(1) << right;
    return *this;
}

Writer& Writer::operator<<(const char* text) {
    m_stream << text;
    return *this;
}

Writer& Writer::operator<<(std::string text) {
    m_stream << text;
    return *this;
}

Writer& Writer::operator<<(NewLine& nl) {
    newline();
    return *this;
}

Writer& Writer::operator<<(NewPage& np) {
    newpage();
    return *this;
}

Writer& Writer::operator<<(HLine& hl) {
    hline();
    return *this;
}

Writer& Writer::operator<<(Enumeration& en) {
    enumeration(en);
    return *this;
}

Writer& Writer::operator<<(Table& tb) {
    table(tb);
    return *this;
}

Writer& Writer::operator<<(Fraction& f) {
    fraction(f);
    return *this;
}

LaTeXWriter::LaTeXWriter(std::string filename)
    : Writer(filename)
{
    m_stream << "\\documentclass[8pt, a4paper]{article}" << endl
             << "\\usepackage[top=2cm,left=1cm,right=1cm,bottom=2cm]{geometry}" << endl
             << "\\usepackage{longtable}" << endl
             << "\\setlength{\\parindent}{0pt}" << endl
             << "\\begin{document}%" << endl;
}

void LaTeXWriter::close() {
    m_stream << "\\end{document}" << endl;
    m_stream.close();
}

void LaTeXWriter::newline() { m_stream << "\\\\%" << endl; }
void LaTeXWriter::newpage() { m_stream << "\\newpage%" << endl; }
void LaTeXWriter::hline() { m_stream << "\\par\\rule[1ex]{\\textwidth}{1pt}\\par%" << endl; }
void LaTeXWriter::enumeration(Enumeration& enumeration) {
    m_stream << "\\begin{enumerate}%" << endl
             << "\\setcounter{enumi}{" << enumeration.start - 1 << "}%" << endl
             << "\\setlength\\itemsep{0em}%" << endl;
    for(int i = 0; i < enumeration.items.size(); i++) {
        m_stream << "\\item " << enumeration.items[i] << "%" << endl;
    }
    m_stream << "\\end{enumerate}%" << endl;
}
void LaTeXWriter::table(Table& tb) {
    // header
    m_stream << "\\begin{longtable}{";
    for(vector<TableColumnProperties>::iterator it = tb.properties.columnProperties.begin();
        it != tb.properties.columnProperties.end(); it++) {
        if(it->line_left) m_stream << "|";
        if(it->alignment == Report::left) m_stream << "l";
        else if(it->alignment == Report::centered) m_stream<< "c";
        else m_stream << "r";
        if(it->line_right) m_stream<<"|";
    }
    m_stream << "}%" << endl;

    // rows
    for(vector<TableRow>::iterator it = tb.rows.begin(); it != tb.rows.end(); it++) {
        if(it->properties.line_above)
            m_stream << "\\hline%" << endl;

        int ci = 0;
        for(vector<TableCell>::iterator cellit = it->cells.begin(); cellit != it->cells.end(); cellit ++) {
            if(cellit->span > 1) {
                m_stream << "\\multicolumn{" << cellit->span << "}{";
                if(tb.properties.columnProperties[ci].line_left) m_stream<<"|";
                if(cellit->alignment == Report::left) m_stream << "l";
                else if(cellit->alignment == Report::centered) m_stream << "c";
                else m_stream << "r";
                m_stream << "}{" << cellit->content << "}";
                if(tb.properties.columnProperties[ci+cellit->span-1].line_right) m_stream<<"|";
                ci += cellit->span;
            } else {
                m_stream << cellit->content;
                ci++;
            }

            if(ci < tb.properties.columnProperties.size())
                m_stream << "&";
            else
                m_stream << "\\\\%"<<endl;
        }
        
        if(it->properties.line_below)
            m_stream << "\\hline%" << endl;
    }

    m_stream << "\\end{longtable}%"<<endl;
}
void LaTeXWriter::fraction(Fraction& f) {
    m_stream << "$\\frac{" << f.numerator << "}{" << f.denominator << "}$";
}

TextWriter::TextWriter(std::string filename)
    : Writer(filename)
{}

void TextWriter::close() {
    m_stream.close();
}

void TextWriter::newline() { m_stream << endl; }
void TextWriter::newpage() { m_stream << endl; }
void TextWriter::hline() {
    m_stream << endl << "------------------------------------------------" << endl;
}

void TextWriter::enumeration(Enumeration& enumeration) {
    m_stream << endl;
    for(int i = 0; i < enumeration.items.size(); i++) {
        m_stream << setfill(' ') << setw(boost::lexical_cast<string>(enumeration.start + enumeration.items.size() - 1).size()) << i
                 << ": " << enumeration.items[i] << endl;
    }
}

void TextWriter::tableline(Table& tb) {
    for(vector<TableColumnProperties>::iterator propit = tb.properties.columnProperties.begin();
        propit != tb.properties.columnProperties.end(); propit++) {
        
        for(int i = 0; i < propit->columnWidth + 2; i++)
            m_stream << "-";       
    }
    m_stream << endl;
}

void TextWriter::printaligned(std::string text, size_t width, TableAlignment align) {
    int i = 0;
    if(align == Report::centered) {
        for(; i *2 < width - text.size(); i++)
            m_stream << " ";
    } else if(align == Report::right) {
        for(i = text.size(); i < width; i++)
            m_stream << " ";
    }
    
    m_stream << text;

    if(align == Report::centered) {
        for(i += text.size(); i < width; i++)
            m_stream << " ";
    } else if(align == Report::left) {
        for(i = text.size(); i < width; i++)
            m_stream << " ";
    }
}
                          
void TextWriter::table(Table& tb) {
    m_stream << endl;

    for(vector<TableRow>::iterator it = tb.rows.begin(); it != tb.rows.end(); it++) {
        if(it->properties.line_above)
            tableline(tb);

        int ci = 0;
        for(vector<TableCell>::iterator cellit = it->cells.begin(); cellit != it->cells.end(); cellit ++) {
            if(tb.properties.columnProperties[ci].line_left)
                m_stream << "| ";
            else
                m_stream << " ";

            int spanwidth = 0;
            TableAlignment align;
            if(cellit->span > 1) {
                for(int i = 0; i < cellit->span; i++)
                    spanwidth += tb.properties.columnProperties[ci+i].columnWidth+2;
                spanwidth -= 2;
                align = cellit->alignment;
            } else {
                spanwidth = tb.properties.columnProperties[ci].columnWidth;
                align = tb.properties.columnProperties[ci].alignment;
            }

            printaligned(cellit->content, spanwidth, align);
            ci+= cellit->span;

            if(tb.properties.columnProperties[ci+cellit->span-1].line_right)
                m_stream << " |";
            else
                m_stream << " ";

            if(ci >= tb.properties.columnProperties.size())
                m_stream << endl;
        }
        
        if(it->properties.line_below)
            tableline(tb);
    }

    m_stream << endl;
}

void TextWriter::fraction(Fraction& f) {
    m_stream << f.numerator << "/" << f.denominator;
}

