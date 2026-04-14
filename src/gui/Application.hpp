/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef APPLICATION_HPP
#define APPLICATION_HPP

// Qt
#include <QAction>
#include <QLabel>

class Application {
public:
    static int main(int argc, char** argv);

    /**
     * @copydoc replaceVersionVars(QString&)
     * @param win Widget - call replaceVersionVars on specific properties of the widget
     */
    static void replaceVersionVars(QWidget* win);

    /**
     * @copydoc replaceVersionVars(QString&)
     * @param action Action Widget - call replaceVersionVars on specific properties of the widget
     */
    static void replaceVersionVars(QAction* action);

    /**
     * @copydoc replaceVersionVars(QString&)
     * @param label Label Widget - call replaceVersionVars on specific properties of the widget
     */
    static void replaceVersionVars(QLabel* label);
};

#endif // APPLICATION_HPP
