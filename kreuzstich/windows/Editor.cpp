// kreuzstich
#include "windows/Editor.h"
#include "ui_Editor.h"
#include "windows/MainWindow.h"
#include "tasks/Task.h"

// libkreuzstich
#include "kreuzstich/creator.h"

// stdlib & stl
#include <sstream>

// Boost
#include <boost/filesystem.hpp>

// ImageMagick
#include <Magick++.h>

// Qt
#include <QFileDialog>

using namespace KreuzstichGUI;
using namespace std;
namespace fs = boost::filesystem;

// *****************************************
// Constructors & destructors
// *****************************************

Editor::Editor(MainWindow *parent) :
    ChildWindow(parent), m_image(NULL),
    ui(new Ui::Editor)
{
    setCurrentColor(0);
    setZoomLevel(500);

    ui->setupUi(this);
    ui->picture_lbl->setEditor(this);
}

Editor::~Editor()
{
    delete ui;
    if(m_image) delete m_image;
}

// *****************************************
// Static methods and members
// *****************************************

QImage* Editor::toQImage(const Magick::Image &image)
{
    QImage *newQImage = new QImage(image.columns(), image.rows(), QImage::Format_RGB32);
    Magick::ColorRGB rgb;
    for (int y = 0; y < newQImage->height(); y++) {
        for (int x = 0; x < newQImage->width(); x++) {
            rgb = image.pixelColor(x, y);
            newQImage->setPixel(x, y, QColor((int) (255 * rgb.red())
                                             , (int) (255 * rgb.green())
                                             , (int) (255 * rgb.blue())).rgb());
        }
    }
    return newQImage;
}

// *****************************************
// Public methods
// *****************************************

Kreuzstich::Creator* Editor::creator() const { return m_creator; }

void Editor::setCreator(Kreuzstich::Creator *creator) {
    m_creator = creator;
    setColortable(creator->colortable());

    // update title
    updateTitle();

    std::stringstream ss;
    ss << creator->width() << "x" << creator->height();
    setTitleSuffix("size", ss.str().c_str());
    setTitleSuffix("colortable", creator->colortable().name().c_str());

    // update image
    if(m_image) delete m_image;
    m_image = toQImage(creator->image());
    zoomLevelChanged();
}

bool Editor::hasSaveInterface() const { return true; }

bool Editor::hasZoom() const { return true; }

bool Editor::hasImageTools() const { return true; }

bool Editor::hasGenerateTools() const { return true; }

void Editor::zoomLevelChanged() {
    if(m_image) {
        ui->picture_lbl->setPixmap(QPixmap::fromImage(*m_image).scaled(
                                   m_image->width() * zoomLevel() / 100,
                                   m_image->height() * zoomLevel() / 100
                                   ));
    }
}

void Editor::colortableChanged() {}

void Editor::currentColorChanged() {}

bool Editor::save() {
    if(m_filename.empty())
        return saveAs();
    else {
        m_creator->writeProjectFile(m_filename);
        return true;
    }
}

bool Editor::saveAs() {
    QFileDialog selectFile(this);
    selectFile.setDirectory(boost::filesystem::current_path().string().c_str());
    selectFile.setAcceptMode(QFileDialog::AcceptSave);
    selectFile.setWindowTitle(tr("Save"));
    selectFile.setFileMode(QFileDialog::AnyFile);
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
        m_filename = file.toStdString();
        m_creator->writeProjectFile(m_filename);
        updateTitle();
        return true;
    } else {
        return false;
    }
}

void Editor::setFilename(string filename) {
    m_filename = filename;
    updateTitle();
}

void Editor::generateGrid() {
    QFileDialog selectFile(this);
    selectFile.setDirectory(boost::filesystem::current_path().string().c_str());
    selectFile.setAcceptMode(QFileDialog::AcceptSave);
    selectFile.setWindowTitle(tr("Generate grid"));
    selectFile.setFileMode(QFileDialog::AnyFile);
    QStringList filters;
    filters << tr("All Images") + " (*.bmp *.dib *.rle *.jpg *.jpeg *.jpe *.jfif *.gif *.tif *.tiff *.png)"
            << tr("BMP Files") + " (*.bmp *.dib *.rle)"
            << tr("JPEG Files") + " (*.jpg *.jpeg *.jpe *.jfif)"
            << tr("GIF Files") + " (*.gif)"
            << tr("TIFF Files") + " (*.tif *.tiff)"
            << tr("PNG Files") + " (*.png)"
            << tr("All Files") + " (*)";
    selectFile.setNameFilters(filters);
    selectFile.setDefaultSuffix("jpg");
    QString file;
    if(selectFile.exec()) {
        file = selectFile.selectedFiles().at(0);
    }
    if(!file.isEmpty()) {
        class GenerateTask: public Task {
        public:
            GenerateTask(MainWindow* mw, Kreuzstich::Creator* creator, string filename)
                : Task(mw), m_creator(creator), m_filename(filename) {}
            void doTask(TaskProgressCallback& callback) {
                emit showMessage(tr("Selecting thread colors..."));
                m_creator->chooseThreads(callback);

                emit showMessage(tr("Saving grid..."));
                m_creator->writeGrid(m_filename, callback);                
            }
            string taskName() const { return "GenerateTask"; }

        private:
            string m_filename;
            Kreuzstich::Creator* m_creator;
        };
        GenerateTask* generateTask = new GenerateTask(mainWindow(), m_creator, file.toStdString());
        generateTask->start();
    }
}

