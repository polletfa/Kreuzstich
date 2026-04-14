/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include "AboutDialog.hpp"
#include "Application.hpp"

// Qt
#include <QMessageBox>

MainWindow::MainWindow()
    : QMainWindow(nullptr)
    , m_ui(std::make_shared<Ui::MainWindow>())
{
    m_ui->setupUi(this);
    Application::replaceVersionVars(this);
    Application::replaceVersionVars(m_ui->action_About_NAME);
}

void MainWindow::openAboutBox() {
    AboutDialog about(this);
    about.setModal(true);
    about.exec();
}
