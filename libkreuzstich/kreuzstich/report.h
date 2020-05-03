/* $Id: report.h 40 2015-05-09 21:05:15Z polletfa $

   Copyright (C) 2013-2020 Fabien Pollet <polletfa@posteo.de>

   Weiterverbreitung und Verwendung in nichtkompilierter oder
   kompilierter Form, mit oder ohne Veränderungen, sind ohne Bedingungen
   zulässig.
   Diese Software wird ohne Garantien vom Autor zur Verfügung gestellt.
*/

#ifndef KREUZSTICH_REPORT_H
#define KREUZSTICH_REPORT_H

#include <string>
#include <fstream>
#include <vector>

#include <kreuzstich/units.h>

namespace Kreuzstich {

    namespace Report {

        struct Header {
            std::string generator;
            std::string colortable;
            size_t count;
            Length margin;
            Length::Unit unit;
        };
        
        class NewLine {};
        class NewPage {};
        class HLine {};

        struct Enumeration {
            Enumeration(int _start) : start(_start) {}
            int start;
            std::vector<std::string> items;
        };

        enum TableAlignment { left, centered, right };
        
        struct TableColumnProperties {
            TableColumnProperties(bool ll, bool lr, size_t w, TableAlignment a)
                : line_left(ll), line_right(lr), columnWidth(w), alignment(a) {}
            bool line_left;
            bool line_right;
            size_t columnWidth;
            TableAlignment alignment;
        };
        
        struct TableProperties {
            std::vector<TableColumnProperties> columnProperties;
        };

        struct TableCell {
            TableCell(size_t s, std::string c) : span(s), content(c) {}
            size_t span;
            std::string content;
            TableAlignment alignment; // only with span > 1
        };

        struct TableRowProperties {
            TableRowProperties(bool la, bool lb) : line_above(la), line_below(lb) {}
            bool line_above;
            bool line_below;
        };
        
        struct TableRow {
            TableRow(TableRowProperties prop) : properties(prop) {}
            TableRowProperties properties;
            std::vector<TableCell> cells;
        };

        struct Table {
            Table(TableProperties prop) : properties(prop) {}
            TableProperties properties;
            std::vector<TableRow> rows;
        };

        struct Fraction {
            Fraction(int num, int denom) : numerator(num), denominator(denom) {}
            int numerator;
            int denominator;
        };

        struct LengthIN {
            LengthIN(double d) : length(Length(d, Length::IN).fraction()) {}
            LengthIN(Length l) : length(l.fraction()) {}
            std::pair<int, std::pair<int, int> > length;
        };
        struct LengthCM {
            LengthCM(Length l) : length(l.cm()) {}
            double length;
        };
        
        extern NewLine newline;
        extern NewPage newpage;
        extern HLine hline;

        class Writer {
        public:
            Writer(std::string filename);

            std::string filename() const;
            bool is_open() const;
            void fill(char);
            void width(std::streamsize);

            Writer& operator<<(LengthIN l);
            Writer& operator<<(LengthCM l);
            Writer& operator<<(int right);
            Writer& operator<<(size_t right);
            Writer& operator<<(double right);
            Writer& operator<<(const char* right);
            Writer& operator<<(std::string right);
            Writer& operator<<(NewLine& nl);
            Writer& operator<<(NewPage& np);
            Writer& operator<<(HLine& hl);
            Writer& operator<<(Enumeration& en);
            Writer& operator<<(Table& tb);
            Writer& operator<<(Fraction& f);
            
            virtual void newline() = 0;
            virtual void newpage() = 0;
            virtual void hline() = 0;
            virtual void enumeration(Enumeration& enumeration) = 0;
            virtual void table(Table& table) = 0;
            virtual void fraction(Fraction& f) = 0;
            virtual void close() = 0;

        protected:
            std::string m_filename;
            std::ofstream m_stream;
        };

        class LaTeXWriter : public Writer {
        public:
            LaTeXWriter(std::string filename);

            void close();

            void newline();
            void newpage();
            void hline();
            void enumeration(Enumeration& enumeration);
            void table(Table& table);
            void fraction(Fraction& f);
        };
        
        class TextWriter : public Writer {
        public:
            TextWriter(std::string filename);

            void close();

            void newline();
            void newpage();
            void hline();
            void enumeration(Enumeration& enumeration);
            void table(Table& table);
            void fraction(Fraction& f);
            
        private:
            void tableline(Table& table);
            void printaligned(std::string text, size_t width, TableAlignment align);

        };
    }    
}

#endif

