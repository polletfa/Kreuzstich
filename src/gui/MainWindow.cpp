#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "version.hpp"

// Qt
#include <QMessageBox>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setWindowTitle(windowTitle().replace("$NAME$", Version::NAME));
    m_ui->action_About_NAME->setText(m_ui->action_About_NAME->text().replace("$NAME$", Version::NAME));
    m_ui->action_About_NAME->setIconText(m_ui->action_About_NAME->iconText().replace("$NAME$", Version::NAME));
    m_ui->action_About_NAME->setToolTip(m_ui->action_About_NAME->toolTip().replace("$NAME$", Version::NAME));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::openAboutBox() {
    QMessageBox::information(this, "Kreuzstich", Version::getVersionString());
    //QApplication::aboutQt();
}
