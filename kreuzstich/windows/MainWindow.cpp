//kreuzstich
#include "windows/MainWindow.h"
#include "ui_MainWindow.h"
#include "dialogs/AboutDialog.h"
#include "windows/Editor.h"
#include "dialogs/ImportPictureDialog.h"
#include "tasks/ImportTask.h"
#include "dialogs/NewPictureDialog.h"
#include "error.h"
#include "version.h"

// libkreuzstich
#include "kreuzstich/exceptions.h"
#include "kreuzstich/resources.h"

// stdlib & stl
#include <sstream>

// boost
#include <boost/filesystem.hpp>

// Qt
#include <QCloseEvent>
#include <QProgressBar>
#include <QSpinBox>
#include <QLabel>
#include <QMessageBox>
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QComboBox>
#include <QPainter>

using namespace std;
using namespace KreuzstichGUI;

// *****************************************
// Constructors & destructors
// *****************************************

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage(KreuzstichGUI::versionString().c_str());
    m_windowActionGroup = new QActionGroup(this);

    initStatusBar();
    initToolBar();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_windowActionGroup;
    delete m_progress;
    delete m_zoom_sb;
    delete m_zoom_lbl;
    delete m_percent_lbl;
    delete m_colors_cmb;
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

void MainWindow::addChildWindow(ChildWindow* child) {
    QMdiSubWindow* subw = ui->mdiArea->addSubWindow(child);
    ui->menu_Window->addAction(child->windowMenuAction());
    m_windowActionGroup->addAction(child->windowMenuAction());
    subw->show();
}

void MainWindow::initToolBar() {
    m_colors_cmb = new QComboBox(this);
    m_colors_cmb->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->toolBar->addWidget(m_colors_cmb);

    ui->toolBar->addSeparator();

    m_zoom_lbl = new QLabel(this);
    m_zoom_lbl->setPixmap(QPixmap(":/icons/zoom.png"));
    ui->toolBar->addWidget(m_zoom_lbl);

    m_zoom_sb = new QSpinBox(this);
    m_zoom_sb->setMinimum(100);
    m_zoom_sb->setMaximum(5000);
    m_zoom_sb->setSingleStep(50);
    ui->toolBar->addWidget(m_zoom_sb);

    m_percent_lbl = new QLabel(this);
    m_percent_lbl->setText(tr(" %"));
    ui->toolBar->addWidget(m_percent_lbl);

    connect(m_colors_cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(selectColor(int)));
    connect(m_zoom_sb, SIGNAL(valueChanged(int)), this, SLOT(zoom(int)));

    subwindowActivated();
}

void MainWindow::initStatusBar() {
    m_progress = new QProgressBar(this);
    m_progress->setTextVisible(false);
    m_progress->setVisible(false);
    m_progress->setMinimum(0);
    m_progress->setMaximum(10000);
    ui->statusbar->addPermanentWidget(m_progress);
}

ChildWindow* MainWindow::activeChild() const {
    QMdiSubWindow *subWindow = ui->mdiArea->activeSubWindow();
    if (subWindow)
        return qobject_cast<ChildWindow*>(subWindow->widget());
    return 0;
}

void MainWindow::updateMenu() {
    bool hasWindows = ui->mdiArea->subWindowList().count() > 0;
    bool hasMultipleWindows = ui->mdiArea->subWindowList().count() > 1;
    bool hasZoom = false;
    bool hasGenerateTools = false;
    if(activeChild()) {
        hasZoom = activeChild()->hasZoom();
        hasGenerateTools = activeChild()->hasGenerateTools();
    }
    bool hasActiveWindow = activeChild() != NULL;
    bool hasModifications = false;
    if(hasActiveWindow) hasModifications = activeChild()->isWindowModified();

    // view menu
    ui->actionZoom_in->setEnabled(hasZoom);
    ui->actionZoom_out->setEnabled(hasZoom);

    // window menu
    ui->action_Cascade->setEnabled(hasWindows);
    ui->action_Tile->setEnabled(hasWindows);
    ui->action_Previous->setEnabled(hasMultipleWindows);
    ui->action_Next->setEnabled(hasMultipleWindows);

    // generate menu
    ui->actionSave_picture->setEnabled(hasGenerateTools);
    ui->actionGenerate_grid->setEnabled(hasGenerateTools);
    ui->actionGenerate_script_as_text->setEnabled(hasGenerateTools);
    ui->actionGenerate_script_as_LaTeX->setEnabled(hasGenerateTools);

    // file menu
    ui->actionClo_se_all->setEnabled(hasWindows);
    ui->actionSave_all->setEnabled(hasWindows);

    ui->action_Close->setEnabled(hasActiveWindow);
    ui->action_Save->setEnabled(hasModifications);
    ui->actionSave_as->setEnabled(hasActiveWindow);
    if(hasActiveWindow)
        activeChild()->windowMenuAction()->setChecked(true);
}

