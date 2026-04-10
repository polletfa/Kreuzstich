#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "AboutDialog.hpp"
#include "Application.hpp"

// Qt
#include <QMessageBox>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    Application::replaceVersionVars(this);
    Application::replaceVersionVars(m_ui->action_About_NAME);
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
