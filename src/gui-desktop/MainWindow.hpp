/*
  Kreuzstich
  Copyright (c) 2013-2020, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

// STL
#include <memory.h>

// Qt
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();

private slots:
    // Help menu
    void openAboutBox(); /**< Open the "about" dialog */

private:
    std::shared_ptr<Ui::MainWindow> m_ui;
};

#endif // MAINWINDOW_HPP