void MainWindow::updateToolBar() {
    bool hasZoom = false;
    bool hasImageTools = false;
    if(activeChild()) {
        hasZoom = activeChild()->hasZoom();
        hasImageTools = activeChild()->hasImageTools();
    }

    m_colors_cmb->setEnabled(hasImageTools);
    if(hasImageTools) {
        bool oldstate = m_colors_cmb->blockSignals(true);
        m_colors_cmb->clear();
        Kreuzstich::ThreadColors colortable = dynamic_cast<ImageToolsInterface*>(activeChild())->colortable();
        int i = 0;
        for(Kreuzstich::ThreadColors::iterator it = colortable.begin(); it != colortable.end(); it++, i++) {
            m_colors_cmb->addItem(it->second.toStdString().c_str());

            Magick::ColorRGB rgb = it->first.rgb();
            m_colors_cmb->setItemIcon(i, makeColorIcon(QColor(255*rgb.red(), 255*rgb.green(), 255*rgb.blue())));
        }
        if(dynamic_cast<ImageToolsInterface*>(activeChild())->currentColor() < m_colors_cmb->count())
            m_colors_cmb->setCurrentIndex(dynamic_cast<ImageToolsInterface*>(activeChild())->currentColor());
        m_colors_cmb->blockSignals(oldstate);
    }
    m_zoom_lbl->setEnabled(hasZoom);
    m_zoom_sb->setEnabled(hasZoom);
    m_percent_lbl->setEnabled(hasZoom);
    if(hasZoom)
        m_zoom_sb->setValue(dynamic_cast<ZoomInterface*>(activeChild())->zoomLevel());
}

QIcon MainWindow::makeColorIcon(QColor color) {
    QPixmap pix(50, 30);
    QPainter paint(&pix);
    paint.setPen(QColor(0, 0, 0));
    paint.fillRect(0, 0, 49, 29, color);
    paint.drawRect(0, 0, 49, 29);
    return QIcon(pix);
}

// *****************************************
// Qt slots
// *****************************************

