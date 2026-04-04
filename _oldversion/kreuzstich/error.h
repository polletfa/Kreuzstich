#ifndef ERROR_H
#define ERROR_H

// stdlib & stl
#include <string>

// libkreuzstich
#include "kreuzstich/exceptions.h"

// Qt
#include <QString>
class QWidget;

namespace KreuzstichGUI {

    std::string getErrorMessage(const Kreuzstich::Exception& exc);
    void genericErrorDialog(QWidget* parent, const std::exception& exc);
    void genericErrorDialog(QWidget* parent, const Kreuzstich::Exception& exc);
    void genericErrorDialog(QWidget* parent, const QString& msg);

}

#endif // ERROR_H
