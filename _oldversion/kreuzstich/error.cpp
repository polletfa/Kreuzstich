// kreuzstich
#include "error.h"

// libkreuzstich
#include "kreuzstich/resources.h"

// boost
#include <boost/lexical_cast.hpp>

// Qt
#include <QMessageBox>

using namespace std;
using namespace KreuzstichGUI;

std::string KreuzstichGUI::getErrorMessage(const Kreuzstich::Exception &e) {
    std::string message;
    switch(e.errorCode()) {
    case Kreuzstich::Exception::EXC_MEMORY_ERROR:
        message = std::string("Insufficient memory.");
        break;
    case Kreuzstich::Exception::EXC_FILE_NOT_FOUND:
        message = std::string("The file "+dynamic_cast<const Kreuzstich::FileNotFound&>(e).fileName()+ " doesn't exist.");
        break;
    case Kreuzstich::Exception::EXC_FILE_IO_ERROR:
        message = std::string("An error occurred while accessing the file ")+dynamic_cast<const Kreuzstich::FileIOError&>(e).fileName();
        break;
    case Kreuzstich::Exception::EXC_COLOR_TABLES_NOT_FOUND:
        message = std::string("The color tables could not be found. Color tables are the *.")
                + Kreuzstich::COLORTABLE_EXTENSION +" files in the $HOME/"
                + Kreuzstich::USERCONFIG_FOLDER+ " directory.";
        break;
    case Kreuzstich::Exception::EXC_EMPTY_COLOR_TABLE:
        message = std::string("The color table is empty. Colortable: ")+dynamic_cast<const Kreuzstich::EmptyColorTable&>(e).colorTable();
        break;
    case Kreuzstich::Exception::EXC_INVALID_LENGTH:
        message = std::string("The value ")+dynamic_cast<const Kreuzstich::InvalidLength&>(e).invalidString()+" is not a valid length.";
        break;
    case Kreuzstich::Exception::EXC_INVALID_FILE_FORMAT:
        message = std::string("The file ")+dynamic_cast<const Kreuzstich::InvalidFileFormat&>(e).fileName()+" could not be loaded: wrong format.";
        break;
    case Kreuzstich::Exception::EXC_WRONG_FILE_FORMAT_VERSION:
        message = std::string("The file ")+dynamic_cast<const Kreuzstich::WrongFileFormatVersion&>(e).fileName()+" could not be loaded: wrong version (found: "
                +boost::lexical_cast<std::string>(dynamic_cast<const Kreuzstich::WrongFileFormatVersion&>(e).version())+"; expected: "
                +boost::lexical_cast<std::string>(dynamic_cast<const Kreuzstich::WrongFileFormatVersion&>(e).exceptedVersion())+").";
        break;
    }
    return message;
}

void  KreuzstichGUI::genericErrorDialog(QWidget *parent, const Kreuzstich::Exception &e) {
    genericErrorDialog(parent, getErrorMessage(e).c_str());
}

void KreuzstichGUI::genericErrorDialog(QWidget *parent, const std::exception& exc) {
    genericErrorDialog(parent, exc.what());
}

void KreuzstichGUI::genericErrorDialog(QWidget *parent, const QString &msg) {
    QMessageBox::critical(parent,QObject::tr("Error"), msg);
}