void MainWindow::taskCompleted(Task* task) {
    try {
        if(!task->taskName().compare("ImportTask")) {
            ui->actionNew_project_from_picture->setEnabled(true);
            if(dynamic_cast<ImportTask*>(task)->creator()) {
                Editor* edit = new Editor(this);
                edit->setCreator(dynamic_cast<ImportTask*>(task)->creator());
                edit->setModified(true);
                addChildWindow(edit);
            }
        }
        delete task;
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::taskFailed(Task* task, const QString& exc) {
    ui->actionNew_project_from_picture->setEnabled(true);
    genericErrorDialog(this, exc);

    delete task;
}

void MainWindow::showMessage(const QString& str) {
    ui->statusbar->showMessage(str);
}

void MainWindow::showProgress(bool visible) {
    m_progress->setVisible(visible);
}

void MainWindow::setProgress(double value) {
    m_progress->setValue((int)(value*m_progress->maximum()));
}

void MainWindow::selectColor(int i) {
    try {
        if(activeChild()) {
            if(activeChild()->hasImageTools())
                dynamic_cast<ImageToolsInterface*>(activeChild())->setCurrentColor(i);
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::zoom(int value) {
    try {
        if(activeChild()) {
            if(activeChild()->hasZoom()) {
                dynamic_cast<ZoomInterface*>(activeChild())->setZoomLevel(value);
            }
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::subwindowActivated() {
    try {
        updateMenu();
        updateToolBar();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

// *****************************************
// Qt slots (file menu)
// *****************************************

void MainWindow::newEmptyProject() {
    try {
        NewPictureDialog* dialog = new NewPictureDialog(this);
        dialog->setModal(true);
        if(dialog->exec() == QDialog::Accepted) {
            Editor* edit = new Editor(this);
            Kreuzstich::Creator* creator = new Kreuzstich::Creator(dialog->columns(), dialog->rows(), Magick::ColorRGB("#ffffff"));
            creator->setProperty("createdWith", versionString());
            creator->setColortable(dialog->colortable());
            edit->setCreator(creator);
            edit->setModified(true);
            addChildWindow(edit);
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::newProjectFromPicture() {
    try {
        QString currentDir = boost::filesystem::current_path().string().c_str();
        QString file = QFileDialog::getOpenFileName(this, tr("Import picture"), currentDir,
                                     tr("All Images") + " (*.bmp *.dib *.rle *.jpg *.jpeg *.jpe *.jfif *.gif *.tif *.tiff *.png);;" +
                                     tr("BMP Files") + " (*.bmp *.dib *.rle);;" +
                                     tr("JPEG Files") + " (*.jpg *.jpeg *.jpe *.jfif);;" +
                                     tr("GIF Files") + " (*.gif);;"+
                                     tr("TIFF Files") + " (*.tif *.tiff);;"+
                                     tr("PNG Files") + " (*.png);;"+
                                     tr("All Files") + " (*)");
        if(!file.isEmpty()) {
            ImportPictureDialog* dialog = new ImportPictureDialog(this);
            dialog->setFilename(file.toStdString());
            dialog->setModal(true);
            if(dialog->exec() == QDialog::Accepted) {
                ui->actionNew_project_from_picture->setEnabled(false);
                ImportParameter params = dialog->parameters();
                ImportTask* task= new ImportTask(this, params);
                task->start();
            }
        }
    } catch(Kreuzstich::Exception& kexc) {
        ui->actionNew_project_from_picture->setEnabled(true);
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        ui->actionNew_project_from_picture->setEnabled(true);
        genericErrorDialog(this, exc);
    }
}

void MainWindow::openProject() {
    try {
        QFileDialog selectFile(this);
        selectFile.setDirectory(boost::filesystem::current_path().string().c_str());
        selectFile.setAcceptMode(QFileDialog::AcceptOpen);
        selectFile.setWindowTitle(tr("Open Project"));
        selectFile.setFileMode(QFileDialog::ExistingFile);
        QStringList filters;
        filters << tr("Kreuzstich Projects") + " (*.gz)"
                << tr("All Files") + " (*)";
        selectFile.setNameFilters(filters);
        selectFile.setDefaultSuffix("gz");
        QString file;
        if(selectFile.exec()) {
            file = selectFile.selectedFiles().at(0);
        }
        if(!file.isEmpty()) {
            Editor* edit = new Editor(this);
            Kreuzstich::Creator* creator = new Kreuzstich::Creator(file.toStdString());
            edit->setCreator(creator);
            edit->setFilename(file.toStdString());
            addChildWindow(edit);
        }
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::saveProject() {
    try {
        if(activeChild())
            if(activeChild()->hasSaveInterface()) {
                SaveInterface* si = dynamic_cast<SaveInterface*>(activeChild());
                if(si->save())
                    si->setModified(false);
            }
        updateMenu();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::saveProjectAs() {
    try {
        if(activeChild())
            if(activeChild()->hasSaveInterface()) {
                SaveInterface* si = dynamic_cast<SaveInterface*>(activeChild());
                if(si->saveAs())
                    si->setModified(false);
            }
        updateMenu();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::saveAll() {
    try {
        QList<QMdiSubWindow*> windows = ui->mdiArea->subWindowList();
        for(QList<QMdiSubWindow*>::iterator it = windows.begin(); it != windows.end(); it++) {
            if(dynamic_cast<ChildWindow*>((*it)->widget())->hasSaveInterface())
                if(dynamic_cast<SaveInterface*>((*it)->widget())->save())
                    dynamic_cast<SaveInterface*>((*it)->widget())->setModified(false);
        }
        updateMenu();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

// *****************************************
// Qt slots (generate menu)
// *****************************************

void MainWindow::savePicture() {
    try {
        if(activeChild())
            if(activeChild()->hasGenerateTools())
                dynamic_cast<GenerateToolsInterface*>(activeChild())->savePicture();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::generateGrid() {
    try {
        if(activeChild())
            if(activeChild()->hasGenerateTools())
                dynamic_cast<GenerateToolsInterface*>(activeChild())->generateGrid();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::generateScriptAsLaTeX() {
    try {
        if(activeChild())
            if(activeChild()->hasGenerateTools())
                dynamic_cast<GenerateToolsInterface*>(activeChild())->generateScriptAsLaTeX();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

void MainWindow::generateScriptAsText() {
    try {
        if(activeChild())
            if(activeChild()->hasGenerateTools())
                dynamic_cast<GenerateToolsInterface*>(activeChild())->generateScriptAsText();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

// *****************************************
// Qt slots (view menu)
// *****************************************

void MainWindow::zoomIn() {
    if(activeChild()) {
        int newlevel = dynamic_cast<ZoomInterface*>(activeChild())->zoomLevel() + m_zoom_sb->singleStep();
        if(newlevel > m_zoom_sb->maximum())
            newlevel = m_zoom_sb->maximum();
        m_zoom_sb->setValue(newlevel);
    }
}

void MainWindow::zoomOut() {
    if(activeChild()) {
        int newlevel = dynamic_cast<ZoomInterface*>(activeChild())->zoomLevel() - m_zoom_sb->singleStep();
        if(newlevel < m_zoom_sb->minimum())
            newlevel = m_zoom_sb->minimum();
        m_zoom_sb->setValue(newlevel);
    }
}

// *****************************************
// Qt slots (help menu)
// *****************************************

void MainWindow::openAboutBox() {
    try {
        AboutDialog about(this);
        about.setModal(true);
        about.exec();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}

// *****************************************
// Qt events
// *****************************************

void MainWindow::closeEvent(QCloseEvent *event) {
    try {
        QList<QMdiSubWindow*> windows = ui->mdiArea->subWindowList();
        for(QList<QMdiSubWindow*>::iterator it = windows.begin(); it != windows.end(); it++) {
            if(!(*it)->close()) {
                event->ignore();
                return;
            }
        }
        event->accept();
    } catch(Kreuzstich::Exception& kexc) {
        genericErrorDialog(this, kexc);
    } catch(exception& exc) {
        genericErrorDialog(this, exc);
    }
}
