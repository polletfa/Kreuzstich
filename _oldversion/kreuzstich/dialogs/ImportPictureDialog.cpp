// kreuzstich
#include "dialogs/ImportPictureDialog.h"
#include "ui_ImportPictureDialog.h"
#include "version.h"
#include "error.h"

// libkreuzstich
#include "kreuzstich/creator.h"
#include "kreuzstich/resources.h"

// stdlib & stl
#include <sstream>

using namespace KreuzstichGUI;

// *****************************************
// Constructors & destructors
// *****************************************

ImportPictureDialog::ImportPictureDialog(QWidget *parent) :
    QDialog(parent), m_creator(NULL),
    ui(new Ui::ImportPictureDialog)
{
    ui->setupUi(this);
}

ImportPictureDialog::~ImportPictureDialog()
{
    delete ui;
}

// *****************************************
// Static methods and members
// *****************************************

// *****************************************
// Public methods
// *****************************************

void ImportPictureDialog::setFilename(std::string filename) {
    m_filename = filename;
    setWindowTitle(filename.c_str());
}

ImportParameter ImportPictureDialog::parameters() const {
    ImportParameter params;
    params.creator = creator();
    params.width = ui->width_sb->value();
    params.height = ui->height_sb->value();
    params.colortable = ui->threadlist_cmb->currentText().toStdString();
    params.reduceTo = ui->reduceTo_cb->isChecked();
    params.maxColors = ui->maxColors_sb->value();
    return params;
}

// *****************************************
// Protected & Private methods
// *****************************************

Kreuzstich::Creator* ImportPictureDialog::creator() const {
    return m_creator;
}

// *****************************************
// Qt slots
// *****************************************

int ImportPictureDialog::exec() {
    try {
        m_creator = new Kreuzstich::Creator();
        m_creator->setProperty("createdWith", versionString());
        m_creator->importPicture(m_filename);

        std::stringstream ss;
        ss << m_creator->width() << "x" << m_creator->height();
        ui->originalSize_lbl->setText(ss.str().c_str());
        ui->width_sb->setValue(m_creator->width());
        ui->height_sb->setValue(m_creator->height());
        std::vector<std::string> threadlists = Kreuzstich::threadLists();
        for(std::vector<std::string>::iterator it = threadlists.begin(); it != threadlists.end(); it++) {
            ui->threadlist_cmb->addItem(it->c_str());
        }
        QDialog::exec();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(parentWidget(), kexc);
        reject();
    } catch(std::exception& exc) {
        genericErrorDialog(parentWidget(), exc);
        reject();
    }
    return this->result();
}

void ImportPictureDialog::reduceToChanged() {
    ui->maxColors_sb->setEnabled(ui->reduceTo_cb->isChecked());
}

void ImportPictureDialog::updateHeight() {
    if(ui->keepAspectRatio_cb->isChecked()) {
        bool oldstate = ui->height_sb->blockSignals(true);
        ui->height_sb->setValue(ui->width_sb->value() * m_creator->height() / m_creator->width());
        ui->height_sb->blockSignals(oldstate);
    }
}

void ImportPictureDialog::updateWidth() {
    if(ui->keepAspectRatio_cb->isChecked()) {
        bool oldstate = ui->width_sb->blockSignals(true);
        ui->width_sb->setValue(ui->height_sb->value() * m_creator->width() / m_creator->height());
        ui->width_sb->blockSignals(oldstate);
    }
}

// *****************************************
// Qt events
// *****************************************
