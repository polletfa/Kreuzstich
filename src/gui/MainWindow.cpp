#include "MainWindow.hpp"
#include "./ui_MainWindow.h"
#include "Version.hpp"
#include "AboutDialog.hpp"

// Qt
#include <QMessageBox>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    Version::replaceVars(this);
    Version::replaceVars(m_ui->action_About_NAME);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::openAboutBox() {
    AboutDialog about(this);
    about.setModal(true);
    about.exec();
}
