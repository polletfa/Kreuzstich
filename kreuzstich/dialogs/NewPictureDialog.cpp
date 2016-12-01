// kreuzstich
#include "dialogs/NewPictureDialog.h"
#include "ui_NewPictureDialog.h"

// libkreuzstich
#include "kreuzstich/resources.h"

using namespace KreuzstichGUI;

// *****************************************
// Constructors & destructors
// *****************************************

NewPictureDialog::NewPictureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPictureDialog)
{
    ui->setupUi(this);
    ui->width_sb->setValue(50);
    ui->height_sb->setValue(50);
    std::vector<std::string> threadlists = Kreuzstich::threadLists();
    for(std::vector<std::string>::iterator it = threadlists.begin(); it != threadlists.end(); it++) {
        ui->threadlist_cmb->addItem(it->c_str());
    }
}

NewPictureDialog::~NewPictureDialog()
{
    delete ui;
}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

int NewPictureDialog::columns() const {
    return ui->width_sb->value();
}

int NewPictureDialog::rows() const {
    return ui->height_sb->value();
}

std::string NewPictureDialog::colortable() const {
    return ui->threadlist_cmb->currentText().toStdString();
}

// *****************************************
// Protected & Private methods
// *****************************************

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************
