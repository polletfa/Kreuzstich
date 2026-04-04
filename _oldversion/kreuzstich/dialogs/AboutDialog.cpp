// kreuzstich
#include "dialogs/AboutDialog.h"
#include "ui_AboutDialog.h"
#include "version.h"

// libkreuzstich
#include "kreuzstich/resources.h"

// stdlib & stl
#include <sstream>

// boost
#include <boost/version.hpp>

// ImageMagick
#include <Magick++.h>

// libXml2
#include <libxml/xmlversion.h>

using namespace std;
using namespace KreuzstichGUI;

// *****************************************
// Constructors & destructors
// *****************************************

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->kreuzstichVersionString_lbl->setText(KreuzstichGUI::versionString().c_str());
    ui->libkreuzstichVersionString_lbl->setText(Kreuzstich::versionString().c_str());
    ui->copyright_lbl->setText(QString("<html>&copy;</html> ")+COPYRIGHT);

    ui->qtVersionString_lbl->setText(QString("<html>&bull;</html> Qt ")+QT_VERSION_STR);
    ui->MagickVersionString_lbl->setText(QString("<html>&bull;</html> ")+MagickCore::GetMagickVersion(NULL));
    stringstream ss;
    ss << "<html>&bull;</html> Boost "
       << BOOST_VERSION / 100000     << "."  // major version
       << BOOST_VERSION / 100 % 1000 << "."  // minior version
       << BOOST_VERSION % 100;               // patch level
    ui->BoostVersionString_lbl->setText(ss.str().c_str());
    ui->xml2VersionString_lbl->setText(QString("<html>&bull;</html> libXml2 ")+ LIBXML_DOTTED_VERSION);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************