void Editor::generateScriptAsLaTeX() {
    QFileDialog selectFile(this);
    selectFile.setDirectory(boost::filesystem::current_path().string().c_str());
    selectFile.setAcceptMode(QFileDialog::AcceptSave);
    selectFile.setWindowTitle(tr("Generate script as LaTeX"));
    selectFile.setFileMode(QFileDialog::AnyFile);
    QStringList filters;
    filters << tr("TeX/LaTeX files") + " (*.tex *.latex)"
            << tr("All Files") + " (*)";
    selectFile.setNameFilters(filters);
    selectFile.setDefaultSuffix("tex");
    QString file;
    if(selectFile.exec()) {
        file = selectFile.selectedFiles().at(0);
    }
    if(!file.isEmpty()) {
        class GenerateTask: public Task {
        public:
            GenerateTask(MainWindow* mw, Kreuzstich::Creator* creator, string filename)
                : Task(mw), m_creator(creator), m_filename(filename) {}
            void doTask(TaskProgressCallback& callback) {
                emit showMessage(tr("Selecting thread colors..."));
                m_creator->chooseThreads(callback);
                
                emit showMessage(tr("Saving script as LaTeX..."));

                // TODO: dialog to select unit and fabric count
                Kreuzstich::Report::Header header;
                header.unit = Kreuzstich::Length::CM;
                header.count = 7;
                header.margin = 0;
                Kreuzstich::Report::LaTeXWriter writer(m_filename);
                m_creator->writeScript(writer, header);                
            }
            string taskName() const { return "GenerateTask"; }

        private:
            string m_filename;
            Kreuzstich::Creator* m_creator;
        };
        GenerateTask* generateTask = new GenerateTask(mainWindow(), m_creator, file.toStdString());
        generateTask->start();
    }
}

void Editor::generateScriptAsText() {
    QFileDialog selectFile(this);
    selectFile.setDirectory(boost::filesystem::current_path().string().c_str());
    selectFile.setAcceptMode(QFileDialog::AcceptSave);
    selectFile.setWindowTitle(tr("Generate script as text"));
    selectFile.setFileMode(QFileDialog::AnyFile);
    QStringList filters;
    filters << tr("Text files") + " (*.txt)"
            << tr("All Files") + " (*)";
    selectFile.setNameFilters(filters);
    selectFile.setDefaultSuffix("txt");
    QString file;
    if(selectFile.exec()) {
        file = selectFile.selectedFiles().at(0);
    }
    if(!file.isEmpty()) {
        class GenerateTask: public Task {
        public:
            GenerateTask(MainWindow* mw, Kreuzstich::Creator* creator, string filename)
                : Task(mw), m_creator(creator), m_filename(filename) {}
            void doTask(TaskProgressCallback& callback) {
                emit showMessage(tr("Selecting thread colors..."));
                m_creator->chooseThreads(callback);
                
                emit showMessage(tr("Saving script as text..."));

                // TODO: dialog to select unit and fabric count
                Kreuzstich::Report::Header header;
                header.unit = Kreuzstich::Length::CM;
                header.count = 7;
                header.margin = 0;
                Kreuzstich::Report::TextWriter writer(m_filename);
                m_creator->writeScript(writer, header);                
            }
            string taskName() const { return "GenerateTask"; }

        private:
            string m_filename;
            Kreuzstich::Creator* m_creator;
        };
        GenerateTask* generateTask = new GenerateTask(mainWindow(), m_creator, file.toStdString());
        generateTask->start();
    }
}

// *****************************************
// Protected & Private methods
// *****************************************

void Editor::updateTitle() {
    if(m_filename.empty()) {
        // new file, not yet saved
        if(!m_creator->hasProperty("pictureImportedFrom")) {
            // from scratch
            setTitle(tr("(new project)"));
        } else {
            // imported
            fs::path p(m_creator->property("pictureImportedFrom"));
            setTitle(p.stem().string().c_str());
            setTitleSuffix("imported", tr("imported"));
        }
    } else {
        // existing project
        fs::path p(m_filename);
        setTitle(p.stem().string().c_str());
        setTitleSuffix("imported", "");
    }
}

// *****************************************
// Qt slots
// *****************************************

// *****************************************
// Qt events
// *****************************************
