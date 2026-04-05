#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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
    MainWindow();
    ~MainWindow();

private slots:
    // Help menu
    void openAboutBox();

private:
    Ui::MainWindow *m_ui;
};

#endif // MAINWINDOW_HPP
