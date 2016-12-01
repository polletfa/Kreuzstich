// kreuzstich
#include "windows/MainWindow.h"

// Qt
#include <QApplication>

using namespace KreuzstichGUI;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
